/* Library
 *
 * Kuvaus:
 * Tämä ohjela kysyy tiedoston, jonka jälkeen se rupeaa avaamaan
 * sitä rivi riviltä. Ohjelma hajottaa syötteen osiin ja tarkastaa,
 * että annetussa tiedostossa joka rivillä on 4 stringiä eroteltuna
 * ';' merkillä. Ohjelma tallentaa tiedot saver funktiolla struct Book
 * tietotyyppiin ja class Library tietotyyppiin. Ohjelma sitten kyselee,
 * mitä komentoja halutaan käyttää. vaihtoehtoja on libraries, material,
 * books, reservable, loanable ja quit, joka lopettaa ohjelman. Eri komennoilla
 * voidaan käydä läpi kirjastossa olevien kirjojen tilaa, ovatko ne lainattavissa,
 * vaiko eivät ja löytyykö niitä kirjastoista.
 *
 * Ohjelman kirjoittaja
 * Nimi: Tuomas Seitajärvi
 * Opiskelijanumero: 150470483
 * Käyttäjätunnus: cgtuse ( Git-repositorion hakemistonimi. )
 * E-Mail: tuomas.seitajarvi@tuni.fi
 *
 * */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "library.hh"
#include <algorithm>

using namespace std;

vector<string> split(const string& s, const char delimiter, bool ignore_empty = false){
    // Aikaisemmassa tehtävässä annettu funktio, joka katsoo läpi syötteen ja laittaa sen muuttujat
    // vektoriin, jos niitä löytyy annetulla merkillä eristettynä toisistaan.

    //returns, vector<string>, vektorin täynnä syötteestä paloiteltuja string muuttujia.
    //param s, string, annettu rivi
    //param delimiter, annettu merkki millä muuttujat erottaa
    //param ignore_empty, bool, tieto siitä jättääkö funktio huomioitta välit

    //tmp, string, uusi pätkä mistä lähteä etsimään muuttujia
    //next_part, string, uusi muuttuja vektoriin
    vector<std::string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string new_part = tmp.substr(0, tmp.find(delimiter)); //ottaa osan annettuun merkkiin asti
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());  //tekee uuden pätkän mistä lähteä liikkeelle

        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }

    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }


    return result;
}

void saver(vector<std::string> strings, vector <Library>& libraries) {
    // Tallentaa vektoriin libraries kirjastot, jota on riviltä tullut ja
    // tallentaa rivillä olevan kirjan ja sen atribuuti ja päivittää kirjan
    // reservations attribuuttia, jos se esiintyy monta kertaa samassa kirjastossa.

    //param strings, vector<string>, sisältää syötteen muuttujat vektorissa
    //param libraries vektor<Library>, sisältää kirjastot, jotka string vektorissa on

    //book, struct(Book), kirja, jolla on omat attribuutit
    //author, string, kirjan kirjoittaja
    //title, string, kirjan nimi
    //reservations_str, string, kirjan varaukset str muodossa, jos se on on-the-shelf
    //it, auto, etsii kirjastovektorista kirjastoa ja etsii sen nimen jos löytää

    Book book;
    string library_name = strings.at(0);
    string author = strings.at(1);
    string title = strings.at(2);
    string reservations_str = strings.at(3);

    auto it = find_if(libraries.begin(), libraries.end(),
    [library_name](const Library& library) {
        return library.get_name() == library_name; });

    if (it == libraries.end()) {
        // Lisää kirjaston vektoriin, jos sitä ei siellä vielä ollut
        Library new_library(library_name);
        new_library.add_book(author, title, reservations_str);
        libraries.push_back(new_library);
    } else {
        if (it->check_book(author, title)) {
            // Jos kirja on olemassa kirjastossa päivittää sen varausta
            it->update_book_reservations(author, title, reservations_str);
        } else {
            it->add_book(author, title, reservations_str);
        }
    }
}

string remove_quotes(const string& input) {
    // Poistaa edestä ja takaa minkä tahansa stringin ensimmäisen ja toisen osan,
    //jos löytää edestä "".

    //param input, string, mikä tahansa syöte, tässä tapauksessa kirja
    //return, result, string, "" merkit alusta ja lopusta poistettu input
    std::string result = input;

    if (result.front() == '"') {

        result = result.substr(1, result.length() - 2);
    }

    return result;
}

int main()
{

    string file_name = "";
    cout << "Input file: ";
    getline(cin, file_name);

    ifstream file(file_name);
    if ( not file ) {
        cout << "Error: input file cannot be opened" << endl;
        return EXIT_FAILURE;

    //Testaa avata tiedoston, jos onnistuu käy läpi split ja saver funktiot.

    } else {
        vector <Library> libraries;
        string line;
        while ( getline(file, line) ) {
            std::vector<std::string> strings = split(line, ';', true);

            if (strings.size() != 4) {
                std::cout << "Error: empty field" << std::endl;
                return EXIT_FAILURE;
            }

            saver(strings, libraries);
        }

        //Tämä osa tarkoitettu kirjastojen järjestelyyn, kun rivit on luettu.

        vector<string> library_names;

        for (const auto& library : libraries) {
            library_names.push_back(library.get_name());
        }

        sort(library_names.begin(), library_names.end());

        //Looppi, joka kysyy syötettä kunnes saa "quit" komennon.

        while (true) {
            string line;
            cout << "lib> ";
            getline(cin, line);
            std::vector<std::string> parts = split(line, ' ', true);
            string option = parts.at(0);

            if (option == "libraries") {

                //Tarkastetaan aina komennon antaessa, onko siinä oikea määrä parametreja

                if(parts.size() != 1) {
                    std::cout << "Error: wrong number of parameters" << std::endl;
                    continue;
                }

                //Tulostaa kirjastot, jotka valmiiksi järjestyksessä

                for (const auto& l : library_names) {
                    cout << l << endl;
                }

            } else if (option == "material") {

                if(parts.size() != 2) {
                    std::cout << "Error: wrong number of parameters" << std::endl;
                    continue;
                }

                //Taas sama koodi, joka etsii kirjaston nimeä.

                string library_name = parts.at(1);
                auto it = find_if(libraries.begin(), libraries.end(),
                [library_name](const Library& library) {
                    return library.get_name() == library_name; });

                //Jos löytää niin printtaa, jos ei antaa errorin.

                if (it != libraries.end()) {
                    it->print_books();

                } else {
                    std::cout << "Error: unknown library" << std::endl;
                }

            } else if (option == "books") {

                if(parts.size() != 3) {
                    std::cout << "Error: wrong number of parameters" << std::endl;
                    continue;
                }

                //Taas sama koodi, joka etsii kirjaston nimeä.

                string library_name = parts.at(1);
                auto it = find_if(libraries.begin(), libraries.end(),
                [library_name](const Library& library) {
                    return library.get_name() == library_name; });

                if (it != libraries.end()) {
                    vector <Book> books = it->get_books();
                    it->sort_books();

                    // Muuttuja, joka auttaa kirjan tekijän löytämiseen.
                    bool author_found = false;

                    //Käy läpi kirjailijan eri kirjojen varaustilanteet.

                    for (const auto& book : books) {
                        if (book.author == parts.at(2)) {
                            if (book.reservations == 0) {
                                cout << book.title << " --- " << "on the shelf"<< endl;
                            } else {
                                cout << book.title << " --- " << book.reservations << " reservations" << endl;
                            }
                            author_found = true;
                        }
                    }

                    if (!author_found) {
                        std::cout << "Error: unknown author" << std::endl;
                    }

                } else {
                    std::cout << "Error: unknown library" << std::endl;
                }


            } else if (option == "reservable") {
                string title = parts.at(2);
                string author = parts.at(1);

                //Käy läpi loput syötteestä ja tekee niistä kirjan muttujan.

                for (size_t i = 3; i < parts.size(); ++i) {
                    title += " " + parts.at(i);
                }

                // Poistaa mahdolliset sulkeet

                string title2 = remove_quotes(title);

                bool book_found = false;
                vector<string> on_the_shelf_libraries;
                vector<string> reserved_libraries;
                Book book;

                int min_reservations = 99999;

                // Käy läpi kirjastot, tarkistaa löytyykö niistä kirjoja.
                // Jos löytää niin ottaa kirjan, ja tarkistaa onko varaus liian
                // suuri, lisää "on-the-shelf" vektoriin jos kirjastossa varauksella
                // sellainen tila ja jos joku muu tila, niin ottaa mahdottoman suureen lukuun
                // vertailun, tallentaa siihen edellisen kirjan varausten määrän ja seuraavalla kerralla
                // pystyy vertaamaan tähän. (Mahdollistaa sen, että reserved_libraries näyttää aina parhaimman
                // vaihtoehdon kirjan saamiseen.

                for (const auto& library : libraries) {
                    if (library.check_book(author, title2)) {
                        book = library.get_book(author, title2);
                        book_found = true;

                        if (book.reservations >= 100) {
                            break;
                        } else if (book.reservations == 0) {
                            on_the_shelf_libraries.push_back(library.get_name());
                        } else {
                            if (book.reservations < min_reservations) {
                                min_reservations = book.reservations;
                                reserved_libraries.clear();
                                reserved_libraries.push_back(library.get_name());
                            } else if (book.reservations == min_reservations) {
                                reserved_libraries.push_back(library.get_name());
                            }
                        }
                    }
                }

                if (!book_found) {
                    cout << "Book is not a library book" << endl;

                } else {

                    if (!on_the_shelf_libraries.empty()) {
                        cout << "on the shelf" << endl;
                        for (const auto& library_name : on_the_shelf_libraries) {
                            cout << "--- " << library_name << endl;
                        }

                    } else if (!reserved_libraries.empty()) {
                        sort(reserved_libraries.begin(), reserved_libraries.end());
                        cout << min_reservations << " reservations" << endl;

                        for (const auto& library_name : reserved_libraries) {
                            cout << "--- " << library_name << endl;
                        }

                    } else {
                        cout << "Book is not reservable from any library" << endl;
                    }
                }

            } else if (option == "loanable") {

                //Tulostaa kirjoista ne, jotka ovat "on-the-shelf" järjestyksessä
                //Ensin laittaa ne vektoriin, jos sellainen kirja löytyy mistään kirjastosta,
                //Ja sitten vertailee aijemmin jo sort_books funktion tapaisella systeemillä
                //kirjoja toisiinsa ja näin saa selville aakkosjärjestyksen kirjoittajilla ja heidän
                //kirjoillaan.

                vector<Book> on_the_shelf_libraries;

                for (const auto& library : libraries) {
                    vector <Book> books = library.get_books();

                    for (auto& book : books) {
                        if (book.reservations == 0) {
                            on_the_shelf_libraries.push_back(book);
                        }
                    }
                }

                sort(on_the_shelf_libraries.begin(), on_the_shelf_libraries.end(), [](const Book& book1, const Book& book2) {
                if (book1.author == book2.author) {
                    return book1.title < book2.title;
                }
                return book1.author < book2.author;
                });

                for (const auto& book : on_the_shelf_libraries) {
                        cout << book.author << ": " << book.title << endl;
                    }


            } else if (option == "quit") {
                return EXIT_SUCCESS;

            } else {
                std::cout << "Error: unknown command" << std::endl;
            }
        }
    }
    file.close();
}
