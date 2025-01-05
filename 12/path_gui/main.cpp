/* Polku
 *
 * Kuvaus:
 * The game Path has 4 green pawns at top and 4 at bot. In the middle of
 * them there are 4 empty spots that can be used to move the pawns to.
 * When you start the game the buttons will be enabled for moving, the
 * timer starts to run and moves will start to be counted. The idea of the
 * game is to move the green pawns to the original places of the red pawns
 * and the other way around. Pawns cannot be moved over each other.
 *
 * The main coding is happening in mainwindow.cpp file, but it uses the
 * class Gameboard to create grid, move pawns, tell which type slot is
 * is in that Point and if the game is completed.
 *
 *
 * Name: Tuomas Seitajärvi
 * Student ID: 150470483
 * Git account: cgtuse ( Git-repositorion hakemistonimi. )
 * E-Mail: tuomas.seitajarvi@gmail.com
 *
 * Additions:
 *
 * The code uses 3 different .png images, which have been made by my friend
 * Harri Hanhisuanto. The theme of the board is made from the game Dota 2
 * as are the characters that are RED and GREEN pawns. The green one is
 * a character called "Treant Protector" and the red one is "Shadow Fiend".
 *
 *
 * The code has an example_play nappi, which can be used to show the player
 * how the game is played. It completes the game in 33 moves.
 *
 * The game changes backgrounds when the game is over (pawns have been moved
 * to the right places). The winning background is orange, losing is red and
 * the example is green.
 *
 * I have made it so you don't need to win the game with 31 moves, but it will
 * still count how close you came. This gives the opportunity to fail and
 * generate a system where you can have points.
 *
 * I tought that the pause button was a necessary part of the game and made it with
 * start, reset, rules and close.
 * */

#include "mainwindow.hh"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
