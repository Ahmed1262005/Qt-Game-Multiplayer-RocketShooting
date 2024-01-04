<?php
require __DIR__ . '/vendor/autoload.php';
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

use Ratchet\ConnectionInterface;
use Ratchet\Http\HttpServer;
use Ratchet\MessageComponentInterface;
use Ratchet\Server\IoServer;
use Ratchet\WebSocket\WsServer;

echo "Server starting...\n";

//die();
class GameLobbyHandler
{
    private $lobbyID;
    private $gameClientList = [];

    public function __construct($lobbyID)
    {
        $this->lobbyID = $lobbyID;
    }

    public function addClient($clientID)
    {
        if (!in_array($clientID, $this->gameClientList)) {
            $this->gameClientList[] = $clientID;
        }
    }

    public function clientsInLobbyList()
    {
        return $this->gameClientList;
    }
}

class MessageProcessorHandler
{
    private $server;

    public function __construct($server)
    {
        $this->server = $server;
    }

    public function processMessage($message)
    {
        // Split the message into parts
        $parts = explode(';', $message);

        // Parse the parts into a key-value array
        $messageData = [];
        foreach ($parts as $part) {
            list($key, $value) = explode(':', $part);
            $messageData[$key] = $value;
        }

        // Check if the message is valid
        if (isset($messageData['type'])) {
            $type = $messageData['type'];
            $payload = isset($messageData['payLoad']) ? trim($messageData['payLoad']) : null;
            $sender = isset($messageData['sender']) ? trim($messageData['sender']) : null;
            $lobbyID = isset($messageData['lobbyID']) ? trim($messageData['lobbyID']) : null;

            // Based on the type of the message, call the appropriate method on the server
            switch ($type) {
                case 'joinGame':
                    $this->server->joinGameLobbyRequest($payload, $sender);
                    break;
                case 'message':
                    $this->server->messageLobbyRequest($lobbyID, $sender, $payload);
                    break;
                case 'createGame':
                    $this->server->createGameLobbyRequest($sender);
                    break;
                case 'rocketLaunch':
                    $position = explode(',', $messageData['position']);
                    $direction = explode(',', $messageData['direction']);
                    $this->server->broadcastRocketLaunch($lobbyID, $position[0], $position[1], $direction[0], $direction[1], $sender);
                    break;
                default:
                    echo "Unknown message type: {$type}\n";
                    break;
            }
        } else {
            echo "Invalid message received: {$message}\n";
        }
    }
}

class WebSocketServer implements MessageComponentInterface
{
    protected $clients = [];
    private $gameLobbyMap = [];

    public function onOpen(ConnectionInterface $conn)
    {
        // Handle new connection
        $clientID = abs(crc32(uniqid()));
        $this->clients[$clientID] = $conn;
        $conn->send("type:uniqueID;payLoad:{$clientID}");

        echo "New client connected: {$clientID}\n";
    }

    public function onMessage(ConnectionInterface $from, $msg)
    {
        // Handle incoming messages
        echo "Received message: {$msg}\n";

        $messageProcessor = new MessageProcessorHandler($this);
        $messageProcessor->processMessage($msg);
    }


    public function createGameLobbyRequest($uniqueID)
    {
        $newLobbyID = abs(crc32(uniqid()));

        $newGameLobby = new GameLobbyHandler($newLobbyID);
        $newGameLobby->addClient($uniqueID);

        $this->gameLobbyMap[$newLobbyID] = $newGameLobby;

        echo "New game lobby created, ID: {$newLobbyID}\n";
        $uniqueID = trim($uniqueID);
        if (isset($this->clients[$uniqueID])) {
            $this->clients[$uniqueID]->send("type:newLobbyCreated;payLoad:{$newLobbyID};clientList:" . implode(',', $newGameLobby->clientsInLobbyList()));
        } else {
            echo "Client {$uniqueID} does not exist\n";
        }
    }

    public function broadcastRocketLaunch($lobbyID, $positionX, $positionY, $directionX, $directionY, $sender)
    {
        // Check if the lobby exists

        if (isset($this->gameLobbyMap[$lobbyID])) {
            // Get all clients in the lobby
            $clients = $this->gameLobbyMap[$lobbyID]->clientsInLobbyList();

            // Form the message
            $message = "type:rocketLaunch;position:{$positionX},{$positionY};direction:{$directionX},{$directionY}";

            // Iterate over all clients and send the message
            foreach ($clients as $clientID) {
                if (isset($this->clients[$clientID]) && $clientID != $sender) {
                    $this->clients[$clientID]->send($message);
                }
            }

            echo "Rocket launch message broadcasted to lobby {$lobbyID}: {$message}\n";
        } else {
            $this->clients[$sender]->send("type:error;payLoad:Lobby does not exist");

            echo "Lobby {$lobbyID} does not exist\n";
        }
    }

    public function onClose(ConnectionInterface $conn)
    {
        // Handle connection close
        foreach ($this->clients as $clientID => $client) {
            if ($client === $conn) {
                unset($this->clients[$clientID]);
                echo "Client disconnected: {$clientID}\n";
                break;
            }
        }
    }


    public function joinGameLobbyRequest($payload, $sender)
    {
        // Extract the lobby ID and client ID from the payload
        $lobbyID = $payload ?? null;
        $clientID = $sender ?? null;

        // Check if the lobby exists
        if (isset($this->gameLobbyMap[$lobbyID])) {
            // Add the client to the lobby
            $newGameLobby = $this->gameLobbyMap[$lobbyID];
            $newGameLobby->addClient($clientID);

            echo "Client {$clientID} joined lobby {$lobbyID}\n";
            $this->clients[$clientID]->send("type:joinSuccess;payLoad:{$lobbyID};clientList:" . implode(',', $newGameLobby->clientsInLobbyList()));
            // Form the updatedClientList message
            $message = "type:updatedClientList;clientList:" . implode(',', $newGameLobby->clientsInLobbyList());

            // Send the updatedClientList message to all clients in the lobby
            $clients = $newGameLobby->clientsInLobbyList();
            foreach ($clients as $client) {
                if (isset($this->clients[$client])) {
                    $this->clients[$client]->send($message);
                }
            }

        } else {
            echo "Lobby {$lobbyID} does not exist\n";
            $this->clients[$clientID]->send("type:error;payLoad:Lobby does not exist");
        }
    }

    public function messageLobbyRequest($lobbyID, $sender, $payload)
    {
        // Extract the lobby ID, client ID and message from the payload
        $lobbyID = $lobbyID ?? null;
        $clientID = $sender ?? null;
        $message = $payload ?? null;

        // Check if the lobby exists
        if (isset($this->gameLobbyMap[$lobbyID])) {
            // Send the message to all clients in the lobby
            $clients = $this->gameLobbyMap[$lobbyID]->clientsInLobbyList();
            foreach ($clients as $client) {
                if (isset($this->clients[$client])) {
                    $this->clients[$client]->send("type:lobbyMessage;payLoad:{$message};sender:{$clientID}");
                }
            }

            echo "Message sent to lobby {$lobbyID} by client {$clientID}: {$message}\n";
        } else {
            $this->clients[$clientID]->send("type:error;payLoad:Lobby does not exist");

            echo "Lobby {$lobbyID} does not exist\n";
        }
    }

    public function onError(ConnectionInterface $conn, \Exception $e)
    {
        // Handle errors
        echo "Error: {$e->getMessage()}\n";
        $conn->close();
    }
}

$server = IoServer::factory(
    new HttpServer(
        new WsServer(
            new WebSocketServer()
        )
    ),
    8585
);

$server->run();
echo "Server started\n";

