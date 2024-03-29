#ifndef STARTMENU_H
#define STARTMENU_H

#include <QDialog>
#include <QVector>
#include <vector>
#include "level.h"
#include "gamemanager.h"
#include "chatlobbywindow.h"

class QMediaPlayer;
class QAudioOutput;
namespace Ui {
class StartMenu;
}

class StartMenu : public QDialog
{
    Q_OBJECT

public:
   explicit StartMenu(QWidget *parent = nullptr , GameManager* manager = nullptr);
    int currentLevel;

    std::vector<Level*>& getLevels() { return levels; }
    void generateLevels();
    void openChatLobbyWindow();
    Level *getCurrentLevel();
    void setMusicPlayer(bool);
    ~StartMenu();
    void renderer_unlocked() const;
    void renderer_stars();
    Ui::StartMenu *ui;

public slots:
    void on_pushButtonlevel1_clicked();

    void on_pushButtonlevel2_clicked();

    void on_pushButtonlevel3_clicked();

    void on_pushButtonlevel4_clicked();

    void on_pushButtonlevel5_clicked();

    void on_pushButtonlevel6_clicked();

    void on_pushButtonlevel7_clicked();

    void on_pushButtonlevel8_clicked();

    void on_pushButtonlevel9_clicked();

    void on_pushButtonlevel10_clicked();

private slots:
    void on_pushButtonQuit_clicked();

    void on_pushButtonlevelCreateGame_clicked();

    void on_pushButtonlevelJoinGame_clicked();

private:
    std::vector<Level*> levels;

    GameManager* manager;

    QMediaPlayer* MusicPlayer;

    QAudioOutput* Speaker;




};

#endif // STARTMENU_H
