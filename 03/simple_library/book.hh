#ifndef BOOK_HH
#define BOOK_HH

#include <string>
#include "date.hh"

class Book {
public:
    Book( std::string const& tekija,  std::string const& nimi);
    void print();
    void loan(Date const& today_);
    void renew();
    void give_back();

    bool is_available();

private:
    std::string nimi_;
    std::string tekija_;

    bool available_;
    Date loan_date_;
    Date return_date_;

};

#endif // BOOK_HH
