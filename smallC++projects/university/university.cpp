#include "university.hh"
#include <iostream>
#include "course.hh"
#include <vector>

University::University(const std::string& email_suffix):
    running_number_(111111), email_suffix_(email_suffix)
{
}

University::~University()
{    
}

void University::new_course(Params params)
{
    std::string code = params.at(0);
    std::string name = params.at(1);
    if ( courses_.find(code) != courses_.end() )
    {
        std::cout << ALREADY_EXISTS << std::endl;
        return;
    }
    else
    {
        std::cout << NEW_COURSE << std::endl;
    }

    Course* n_course = new Course(code, name);
    courses_.insert({n_course->get_code(), n_course});
}

void University::print_courses(Params)
{
    for ( auto course : courses_ )
    {
        course.second->print_info(true);
    }
}

void University::print_course(Params params)
{
    std::string code = params.at(0);
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }

    courses_.at(code)->print_long_info();
}

void University::new_account(Params params)
{
    std::string full_name = params.at(0);
    int num = 0;
    for ( std::map<int, Account*>::iterator iter = accounts_.begin();
          iter != accounts_.end();
          ++iter )
    {
        if ( iter->second->get_full_name() == full_name )
        {
            std::string email = iter->second->get_email();
            num = Utils::numeric_part(email);
            if(num == 0)
            {
                ++num;
            }
            ++num;
        }
    }

    int account_number = running_number_++;
    Account* n_account = new Account(full_name, account_number, num,
                                     email_suffix_);
    accounts_.insert({account_number, n_account});
    std::cout << NEW_ACCOUNT << std::endl;
    n_account->print();
}

void University::print_accounts(Params)
{
    for ( auto account : accounts_ )
    {
        account.second->print();
    }
}

void University::print_account(Params params)
{
    int account = std::stoi(params.at(0));
    std::map<int, Account*>::iterator iter = accounts_.find(account);

    if (check_account(account)) {
        iter->second->print();
    }
}

void University::add_staff(Params params)
{
    std::string code = params.at(0);
    int account = std::stoi(params.at(1));

    if (check_account(account)) {
        if (check_course(code)) {
            courses_.at(code)->add_staff(accounts_.at(account));
        }
    }
}

void University::sign_up(Params params)
/* Ilmoittaa henkilön kurssille saadessaan oikean
 * kurssikoodin ja henkilönumeron.

 * Param code, string, kurssikoodi
 * Param account, int, henkilönumero
 */
{
    std::string code = params.at(0);
    int account = std::stoi(params.at(1));

    if (check_course(code)) {
        if (check_account(account)) {
            if (check_if_graduated(account)) {
                //lisää kurssille henkilön ja henkilölle uuden kurssin.
                courses_.at(code)->add_student(accounts_.at(account));
                accounts_.at(account)->add_course(courses_.at(code));
            }
        }
    }
}

void University::complete(Params params)
/* Suorittaa opiskelijan kurssin, jos mahdollista
 * (virhetilanteet, ei ole suorittanut vielä).

 * Param code, string, kurssikoodi
 * Param account, int, henkilönumero
 */
{
    std::string code = params.at(0);
    int account = std::stoi(params.at(1));

    if (check_course(code)) {
        if (check_account(account)) {
            if (check_if_graduated(account)) {
                //lisää henkilölle kurssin suoritetuksi ja kurssin
                //suoritettujen infoon henkilön
                accounts_.at(account)->complete_course(courses_.at(code));
                courses_.at(code)->add_completed_student(accounts_.at(account));
            }
        }
    }
}

void University::print_signups(Params params)
/* Tulostaa kurssille ilmottautuneet henkilöt.

 * Param code, string, kurssikoodi
 */
{
    std::string code = params.at(0);
    if (check_course(code)) {
        courses_.at(code)->print_students();
    }
}

void University::print_completed(Params params)
/* Tulostaa henkilön suoritetut kurssit ja opintopisteet.

 * Param account, int, henkilönumero
 */
{
    int account = std::stoi(params.at(0));

    if (check_account(account)) {
        accounts_.at(account)->completed_print();
    }
}

void University::print_study_state(Params params)
/* Tulostaa kaikki tiedot henkilön kurssimenestyksestä.

 * Param account, int, henkilönumero
 */
{
    int account = std::stoi(params.at(0));

    if (check_account(account)) {
        accounts_.at(account)->study_state_print();
    }
}

void University::graduate(Params params)
/* Tekee henkilöstä valmistuneet ja lisää valmistuneiden
 * joukkoon.

 * Param account, int, henkilönumero
 */
{
    int account = std::stoi(params.at(0));

    if (check_account(account)) {
        accounts_.at(account)->graduate();
        graduated_students.push_back(accounts_.at(account));
    }
}

bool University::check_account(int account)
/* Tarkastaa löytyykö käyttäjä järjestelmästä,
 * jos ei antaa error ja palauttaa false

 * Param account, int, henkilönumero
 */
{
    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return false;
    }
    return true;
}

bool University::check_course(std::string code)
/* Tarkastaa löytyykö kurssi järjestelmästä,
 * jos ei antaa error ja palauttaa false

 * Param code, string, kurssikoodi
 */
{
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return false;
    }
    return true;
}

bool University::check_if_graduated(int account)
/* Tarkastaa löytyykö käyttäjä valmistuneista,
 * jos ei antaa error ja palauttaa false.

 * Param account, int, henkilönumero
 */
{
    for ( unsigned int i = 0; i < graduated_students.size(); ++i )
    {
        if ( graduated_students.at(i) == accounts_.at(account) )
        {
            std::cout << ALREADY_GRADUATED << std::endl;
            return false;
        }
    }
    return true;
}

void University::cleanup()
{


    for (auto& account : accounts_) {
        delete account.second;
    }
    accounts_.clear();

    for (auto& course : courses_) {
        delete course.second;
    }
    courses_.clear();

}
