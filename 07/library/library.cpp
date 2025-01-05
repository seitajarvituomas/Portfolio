#include "library.hh"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

Library::Library(const string& name):
    name(name)
{
}

void Library::add_book(string author, string title, string reservations_str) {
   //Lisää kirjan Kirjastoon ja vektoriin kirjat
   Book book;
   book.author = author;
   book.title = title;

   if ( reservations_str=="on-the-shelf") {
       book.reservations = 0;
   } else {
       book.reservations = stol(reservations_str);
   }


   books.push_back(book);
}

string Library::get_name() const{
    //Palauttaa kirjaston nimen
    return name;
}

vector <Book> Library::get_books() const{
    //Palauttaa kirjaston kirjat
    return books;
}

bool Library::check_book(string author, string title) const {
    //Tarkistaa kirjaston kirjoista löytyykö pari annettujen stringien kanssa
    //Ja palauttaa, joko true tai false
    for (auto& book : books) {
        if (book.author == author && book.title == title) {
            return true;
        }
    }
    return false;
}

Book Library::get_book(string author, string title) const  {
    // Tarkastaa kirjaston kirjoista löytyykö paria ja palautta
    // kirjan, jos se löytyy, muuten tyhjän kirjan
    for (auto& book : books) {
        if (book.author == author && book.title == title) {
            return book;
        }
    }
    return Book();
}

void Library::sort_books() {
    // Vertailee kirjoittajia toisiinsa, jos löytää saman, vertailee niiden kirjoja
    // jos ei palauttaa kirjailijan (ja tämän kirjan).

    sort(books.begin(), books.end(), [](const Book& book1, const Book& book2) {
    if (book1.author == book2.author) {
        return book1.title < book2.title;
    }
    return book1.author < book2.author;
    });

}

void Library::print_books() {
    // käyttää sort_books komentoa järjestelyyn ja sitten printtaa kirjat kirjastossa
    sort_books();

    for (const auto& book : books) {
           std::cout << book.author << ": " << book.title << std::endl;
       }
}

void Library::update_book_reservations(string author, string title, string reservations) {
    //Päivittää kirjojen varauksia kirjastossa.
    Book book = get_book(author, title);

    if ( reservations=="on-the-shelf") {
        book.reservations = 0;
    } else {
        book.reservations = stol(reservations);
    }
}
