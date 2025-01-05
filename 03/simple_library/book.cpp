#include "book.hh"
#include "date.hh"
#include <iostream>
#include <string>

Book::Book(std::string const& tekija, std::string const& nimi):
    nimi_(nimi), tekija_(tekija)
{
    available_ = true;
    loan_date_ = Date(0, 0, 0);
    return_date_ = Date(0, 0, 0);
}

void Book::print(){
    std::cout << tekija_  << " : " << nimi_ << std::endl;
    
    if (is_available()) {
        std::cout << "- available" << std::endl;
    } else {

        std::cout << "- loaned: ";
        loan_date_.print();
        std::cout << "- to be returned: ";
        return_date_.print();
    }

}

bool Book::is_available() {
    return available_;
}


void Book::loan(Date const& today_) {

    if (is_available()) {
        available_ = false;
        loan_date_ = today_;
        return_date_ = loan_date_;
        return_date_.advance(28);
        
    } else {
        std::cout << "Already loaned: cannot be loaned" << std::endl;
    }
}

void Book::renew(){
    if (is_available()) {
        std::cout << "Not loaned: cannot be renewed" << std::endl;
    } else {
        return_date_.advance(28);

    }

}

void Book::give_back(){
    if (not is_available()) {
        available_ = true;
    }


}
