#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPushButton>
#include <QLabel>
#include <QTimer>
#include <vector>
#include <QTextBrowser>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Draws the board
    void create_board();

    // Creates pawns
    void create_pawns();

    // Creates buttons like start and reset and
    // moves amount label
    void create_buttons();

    //Handles all moves done by pawns also using
    // move() from Gameboard
    void handle_pawn_clicked();

    //All the buttons functions when clicked
    void handle_start_button_clicked();

    void handle_reset_button_clicked();

    void handle_pause_button_clicked();

    void handle_rules_button_clicked();

    void handle_close_button_clicked();

    //Disables pawns (exp. when paused)
    void disable_pawns();

    //Sends time signals for the timer
    void timeout();

    void example_clicked();

    void execute_example_move();

    void succesfully_move(Point& from, Point& to);

private:

    Ui::MainWindow *ui;         //Ui that has some empty widgets where to code actions
    QGraphicsScene* scene_;     //The QGraphicsScene where the board will go
    GameBoard* game_board;      //The new Gameboard class what can be used to see slots
    QTimer* game_timer;              //Timer for the game

    std::vector<std::vector<QPushButton*>> pawn_buttons;
    std::vector<std::vector<Point>> pawn_positions;

    //Positions for the pawns
    int pawn_spacing_x = 136;
    int pawn_spacing_y = 105;
    int pawn_start_x = 171;
    int pawn_start_y= 80;

    bool pawn_selected_ = false;            //If pawn selected can choose another to move to
    Point selected_pawn_position_;  //Pawn what is going to move position
    Point selected_destination_;    //The destination where the pawn moves

    QPushButton* start_button;
    QPushButton* rules_button;
    QPushButton* example_play_button;
    QPushButton* pause_button;
    QPushButton* reset_button;
    QPushButton* close_button;

    //Vector where all pawns are to adjust how they look
    std::vector<QPushButton*> buttons;

    int moves_used = 0;
    int minutes = 0;
    int seconds = 0;

    //Bools to keep track of things done with buttons
    bool has_started = false;
    bool rules_open = false;
    bool paused = false;
    bool buttons_disabled = false;

    QTimer* pawn_move_timer;
    int example_index;

};
#endif // MAINWINDOW_HH
