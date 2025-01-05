#ifndef LIBRARY_HH
#define LIBRARY_HH

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Book
{
    string author;
    string title;
    int reservations;
};

class Library

{
public:
    Library(const string& name);

    void add_book(string author, string title, string reservations_str);
    string get_name() const;
    void print_books();
    vector <Book> get_books() const;
    void sort_books();
    bool check_book(string author, string title) const;
    Book get_book(string author, string title) const;
    void update_book_reservations(string author, string title, string reservations);

private:
    string name;
    vector <Book> books;

};

#endif // LIBRARY_HH
