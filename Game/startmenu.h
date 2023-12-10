#ifndef STARTMENU_H
#define STARTMENU_H

#include <QDialog>
#include <QVector>
#include <vector>
#include "level.h"
class QMediaPlayer;
class QAudioOutput;
namespace Ui {
class StartMenu;
}

class StartMenu : public QDialog
{
    Q_OBJECT

public:
   explicit StartMenu(QWidget *parent = nullptr);
    int currentLevel;

    std::vector<Level*>& getLevels() { return levels; }
    void generateLevels();
    Level *getCurrentLevel();
    void setMusicPlayer(bool);
    ~StartMenu();

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

    Ui::StartMenu *ui;

    QMediaPlayer* MusicPlayer;

    QAudioOutput* Speaker;




};

#endif // STARTMENU_H
