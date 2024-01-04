
# Stellar Strike
![version](https://img.shields.io/badge/version-1.0.0-blue)
[![PHP Version Require](http://poser.pugx.org/badges/poser/require/php)](https://packagist.org/packages/badges/poser)
![Qt](https://img.shields.io/badge/Qt-6.5.3-green)
![Python](https://img.shields.io/badge/Python-3.8-blue)
![OpenCV](https://img.shields.io/badge/OpenCV-4.5.3-green)
![Mediapipe](https://img.shields.io/badge/Mediapipe-0.8.7.1-orange)
![Autopy](https://img.shields.io/badge/Autopy-4.0.0-red)

Stellar Strike is a real-time multiplayer rocket shooting game developed using the Qt framework. It features a physics world with realistic trajectories, gravity, bouncing, and friction. The game also includes an AI mode that uses computer vision to allow you to play the game using hand gestures.

## Features

- **Real-Time Multiplayer Battles**: Engage in epic multiplayer battles where rockets become the pixels of a dynamic canvas, painted with the chaos of real-time gaming.
- **Physics World**: Experience a full-on physics world with all the physics thingies like trajectories, gravity bouncing, and friction.
- **AI Mode**: Run `handTracking.py` to make the game playable using computer vision and hands.
- **Customizable Rockets**: Customize your rockets like a digital Picasso. Different skins and attributes let you express your inner code-artist, making each rocket launch a masterpiece.
- **Score Tracking**: The built-in scoring system is your scoreboard in the symphony of chaos. Track your rocket hits and achievements like a virtuoso conductor leading a cosmic orchestra.
- **Progress Saving**: The game saves your progress as you advance through the levels.
- **10 Levels with Incremental Difficulty**: The game features 10 levels with increasing difficulty to challenge your rocket shooting skills.
- **Multiplayer Chat and Lobby**: Connect with friends using the provided IP/Hostname and port. Engage in exciting battles and compete for the highest score.
- **Lovely UI**: The game features a user-friendly interface that is intuitive and easy to navigate.

## Game Trailer

A full developed trailer of the game is available.
[Game Trailer.mp4](Game%2FGame%20Trailer.mp4)
## Executable

The game executable is available in the folder `Executable` [Game.exe](Executable%2FGame.exe).

## Requirements
![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=c%2B%2B&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=flat-square&logo=python&logoColor=white)
![PHP](https://img.shields.io/badge/PHP-777BB4?style=flat-square&logo=php&logoColor=white)
![Qt](https://img.shields.io/badge/Qt-41CD52?style=flat-square&logo=qt&logoColor=white)
![OpenCV](https://img.shields.io/badge/OpenCV-5C3EE8?style=flat-square&logo=opencv&logoColor=white)
![MediaPipe](https://img.shields.io/badge/MediaPipe-FF6347?style=flat-square&logo=mediapipe&logoColor=white)
![AutoPy](https://img.shields.io/badge/AutoPy-3776AB?style=flat-square&logo=python&logoColor=white)

Following modules need to be installed for the AI Mode to work properly:

### OpenCV

OpenCV is a huge open-source library for computer vision, machine learning, and image processing. OpenCV supports a wide variety of programming languages like Python, C++, Java, etc. It can process images and videos to identify objects, faces, or even the handwriting of a human.

```bash
pip install opencv-python
```

### Mediapipe

MediaPipe is a framework for building multimodal (eg. video, audio, any time series data), cross platform (i.e Android, iOS, web, edge devices) applied ML pipelines.

```bash
pip install mediapipe
```

### Autopy

AutoPy is a simple, cross-platform GUI automation library for Python. It includes functions for controlling the keyboard and mouse, finding colors and bitmaps on-screen, and displaying alerts.

```bash
pip install autopy
```

## Important Note

This project requires Python 3.8 due to dependency issues. If you have a newer version of Python installed, you will need to downgrade to Python 3.8. You can download Python 3.8 from [here](https://www.python.org/downloads/release/python-380/).

## Server Setup

The server for the game is written in PHP and is located in the `index.php` file. To set up the server, follow these steps:

1. Navigate to the server folder.
2. Run `composer install` to install the necessary dependencies.
3. Run the server on Apache or a similar server.

To run the multiplayer mode, you will need to change the server address in the `main.cpp` file:

```cpp
webSocketHandler.connectToServer("ws://your-server-address:8585");
```

Replace `your-server-address` with the address of your server.


## Contributors

- [Ramy Shehata](https://github.com/GM-Sniper)
- [Ahmed ElShireef](https://github.com/Ahmed1262005)
- [Eman Abdelhady](https://github.com/emanabdelhad-y)
- [Seif ElAnsary](https://github.com/MrSykoPath)

Contributions are welcome! Feel free to open issues or submit pull requests.

1. Fork the project.
2. Create your feature branch (`git checkout -b feature/YourFeature`).
3. Commit your changes (`git commit -m 'Add YourFeature'`).
4. Push to the branch (`git push origin feature/YourFeature`).
5. Open a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
