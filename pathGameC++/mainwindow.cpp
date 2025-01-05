/* Name: Tuomas Seitajärvi
 * Student ID: 150470483
 * Git account: cgtuse ( Git-repositorion hakemistonimi. )
 * E-Mail: tuomas.seitajarvi@gmail.com
 *
 * Train of thought when making the game
 *
 * When the game started I got two good ideas. To use my connections
 * and make the board nice looking (Graphic designer 1st year student friend
 * from Lahti who made me images to use to make the game pretty).
 * The other idea was to make a chess like moving mechanic. I used all of
 * the week 12 examples and combined them so that there are images,
 * graphicsview and many QPushButtons. I started to use the pictures and link
 * them to the game board and then made the moving function with click button,
 * choose location, mechanic. Then i created the buttons that help the game
 * (start,reset,rules,pause,close). After that i made the example play by
 * trying out to win and failing. Then I added the final pictures and
 * background to game ending possibilities.
 *
 */

#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    //Creates the gameboard, buttons, labels, pawns and the timer
    //connects timer (QTimer) and the timeout function that
    //sends timeout signals to the timer

    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene_ = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene_);

    game_board = new GameBoard();
    create_buttons();
    create_board();
    create_pawns();

    //The game timer
    game_timer = new QTimer(this);
    connect(game_timer, &QTimer::timeout, this, &MainWindow::timeout);

    //The timer used in example play
    pawn_move_timer = new QTimer(this);
}

MainWindow::~MainWindow()
{
    for (auto& row : pawn_buttons) {
        for (auto& button : row) {
            button->setIcon(QIcon());
            delete button;
        }
        row.clear();
    }
    pawn_buttons.clear();

    for (auto& row : pawn_positions) {
        row.clear();
    }

    for (auto& button : buttons) {
        delete button;
    }

    buttons.clear();

    delete game_timer;
    delete pawn_move_timer;
    delete scene_;
    delete game_board;

    delete ui;
}

void MainWindow::create_board()
{
    // Uses a .png image set on a graphicsview as a board

    // Defining where the images can be found and what kind of images they are
    const std::string PREFIX(":/");
    const std::string SUFFIX(".png");

    std::string board_file = PREFIX + "game_board" + SUFFIX;
    QPixmap board_pixmap(QString::fromStdString(board_file));

    qreal scaleFactor = 0.271; // The scaling value to scale to
                               //GraphicsView (tested multiple)

    // Scaling the pixmap
    QPixmap scaled_board_pixmap = board_pixmap
            .scaled(board_pixmap.width() * scaleFactor,
                    board_pixmap.height() * scaleFactor,
                    Qt::KeepAspectRatio);

    // Clears the scene and adds the scaled pixmap
    scene_->clear();
    scene_->addPixmap(scaled_board_pixmap);

    // Sets that you can't pause or reset
    // if the start button hasn't been clicked
    pause_button->setDisabled(true);
    reset_button->setDisabled(true);
}

void MainWindow::create_pawns()
{
    // Creates the pawns, links them to the board, sets them to the
    // gameboard .png image and connects them to handle_pawn_clicked
    // what uses gameboard to do all pawns moving

    // Defining the other 2 pictures made to pixmaps
    const std::string PREFIX(":/");
    const std::string SUFFIX(".png");

    std::string red_button_file = PREFIX + "red_button" + SUFFIX;
    std::string green_button_file = PREFIX + "green_button" + SUFFIX;

    QPixmap red_button_pixmap(QString::fromStdString(red_button_file));
    QPixmap green_button_pixmap(QString::fromStdString(green_button_file));

    // Resizing the vectors
    pawn_buttons.resize(COLUMS, std::vector<QPushButton*>(ROWS));
    pawn_positions.resize(COLUMS, std::vector<Point>(ROWS));

    // Searching in a loop the ROWS and COLUMS (gameboard.hh) and creating new
    // QPushButtons for every pawn
    for (int row = 0; row < static_cast<int>(ROWS); row++) {
        for (int col = 0; col < static_cast<int>(COLUMS); col++) {
            QPushButton* button = new QPushButton(this);

            // Finds what the slot is in that ROW and COLUMN
            // (uses init_grid in gameboard to do so)
            Slot_type slot = game_board->which_slot(Point{col, row});

            // Set the icon based on slot and
            // geomatry scaled to the game_board.png
            if (slot == RED) {
                button->setIcon(red_button_pixmap);
                button->setGeometry(pawn_start_x + col *
                pawn_spacing_x, pawn_start_y + row * pawn_spacing_y, 100, 100);
            } else if (slot == GREEN) {
                button->setIcon(green_button_pixmap);
                button->setGeometry(pawn_start_x + col *
                pawn_spacing_x, pawn_start_y + row * pawn_spacing_y, 100, 100);
            } else if (slot == EMPTY) {
                // Set a transparent icon for empty spots
                QIcon transparent_icon;
                button->setIcon(transparent_icon);
                button->setGeometry(pawn_start_x + col *
                pawn_spacing_x, pawn_start_y + row * pawn_spacing_y, 100, 100);
            }

            // Sets the style so that if it is not a green
            // or red button it cannot be seen.
            button->setStyleSheet("background-color: "
            "rgba(0,0,0,0); border-radius: 50%;");
            button->setIconSize(QSize(100, 100));
            button->show();

            // Disables it so if start isn't pressed, you can't move the button
            button->setDisabled(true);

            // Settin buttons and their positions to vectors by COLUMS and ROWS
            pawn_buttons[col][row] = button;
            pawn_positions[col][row] = Point{col, row};

            // Connects all buttons to handle_pawn_clicked() what moves them
            connect(button, &QPushButton::clicked,
                    this, &MainWindow::handle_pawn_clicked);
        }
    }
}

void MainWindow::create_buttons()
{
    // Creates all of the other buttons (no pawns)

    start_button = new QPushButton("Start", this);
    rules_button = new QPushButton("Rules", this);
    example_play_button = new QPushButton("Example game", this);
    pause_button = new QPushButton("Pause", this);
    reset_button = new QPushButton("Reset", this);
    close_button = new QPushButton("Close game", this);

    // Adds them to buttonsLayout
    ui->buttonsLayout->addWidget(start_button);
    ui->buttonsLayout->addWidget(rules_button);
    ui->buttonsLayout->addWidget(example_play_button);
    ui->buttonsLayout->addWidget(pause_button);
    ui->buttonsLayout->addWidget(reset_button);
    ui->buttonsLayout->addWidget(close_button);

    // Connects them to their different clicked functions
    connect(start_button, &QPushButton::clicked,
            this, &MainWindow::handle_start_button_clicked);
    connect(rules_button, &QPushButton::clicked,
            this, &MainWindow::handle_rules_button_clicked);
    connect(example_play_button, &QPushButton::clicked,
            this, &MainWindow::example_clicked);
    connect(pause_button, &QPushButton::clicked,
            this, &MainWindow::handle_pause_button_clicked);
    connect(reset_button, &QPushButton::clicked,
            this, &MainWindow::handle_reset_button_clicked);
    connect(close_button, &QPushButton::clicked,
            this, &MainWindow::handle_close_button_clicked);

    // Adds them to a vector to set their styles the same
    buttons.push_back(start_button);
    buttons.push_back(rules_button);
    buttons.push_back(example_play_button);
    buttons.push_back(pause_button);
    buttons.push_back(reset_button);
    buttons.push_back(close_button);

    for (auto& button : buttons) {
        button->setStyleSheet("background-color: orange");
    }
    ui->moves_label->setText(QString::number(moves_used));
}

void MainWindow::handle_pawn_clicked()
{
    // Takes control of the clicked button
    QPushButton* clicked_button = qobject_cast<QPushButton*>(sender());
    // Initializes the clicked position
    Point clicked_position;

    // Find the clicked button's position in the game board
    for (int row = 0; row < static_cast<int>(ROWS); row++) {
        for (int col = 0; col < static_cast<int>(COLUMS); col++) {
            QPushButton* current_button = pawn_buttons[col][row];
            if (current_button == clicked_button) {
                // Sets the clicked position according to COLUMS  and ROWS
                clicked_position = Point{col, row};

                //Figures which type is the slot
                Slot_type slot = game_board->which_slot(clicked_position);

                // First step: Select a pawn
                // (only can move buttons that are RED or GREEN)
                if (slot == RED || slot == GREEN) {

                    if (!pawn_selected_) {

                        //Sets the boarders to blue (get the chess vibe)
                        clicked_button->setStyleSheet("background-color:"
                        " blue; border-radius: 75%;");

                        // Selects the pawns position that is going to be moved
                        selected_pawn_position_ = clicked_position;

                        // Sets the pawn selected
                        pawn_selected_ = true;

                        // Deselect if the same pawn is clicked again
                    } else if (selected_pawn_position_ == clicked_position) {

                        clicked_button->setStyleSheet("background-color:"
                        " rgba(0,0,0,0); border-radius: 75%;");
                        pawn_selected_ = false;

                        // Null the position
                        selected_pawn_position_ = Point{-1, -1};
                    }

                    // Second step: Select an empty spot and move the pawn
                } else if (pawn_selected_) {

                    // Use the move function to move the pawns and set slots
                    bool move_successful = game_board->move
                        (selected_pawn_position_, clicked_position);

                    if (move_successful) {
                        succesfully_move(selected_pawn_position_, clicked_position);

                        pawn_selected_ = false;
                        selected_pawn_position_ = Point{-1, -1};

                        // Reset background style to transparent for all buttons
                        for (int row = 0; row < static_cast<int>(ROWS); row++) {
                            for (int col = 0; col < static_cast<int>(COLUMS); col++) {
                                pawn_buttons[col][row]->setStyleSheet
                                ("background-color: rgba(0,0,0,0); border-radius: 75%;");
                            }
                        }
                    } else {
                    ui->move_success_label->setText("Move unsuccessful");
                    }

                    // Checks if the pawns are at right place
                    if (game_board->is_game_over()) {
                        game_timer->stop();
                        pause_button->setDisabled(true);
                        disable_pawns();
                        if (moves_used > 31) {
                            ui->move_success_label->setText("You lost!");
                            ui->centralWidget->setStyleSheet("background: red");
                        } else {
                             ui->move_success_label->setText("You won!");
                             ui->centralWidget->setStyleSheet("background: orange");
                        }
                    }
                }
            }
        }
    }
}

void MainWindow::handle_start_button_clicked()
{
    // If the game hasn't started starts the timer and enables pawns
    if (!has_started) {
        game_timer->start(1000);

        for (auto& row : pawn_buttons) {
            for (auto& button : row) {
                button->setEnabled(1);
            }
        }
        // Enables also pause and reset button and disables start button
        pause_button->setEnabled(1);
        reset_button->setEnabled(1);
        example_play_button->setDisabled(true);
        start_button->setDisabled(true);
        has_started = true;
    }
}

void MainWindow::handle_rules_button_clicked()
{
    // If rules are not open sets the rules to be visible
    // and rules_open true
    if (!rules_open) {

        ui->textBrowserRules->setText("Move green pawns "
                                      "where red pawns "
                                      "are in 31 moves or "
                                      "less. You can't move "
                                      "over other pawns.");
        ui->textBrowserRules->show();
        rules_open = true;
        return;
    }
    // Sets the rules to nothing and rules_open false
    ui->textBrowserRules->setText("");
    rules_open = false;
}

void MainWindow::handle_pause_button_clicked()
{
    // If the game isn't paused pauses it
    if (!paused) {

        // Stops the timer
        game_timer->stop();
        ui->lcdNumberSec->display(seconds);
        ui->lcdNumberMin->display(minutes);

        // disables pawns
        disable_pawns();

        // Turns paused true and differs the pause button
        paused = true;
        pause_button->setText("Unpause");
        return;
    }

    // Sets timer, enables the pawns, sets paused to false
    game_timer->start(1000);
    ui->lcdNumberSec->display(seconds);
    ui->lcdNumberMin->display(minutes);
    disable_pawns();
    paused = false;
    pause_button->setText("Pause");
}

void MainWindow::handle_reset_button_clicked()
{
    // Stop the timer, set seconds, minutes, and moves to zero
    game_timer->stop();
    seconds = 0;
    minutes = 0;

    moves_used = 0;
    ui->moves_label->setText(QString::number(moves_used));

    ui->lcdNumberSec->display(seconds);
    ui->lcdNumberMin->display(minutes);

    // Clear both of the vectors (buttons and their positions)
    for (auto& row : pawn_buttons) {
        for (auto& button : row) {
            button->setIcon(QIcon());
            delete button;
        }
        row.clear();
    }
    pawn_buttons.clear();

    for (auto& row : pawn_positions) {
        row.clear();
    }
    pawn_positions.clear();

    // Deletes the old game_board and creates a new one and
    // calls the create_pawns() function
    delete game_board;
    game_board = new GameBoard();
    create_pawns();

    // Reset other variables and UI elements as needed
    has_started = false;
    paused = false;
    buttons_disabled = false;

    start_button->setEnabled(true);
    pause_button->setDisabled(true);
    reset_button->setDisabled(true);
    example_play_button->setEnabled(true);
    ui->move_success_label->setText("");
    ui->centralWidget->setStyleSheet("background-color: "
    "qlineargradient(spread:pad, x1:0.931, y1:0.125, x2:0.164, y2:0.863636, stop:0 "
    "rgba(0, 137, 7, 255), stop:1 rgba(152, 4, 4, 255));");
}

void MainWindow::handle_close_button_clicked()
{
    close();
}

void MainWindow::example_clicked()
{
    // If the player wants a example how to play this function
    // shows it. It connects thr pawn_timer to execute_example move
    // and starts the timer

    // Index needed for going threw the points on where to put the pawns
    example_index = 0;

    // Disables certain UI elements as needed
    pawn_move_timer->stop();
    pause_button->setDisabled(true);
    rules_button->setDisabled(true);
    start_button->setDisabled(true);
    reset_button->setDisabled(true);
    example_play_button->setDisabled(true);
    ui->move_success_label->setText("");

    //Enables the buttons to allow moving
    for (auto& row : pawn_buttons) {
        for (auto& button : row) {
            button->setEnabled(true);
        }
    }

    // Starts the example
    pawn_move_timer->start(1000);
    connect(pawn_move_timer, &QTimer::timeout,
            this , &MainWindow::execute_example_move);

}

void MainWindow::execute_example_move()
{
    // Uses succesfull move, indexing and the points in the below vector
    // to move the pawns
    std::vector<std::pair<Point, Point>> example_moves = {

        {Point{1, 4}, Point{2, 2}}, {Point{1, 0}, Point{1, 4}},

        {Point{0, 0}, Point{1, 3}}, {Point{2, 2}, Point{0, 0}},

        {Point{1, 3}, Point{2, 2}}, {Point{1, 4}, Point{1, 0}},

        {Point{0, 4}, Point{1, 1}}, {Point{2, 2}, Point{0, 4}},

        {Point{1, 1}, Point{2, 2}}, {Point{1, 0}, Point{1, 4}},

        {Point{2, 0}, Point{1, 3}}, {Point{3, 0}, Point{1, 2}},

        {Point{0, 0}, Point{3, 0}}, {Point{1, 2}, Point{0, 0}},

        {Point{2, 2}, Point{2, 0}}, {Point{1, 3}, Point{2, 2}},

        {Point{1, 4}, Point{1, 0}}, {Point{2, 4}, Point{1, 1}},

        {Point{3, 4}, Point{1, 3}}, {Point{0, 4}, Point{3, 4}},

        {Point{1, 3}, Point{0, 4}}, {Point{2, 2}, Point{2, 4}},

        {Point{1, 1}, Point{2, 2}}, {Point{1, 0}, Point{1, 4}},

        {Point{0, 0}, Point{1, 3}}, {Point{2, 2}, Point{0, 0}},

        {Point{1, 3}, Point{2, 2}}, {Point{1, 4}, Point{1, 0}},

        {Point{0, 4}, Point{1, 1}}, {Point{2, 2}, Point{0, 4}},

        {Point{1, 1}, Point{2, 2}}, {Point{1, 0}, Point{1, 4}},

        {Point{2, 2}, Point{1, 0}}

    };

    // Goes threw the vector with increasing vector and condition
    if (example_index >= 0 && example_index < static_cast<int>(example_moves.size())) {

        // Sets from where to go
        Point from = example_moves[example_index].first;
        Point to = example_moves[example_index].second;

        //uses Gameboard function move to move the pawn and set the slots
        bool move_successful = game_board->move(from, to);

        if (move_successful) {
            // function below used to move pawns
            succesfully_move(from, to);
        }
        // Allow moving on to next points
        example_index ++;

        // Allows the example to end
        if (example_index == static_cast<int>(example_moves.size())) {
            pawn_move_timer->stop();
            reset_button->setEnabled(true);
            rules_button->setEnabled(true);
            disable_pawns();
            ui->move_success_label->setText("Can you do better?");
            ui->centralWidget->setStyleSheet("background: green");
        }
    }
}

void MainWindow::succesfully_move(Point& from, Point& to)
{
    // Used on example and manual moving to count moves
    // and move pixmaps and icons

    moves_used += 1;
    // Update the moves shown
    ui->moves_label->setText(QString::number(moves_used));
    ui->move_success_label->setText("");

    // Move the icon of the button if move succesful
    QPixmap pixmap = pawn_buttons[from.x]
    [from.y]->icon().pixmap(QSize(100, 100));

    pawn_buttons[to.x][to.y]->setIcon(pixmap);

    // Clear the icon of the source button
    pawn_buttons[from.x]
    [from.y]->setIcon(QIcon());
}

void MainWindow::disable_pawns()
{
    // Goes threw buttons and either enables or disables them
    for (auto& row : pawn_buttons) {
        for (auto& button : row) {
            if (!buttons_disabled) {
                button->setDisabled(true);
            } else {
                button->setEnabled(true);
            }
        }
    }
    // Sets the bools according to present state
    if (buttons_disabled) {
        buttons_disabled = false;
    } else {
        buttons_disabled = true;
    }
}

void MainWindow::timeout()
{
    // Sets timeout signals to the timer
    seconds++;
    if (seconds >= 60) {
        seconds = 0;
        minutes++;
        if (minutes >= 60) {
            minutes = 0;
        }
    }

    ui->lcdNumberSec->display(seconds);
    ui->lcdNumberMin->display(minutes);
}




