#include "startmenu.h"
#include "ui_startmenu.h"
#include "level.h"
#include <QMediaPlayer>
#include <QAudioOutput>
#include "PhysicsWorld.h"

StartMenu::StartMenu(QWidget *parent, GameManager *manager) :
        QDialog(parent),
        ui(new Ui::StartMenu) {
    this->manager = manager;
    connect(manager, &GameManager::inGameLobby, this, &StartMenu::openChatLobbyWindow);

    ui->setupUi(this);
    QPixmap background(":/Resources/Images/StartMenuBackground.png");
    QPixmap lock("://Resources/Images/lock.png");
    ui->labellock_1->setPixmap(lock.scaled(ui->labellock_1->width(), ui->labellock_1->height()));
    ui->labellock_2->setPixmap(lock.scaled(ui->labellock_2->width(), ui->labellock_2->height()));
    ui->labellock_3->setPixmap(lock.scaled(ui->labellock_3->width(), ui->labellock_3->height()));
    ui->labellock_4->setPixmap(lock.scaled(ui->labellock_4->width(), ui->labellock_4->height()));
    ui->labellock_5->setPixmap(lock.scaled(ui->labellock_5->width(), ui->labellock_5->height()));
    ui->labellock_6->setPixmap(lock.scaled(ui->labellock_6->width(), ui->labellock_6->height()));
    ui->labellock_7->setPixmap(lock.scaled(ui->labellock_7->width(), ui->labellock_7->height()));
    ui->labellock_8->setPixmap(lock.scaled(ui->labellock_8->width(), ui->labellock_8->height()));
    ui->labellock_9->setPixmap(lock.scaled(ui->labellock_9->width(), ui->labellock_9->height()));
    ui->labellock_10->setPixmap(lock.scaled(ui->labellock_10->width(), ui->labellock_10->height()));
    ui->labelBackground->setPixmap(background.scaled(1920, 1080));

    setMusicPlayer(true);
    ui->labelTitle->setPixmap(QPixmap(":/Resources/Images/Title.png").scaled(700, 200, Qt::KeepAspectRatio));
    generateLevels();

    QPixmap coloredStarsPic(":/Resources/Images/coloredStars.png");
    ui->labelColoredStarsL1->setPixmap(
            coloredStarsPic.scaled(ui->labelColoredStarsL1->width(), ui->labelColoredStarsL1->height(),
                                   Qt::KeepAspectRatio));
    ui->labelColoredStarsL2->setPixmap(
            coloredStarsPic.scaled(ui->labelColoredStarsL2->width(), ui->labelColoredStarsL2->height(),
                                   Qt::KeepAspectRatio));
    ui->labelColoredStarsL3->setPixmap(
            coloredStarsPic.scaled(ui->labelColoredStarsL2->width(), ui->labelColoredStarsL2->height(),
                                   Qt::KeepAspectRatio));
    ui->labelColoredStarsL4->setPixmap(
            coloredStarsPic.scaled(ui->labelColoredStarsL2->width(), ui->labelColoredStarsL2->height(),
                                   Qt::KeepAspectRatio));
    ui->labelColoredStarsL5->setPixmap(
            coloredStarsPic.scaled(ui->labelColoredStarsL2->width(), ui->labelColoredStarsL2->height(),
                                   Qt::KeepAspectRatio));
    ui->labelColoredStarsL6->setPixmap(
            coloredStarsPic.scaled(ui->labelColoredStarsL2->width(), ui->labelColoredStarsL2->height(),
                                   Qt::KeepAspectRatio));
    ui->labelColoredStarsL7->setPixmap(
            coloredStarsPic.scaled(ui->labelColoredStarsL2->width(), ui->labelColoredStarsL2->height(),
                                   Qt::KeepAspectRatio));
    ui->labelColoredStarsL8->setPixmap(
            coloredStarsPic.scaled(ui->labelColoredStarsL2->width(), ui->labelColoredStarsL2->height(),
                                   Qt::KeepAspectRatio));
    ui->labelColoredStarsL9->setPixmap(
            coloredStarsPic.scaled(ui->labelColoredStarsL2->width(), ui->labelColoredStarsL2->height(),
                                   Qt::KeepAspectRatio));
    ui->labelColoredStarsL10->setPixmap(
            coloredStarsPic.scaled(ui->labelColoredStarsL2->width(), ui->labelColoredStarsL2->height(),
                                   Qt::KeepAspectRatio));

    ui->labelColoredStarsL1->setVisible(1);
    ui->labelColoredStarsL2->setVisible(0);
    ui->labelColoredStarsL3->setVisible(0);
    ui->labelColoredStarsL4->setVisible(0);
    ui->labelColoredStarsL5->setVisible(0);
    ui->labelColoredStarsL6->setVisible(0);
    ui->labelColoredStarsL7->setVisible(0);
    ui->labelColoredStarsL8->setVisible(0);
    ui->labelColoredStarsL9->setVisible(0);
    ui->labelColoredStarsL10->setVisible(0);


    QPixmap blackStarsPic(":/Resources/Images/blackStars.png");
    ui->labelBlackStars_1->setPixmap(
            blackStarsPic.scaled(ui->labelBlackStars_1->width(), ui->labelBlackStars_1->height()));
    ui->labelBlackStars_2->setPixmap(
            blackStarsPic.scaled(ui->labelBlackStars_2->width(), ui->labelBlackStars_2->height()));
    ui->labelBlackStars_3->setPixmap(
            blackStarsPic.scaled(ui->labelBlackStars_3->width(), ui->labelBlackStars_3->height()));
    ui->labelBlackStars_4->setPixmap(
            blackStarsPic.scaled(ui->labelBlackStars_4->width(), ui->labelBlackStars_4->height()));
    ui->labelBlackStars_5->setPixmap(
            blackStarsPic.scaled(ui->labelBlackStars_5->width(), ui->labelBlackStars_5->height()));
    ui->labelBlackStars_6->setPixmap(
            blackStarsPic.scaled(ui->labelBlackStars_6->width(), ui->labelBlackStars_6->height()));
    ui->labelBlackStars_7->setPixmap(
            blackStarsPic.scaled(ui->labelBlackStars_7->width(), ui->labelBlackStars_7->height()));
    ui->labelBlackStars_8->setPixmap(
            blackStarsPic.scaled(ui->labelBlackStars_8->width(), ui->labelBlackStars_8->height()));
    ui->labelBlackStars_9->setPixmap(
            blackStarsPic.scaled(ui->labelBlackStars_9->width(), ui->labelBlackStars_9->height()));
    ui->labelBlackStars_10->setPixmap(
            blackStarsPic.scaled(ui->labelBlackStars_10->width(), ui->labelBlackStars_10->height()));

    void StartMenu::openChatLobbyWindow() {
        qDebug() << "Joined lobby";
        ChatLobbyWindow *chatLobbyWindow = new ChatLobbyWindow(manager, this);
        chatLobbyWindow->show();
        this->hide(); // Optionally, hide the current window//    chatLobbyWindow.setModal(true);
//    chatLobbyWindow.exec();
//    chatLobbyWindow.show();
//    hide();
    }
    void StartMenu::generateLevels() {
        for (int i = 1; i <= 10; ++i) {
            Level *level = new Level(i);
            switch (i) {
            case 1: //one enemy >> DONE
                    // Configuration for level 1
                level->AddTower(800.0f,-10.0f,200.0f,500.0f,2);
                    level->AddEnemy(1100.f, -10.f, 100.f, 100.f, ArmoredEnemy);
                    break;
            case 2: //one enemy >> DONE
                    // Configuration for level 2
                    level->AddTower(600.0f, -10.0f, 200.0f, 500.0f, 1);
                level->AddTower(850.0f,-10.0f,200.0f,500.0f,1);
                level->AddEnemy(1050.f, -20.f,200.f,200.f,ArmoredEnemy);
                    break;
            case 3: //one enemy >> DONE
                    // Configuration for level 3
                level->AddTower(700.0f,-10.0f,200.0f,500.0f,2);
                level->AddTower(910.0f,-10.0f,150.0f,400.0f,1); //short
                level->AddEnemy(1080.f, -20.f,200.f,200.f,ArmoredEnemy);
                level->AddTower(1300.0f,-10.0f,200.0f,500.0f,2);
                    break;
            case 4: //two enemies >> DONE
                    // Configuration for level 4
                level->AddEnemy(700.f, -20.f,200.f,200.f,ArmoredEnemy);
                level->AddTower(820.0f,-20.0f,200.0f,600.0f,1);
                level->AddEnemy(1020.f, -20.f,200.f,200.f,ArmoredEnemy);

                    break;
            case 5://two enemies >> DONE
                    // Configuration for level 5
                level->AddTower(700.0f,-20.0f,150.0f,400.0f,1);
                level->AddEnemy(860.f, -20.f,200.f,200.f,ArmoredEnemy);
                level->AddTower(1070.0f,-20.0f,200.0f,500.0f,2);
                level->AddEnemy(1275.f, -20.f,200.f,200.f,ArmoredEnemy);
                    break;
            case 6: //two enemies >>DONE
                    // Configuration for level 6
                level->AddTower(600.0f,-20.0f,200.0f,500.0f,2); //tall
                level->AddTower(820.0f,-20.0f,150.0f,400.0f,1);
                level->AddEnemy(975.f, -20.f,200.f,200.f,ArmoredEnemy);
                level->AddTower(1180.0f,-20.0f,200.0f,500.0f,2);
                level->AddEnemy(1385.f, -20.f,200.f,200.f,ArmoredEnemy);
                    break;
            case 7: //three enemies >>
                    // Configuration for level 7
                level->AddEnemy(650.f, -20.f,200.f,200.f,ArmoredEnemy);
                level->AddTower(851.0f,-20.0f,200.0f,500.0f,2);
                level->AddEnemy(1055.f, -20.f,200.f,200.f,ArmoredEnemy);
                level->AddTower(1260.0f,-20.0f,150.0f,400.0f,2);
                level->AddEnemy(1420.f, -20.f,200.f,200.f,ArmoredEnemy);
                    break;
            case 8: //three enemies
                    // Configuration for level 8
                level->AddTower(650.0f,-20.0f,150.0f,400.0f,2);
                level->AddEnemy(805.f, -20.f,200.f,200.f,ArmoredEnemy);
                level->AddTower(1010.0f,-20.0f,200.0f,500.0f,2); //tower 3
                level->AddEnemy(1215.f, -20.f,200.f,200.f,ArmoredEnemy);
                level->AddEnemy(1420.f, -20.f,200.f,200.f,ArmoredEnemy);
                    break;
            case 9: //three enemies
                    // Configuration for level 9
                level->AddTower(650.0f,-20.0f,150.0f,400.0f,2);
                level->AddEnemy(805.f, -20.f,200.f,200.f,ArmoredEnemy);
                level->AddTower(1010.0f,-20.0f,200.0f,500.0f,2);
                level->AddEnemy(1220.0f, -20.f,200.f,200.f,ArmoredEnemy);
                level->AddTower(1425.0f,-20.0f,150.0f,400.0f,2);
                level->AddEnemy(1580.0f, -20.f,200.f,200.f,ArmoredEnemy);
                    break;
            case 10: //three enemies
                    // Configuration for level 10
                level->AddTower(600.0f,-20.0f,200.0f,500.0f,2);
                level->AddTower(800.0f,-20.0f,150.0f,400.0f,1);
                level->AddEnemy(960.f, -20.f,150.f,150.f,ArmoredEnemy);
                level->AddTower(1115.0f,-20.0f,200.0f,500.0f,2);//tower3
                level->AddEnemy(1320.f, -20.f,150.f,150.f,ArmoredEnemy);
                level->AddTower(1475.0f,-20.0f,150.0f,400.0f,1);
                level->AddEnemy(1625.f, -20.f,150.f,150.f,ArmoredEnemy);
                    break;
                default:
                    // Default configuration for levels without a specific case
                    level->AddTower(600.0f * i, -10.0f * i, 200.0f * i, 500.0f * i, 1);
                    level->AddEnemy(1100.f * i, -10.f * i, 100.f * i, 100.f * i, BasicEnemy);
                    break;
            }
            levels.push_back(level);
        }

        levels[0]->set_unlocked(1);
        levels[2]->set_unlocked(1);


        //Testing
        levels[1]->set_unlocked(1);
        levels[2]->set_unlocked(1);
        levels[3]->set_unlocked(1);
        levels[4]->set_unlocked(1);
        levels[5]->set_unlocked(1);
        levels[6]->set_unlocked(1);
        levels[7]->set_unlocked(1);
        levels[8]->set_unlocked(1);
        levels[9]->set_unlocked(1);
        //


        ui->labellock_1->setVisible(0);


    }
    StartMenu::~StartMenu()
    {
        delete ui;
        delete MusicPlayer;
        delete Speaker;

    }

    Level *StartMenu::getCurrentLevel() {
        return levels[currentLevel];
    }

    void StartMenu::on_pushButtonlevel1_clicked() {

        currentLevel = 0;
        Level *lvl1 = getCurrentLevel();
        hide();
        MusicPlayer->stop();
        lvl1->drawObstacles();
        lvl1->window->setCurrentLevel(currentLevel);
        lvl1->window->showFullScreen();
        lvl1->window->setRocketCount(4);
        lvl1->window->get_startmenu(this);
        lvl1->window->get_currentlevelindex(currentLevel);
        lvl1->window->set_winoffset(4);


    }

    void StartMenu::on_pushButtonlevel2_clicked() {
        if (levels[1]->get_unlocked()) {


            hide();
            MusicPlayer->stop();
            currentLevel = 1;
            Level *lvl2 = getCurrentLevel();

            lvl2->drawObstacles();
            lvl2->window->setCurrentLevel(currentLevel);
            lvl2->window->showFullScreen();
            lvl2->window->get_startmenu(this);
            lvl2->window->get_currentlevelindex(currentLevel);
        }
    }


// Repeat for the other levels
    void StartMenu::on_pushButtonlevel3_clicked() {

        if (levels[2]->get_unlocked()) {
            hide();
            MusicPlayer->stop();
            currentLevel = 2;
            Level *lvl3 = getCurrentLevel();

            lvl3->drawObstacles();
            lvl3->window->setCurrentLevel(currentLevel);
            lvl3->window->showFullScreen();
            lvl3->window->setRocketCount(4);
            lvl3->window->get_startmenu(this);
            lvl3->window->get_currentlevelindex(currentLevel);
        }

    }

    void StartMenu::on_pushButtonlevel4_clicked() {

        if (levels[3]->get_unlocked()) {
            hide();
            MusicPlayer->stop();
            currentLevel = 3;
            Level *lvl4 = getCurrentLevel();

            lvl4->drawObstacles();
            lvl4->window->setCurrentLevel(currentLevel);
            lvl4->window->showFullScreen();
            lvl4->window->get_startmenu(this);
            lvl4->window->get_currentlevelindex(currentLevel);
        }
    }

    void StartMenu::on_pushButtonlevel5_clicked() {

        if (levels[4]->get_unlocked()) {
            hide();
            MusicPlayer->stop();
            currentLevel = 4; // Pass the difficulty as a parameter
            Level *lvl5 = getCurrentLevel();

            lvl5->drawObstacles();
            lvl5->window->setCurrentLevel(currentLevel);
            lvl5->window->showFullScreen();
            lvl5->window->get_startmenu(this);
            lvl5->window->get_currentlevelindex(currentLevel);
        }
    }

    void StartMenu::on_pushButtonlevel6_clicked() {

        if (levels[5]->get_unlocked()) {
            hide();
            MusicPlayer->stop();
            currentLevel = 5; // Pass the difficulty as a parameter
            Level *lvl6 = getCurrentLevel();

            lvl6->drawObstacles();
            lvl6->window->setCurrentLevel(currentLevel);
            lvl6->window->showFullScreen();
            lvl6->window->get_startmenu(this);
            lvl6->window->get_currentlevelindex(currentLevel);
        }
    }

    void StartMenu::on_pushButtonlevel7_clicked() {
        if (levels[6]->get_unlocked()) {
            hide();
            MusicPlayer->stop();
            currentLevel = 6; // Pass the difficulty as a parameter
            Level *lvl7 = getCurrentLevel();

            lvl7->drawObstacles();
            lvl7->window->setCurrentLevel(currentLevel);
            lvl7->window->showFullScreen();
    lvl7->window->get_startmenu(this);
    lvl7->window->get_currentlevelindex(currentLevel);
        }
    }

    void StartMenu::on_pushButtonlevel8_clicked() {
        if (levels[7]->get_unlocked()) {
            hide();
            MusicPlayer->stop();
            currentLevel = 7; // Pass the difficulty as a parameter
            Level *lvl8 = getCurrentLevel();

            lvl8->drawObstacles();
            lvl8->window->setCurrentLevel(currentLevel);
            lvl8->window->showFullScreen();
    lvl8->window->get_startmenu(this);
    lvl8->window->get_currentlevelindex(currentLevel);
        }
    }

    void StartMenu::on_pushButtonlevel9_clicked() {
        if (levels[8]->get_unlocked()) {
            hide();
            MusicPlayer->stop();
            currentLevel = 8; // Pass the difficulty as a parameter
            Level *lvl9 = getCurrentLevel();

            lvl9->drawObstacles();
            lvl9->window->setCurrentLevel(currentLevel);
            lvl9->window->showFullScreen();
    lvl9->window->get_startmenu(this);
    lvl9->window->get_currentlevelindex(currentLevel);
        }
    }

    void StartMenu::on_pushButtonlevel10_clicked() {
        if (levels[9]->get_unlocked()) {
            hide();
            MusicPlayer->stop();
            currentLevel = 9; // Pass the difficulty as a parameter
            Level *lvl10 = getCurrentLevel();

            lvl10->drawObstacles();
            lvl10->window->setCurrentLevel(currentLevel);
            lvl10->window->showFullScreen();
    lvl10->window->get_startmenu(this);
    lvl10->window->get_currentlevelindex(currentLevel);
        }
    }
    void StartMenu::setMusicPlayer(bool music) {
        // Instantiate a QMediaPlayer for music playback
        MusicPlayer = new QMediaPlayer;

        // Instantiate a QAudioOutput for sound output
        Speaker = new QAudioOutput;

        // Set the source URL for the music (adjust the path as needed)
        MusicPlayer->setSource(QUrl("qrc:/Resources/Audio/Main_Menu_Song(COD Mobile Season 9) .mp3"));

        // Set the audio output for the music player
        MusicPlayer->setAudioOutput(Speaker);

        // Set the volume level for the music (adjust as needed)
        Speaker->setVolume(20);

        // Set the music to loop indefinitely (-1 means infinite loops)
        MusicPlayer->setLoops(-1);

        // Check the 'music' flag to determine whether to play or stop the music
        if (music) {
            // If 'music' is true, play the music
            MusicPlayer->play();
        } else {
            // If 'music' is false, stop the music playback
            MusicPlayer->stop();
        }
    }

    void StartMenu::on_pushButtonQuit_clicked() {
        exit(1);
    }


    void StartMenu::on_pushButtonlevelCreateGame_clicked() {
// Call the createGameRequest function from the GameManager instance
        manager->createGameRequest();

    }


    void StartMenu::on_pushButtonlevelJoinGame_clicked() {
        QString lobbyId = ui->lineEditJoinGame->text();
        ui->lineEditJoinGame->clear();
        manager->joinLobbyRequest(lobbyId);
    }


    void StartMenu::renderer_unlocked() const {
        if (levels[1]->get_unlocked())
            ui->labellock_2->setVisible(0);
        if (levels[2]->get_unlocked())
            ui->labellock_3->setVisible(0);
        if (levels[3]->get_unlocked())
            ui->labellock_4->setVisible(0);
        if (levels[4]->get_unlocked())
            ui->labellock_5->setVisible(0);
        if (levels[5]->get_unlocked())
            ui->labellock_6->setVisible(0);
        if (levels[6]->get_unlocked())
            ui->labellock_7->setVisible(0);
        if (levels[7]->get_unlocked())
            ui->labellock_8->setVisible(0);
        if (levels[8]->get_unlocked())
            ui->labellock_9->setVisible(0);
        if (levels[9]->get_unlocked())
            ui->labellock_10->setVisible(0);
    }
}

