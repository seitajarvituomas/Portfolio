/* Mysteerimatto
 *
 * Kuvaus:
 *
 * Ohjelma toteuttaa mysteerimaton, josta voi arvata
 * neliön muotoisia kuvioita 4 merkin syötteenä.
 * Matto koostuu erivärisistä ruuduista ja sen on oltava
 * vähintään 2x2 ruutua, koska tällaisia kuvioita
 * pelissä etsitään. Aluksi ohjelma kysyy maton pituuden.
 * Sen jälkeen ohjelma kysyy tehdäänkö matto randomilla
 * vai syötteellä. randomilla pitää syöttää vielä siemenluku,
 * joka on väliltä [1, 20]. Syötteellä syötetään aiemmin annettu
 * maton pituuden verran ruutujen värejä. Jos kaikki on kunnossa
 * (värit ja syötteiden pituudet) tulostetaan matto ja siitä voi
 * alkaa kysyä kuvioita.
 *
 * Nimi: Tuomas Seitajärvi
 * Opiskelijanumero: 150470483
 * Käyttäjätunnus: cgtuse
 * E-Mail: tuomas.seitajarvi@tuni.fi
 * */

#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <random>

using namespace std;

enum Color {RED, GREEN, BLUE, YELLOW, WHITE, NUMBER_OF_COLORS};

struct ColorInfo {
    // char color on kirjain mikä vastaa
    // Color color_codessa olevaa väriä
    char color;
    Color color_code;
};

const vector<ColorInfo> COLORS = {
    // värit ja niiden kirjaimet
    {'R' , RED},
    {'G' , GREEN},
    {'B' , BLUE},
    {'Y' , YELLOW},
    {'W' , WHITE},
    {5, NUMBER_OF_COLORS}
};

bool is_colors_length_correct(string colors, int length_of_carpet) {
    // Palauttaa false, jos pituus*leveys ei ole yhtä pitkä kuin
    // annettujen merkkien pituus. Muuten palauttaa true.

    // param colors, string, värejä annettuna
    // param length_of_carpet, int, leveys kertaa pituus
    // length, colors parametrin pituus
    string::size_type length = 0;
    length = colors.length();

    if (static_cast<int>(length) != length_of_carpet) {
        cout << "Error: Wrong amount of colors." << endl;
        return false;
    }
    return true;
}

bool is_valid_color(const string& play) {
    // Palauttaa false ja lopettaa loopin, jos
    // ei löydä väriä COLORS:sta. Muuten palauttaa
    // true.

    //param play, string, syötteestä otettuja värejä
    for (const char& color : play) {
        bool found = false;
        char uppercasecolor = toupper(color);

        for (const ColorInfo& colorInfo : COLORS) {
            if (colorInfo.color == uppercasecolor) {
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Error: Unknown color." << endl;
            return false;
        }
    }
    return true;
}

vector<vector<Color>> initialize_board(int width, int height, const string& colors) {
    // Inputilla tehty board. Käy läpi height ja width verran lautaa ja
    // muuttaa jokaisen kirjaimen isoksi. lisää jokaisen colors inputissa
    // olevan kirjaimen yksitellen boardiin ja palauttaa sitten sen.

    //param width, int, leveys
    //param hegith, int, korkeus
    //param colors, string, annetut värit lautaan

    vector<vector<Color>> board(height, vector<Color>(width));

    int index = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            char color = toupper(colors.at(index));

            for (const ColorInfo& colorInfo : COLORS) {
                if (colorInfo.color == color) {
                    board.at(i).at(j) = colorInfo.color_code;

                    break;
                }
            }
            ++index;
        }
    }

    return board;
}

vector<vector<Color>> randomize_board(int width, int height, int seed) {
    // Randomisoinnillta toimiva laudan teko funktio. Käyttää <random>
    // kirjastoa tekemään random kirjaimia Color luokasta random_index
    // avulla ja looppaamalla laittaa leveyden ja pituuden avulla kaikkiin
    // paikkoihin jonkun värin.

    //param width, int, leveys
    //param hegith, int, korkeus
    //param seed, int, siemenluku väliltä [1,20]
    default_random_engine gen(seed);
    uniform_int_distribution<int> distr(0, NUMBER_OF_COLORS -1);

    vector<vector<Color>> board(height, vector<Color>(width));

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            int random_index = distr(gen);
            Color random_color = static_cast<Color>(random_index);
            board.at(i).at(j) = random_color;
        }
    }

    return board;
}

void print_board(const vector<vector<Color>>& board) {
    // Printtaa värejä laudasta ja jokaisen jälkeen välin.

    //param board, vektori, jossa alkioina vektoreita, pelilauta

    for (const auto& row : board) {
        for (const auto& color : row) {
            for (const ColorInfo& colorInfo : COLORS) {
                if (colorInfo.color_code == color) {
                    cout << colorInfo.color << " ";
                    break;
                }
            }
        }
        cout << endl;
    }
}

Color getColor(char color) {
    // Palauttaa värin color_coden ja NUMBER_OF_COLORS.

    // param color, char, yksi väri
    for (const ColorInfo& color_info : COLORS) {
        if (color_info.color == color) {
            return color_info.color_code;
        }
    }
    return NUMBER_OF_COLORS;
}

void find_pattern(const vector<vector<Color>> board, const string& pattern) {
    // Löytää kuviot käymällä läpi jokaisen kirjaimen onko se missä .at funktion
    // avulla. Jos löytää tulostaa siitä viestin, ja lisää yhden löydön. Lopuksi
    // kertoo montako paria löydettiin ja mistä.

    // param pattern, string, kuvio väreistä
    // param board, vektori, jossa alkioina vektoreita, pelilauta
    // width, int, leveys
    // height, int, korkeus
    int height = board.size();
    int width = board.at(0).size();

    int matches = 0;

    for (int i = 0; i < height - 1; ++i) {
        for (int j = 0; j < width - 1; ++j) {
            if (board.at(i).at(j) == getColor(pattern.at(0)) &&
                board.at(i).at(j+1) == getColor(pattern.at(1)) &&
                board.at(i+1).at(j) == getColor(pattern.at(2)) &&
                board.at(i+1).at(j+1) == getColor(pattern.at(3))) {
                cout << "- Found at (" << j+1 << ", " << i+1 << ")" << endl;
                matches++;
            }
        }
    }
    cout << "= Matches found: " << matches << endl;
}


int main()
{
    int width = 0;
    int height = 0;
    cout << "Enter carpet's width and height: ";
    cin >> width;
    cin >> height;

    if (width < 2 || height < 2) {
        cout << "Error: Carpet cannot be smaller than pattern.";
        return EXIT_FAILURE;
    }

    string option;
    bool valid_input = false;
    vector<vector<Color>> board;

    while (!valid_input) {

        cout << "Select start (R for random, I for input): ";
        cin >> option;

        for (char& o : option) {
            o = toupper(o);
        }

        if (option == "I") {
            string colors = "";
            cout << "Input: ";
            cin >> colors;

            if (is_colors_length_correct(colors, width*height) == true) {
                if (is_valid_color(colors)) {
                    board = initialize_board(width, height, colors);
                    valid_input = true;
                }
            }
        }

        if (option == "R") {
            valid_input = true;
            int seed = 0;
            bool valid_input2 = false;

            while (!valid_input2) {
                cout << "Enter seed value: " ;
                cin >> seed;

                if (seed > 0 && seed <= 20) {
                    valid_input2 = true;
                    board = randomize_board(width, height, seed);
                } else {
                    cout << "Error: Wrong seed value." << endl;
                }
            }
        }
    }

    print_board(board);

    while (true) {
        string play;
        cout << "Enter 4 colors, or q to quit: ";
        cin >> play;

        //tekee merkeistä isoja
        for (char& color : play) {
            color = toupper(color);
        }

        if (play == "Q") {
            return EXIT_SUCCESS;
        }

        //Käy läpi virhetilanteet
        if (is_colors_length_correct(play, 4)) {
            if (is_valid_color(play)) {
                find_pattern(board, play);

            }
        }
    }
}
