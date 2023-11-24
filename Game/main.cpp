#include "mainwindow.h"
#include "level.h"
#include <QApplication>
#include <QVector>
#include <cmath>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

   /* QVector<Level> levels;
    int initialRocketCount = 5; // Adjust as needed

    // Initialize 20 levels with increasing difficulty using Fibonacci progression
    int fibPrev = 0, fibCurr = 1;
    for (int i = 0; i < 20; ++i) {
        int difficulty = fibCurr; // Use the Fibonacci number as difficulty
        Level level(i + 1, difficulty, initialRocketCount);
        levels.push_back(level);

        // Calculate the next Fibonacci number
        int fibNext = fibPrev + fibCurr;
        fibPrev = fibCurr;
        fibCurr = fibNext;
    }
        */
    // Now, you can use the 'levels' QVector across your game

    return a.exec();
}
