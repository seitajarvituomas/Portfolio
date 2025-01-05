/* Yliopisto
 *
 * Kuvaus:
 * Ohjelmassa toimii 5 eri luokkaa Account, Cli, Course, University
 * ja Utils. Utils luokkassa on hyödyllisiä komentoja tekstin käsittelyyn
 * ja Cli pyörittää ohjelmaa. Cli toimii myös komentojen avustimena.
 * University on luokka, jota käyttäjän pitää ymmärtää, koska siellä
 * on komennot, jota käyttäjän pitää syöttää tehdäkseen yliopiston sisällä asioita.
 * Yliopistossa voi hallinnoida kursseja ja henkilöitä yliopistossa, tehdä näillä eri
 * toimenpiteitä ja printata tietoja mitä kurssilla tai henkilöllä tapahtuu yliopistossa.
 * University-luokka käyttää apunaan kahta muuta luokkaa Course ja Account. Ohjelman voi
 * lopettaa antamalla sille käskyn "QUIT".
 *
 * Ohjelman kirjoittaja
 * Nimi: Tuomas Seitajärvi
 * Opiskelijanumero: 150470483
 * Käyttäjätunnus: cgtuse
 * E-Mail: tuomas.seitajarvi@tuni.fi
 * */

//#include "utils.hh"
#include "cli.hh"
#include "university.hh"
//#include <iostream>
//#include <string>
//#include <vector>
//#include <fstream>

const std::string PROMPT = "Uni> ";


int main()
{
    University* university = new University("tuni.fi");
    Cli cli(university, PROMPT);
    while ( cli.exec() ){}

    university->cleanup();
    delete university;
    return EXIT_SUCCESS;
}

