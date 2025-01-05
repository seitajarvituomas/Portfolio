#include "account.hh"
#include <iostream>
#include <string>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit)
{
    generate_iban();
    money_ = 0;
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);

}

int Account::hae_money() {
    return money_;
}

void Account::print() const {
    std::cout << owner_ << " : " << iban_ << " : " << money_ << " euros" << std::endl;
}

void Account::set_credit_limit(int amount_) {
    if (has_credit_) {
    credit_limit_ = amount_;
    } else {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
    }
}

void Account::save_money(int amount_) {
    money_ += amount_;

}

void Account::take_money(int amount_){
    if (has_credit_) {
        if (money_-amount_ <= -credit_limit_) {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;

        } else {
            money_ -= amount_;
            std::cout << amount_ << " euros taken: new balance of " << iban_ << " is " << money_ << " euros" << std::endl;
        }

    }else {

        if (money_ >= amount_) {
            money_ -= amount_;
            std::cout << amount_ << " euros taken: new balance of " << iban_ << " is " << money_ << " euros " << std::endl;
        } else {
            std::cout << "Cannot take money: balance underflow" << std::endl;
        }
    }
}

void Account::transfer_to(Account& other_account, int amount_){
    if (has_credit_) {
        if (money_-amount_ <= -credit_limit_) {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
            std::cout << "Transfer from " << iban_ << " failed" << std::endl;

        } else {
            money_ -= amount_;
            other_account.money_ += amount_;
            std::cout << amount_ << " euros taken: new balance of " << iban_ << " is " << money_ << " euros" << std::endl;
        }

    }else {

        if (money_ >= amount_) {
            money_ -= amount_;
            other_account.money_ += amount_;
            std::cout << amount_ << " euros taken: new balance of " << iban_ << " is " << money_ << " euros " << std::endl;

        } else {
            std::cout << "Cannot take money: balance underflow" << std::endl;
            std::cout << "Transfer from " << iban_ << " failed" << std::endl;
        }
    }
}
