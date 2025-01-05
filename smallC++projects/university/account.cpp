#include "account.hh"
#include "utils.hh"
#include "course.hh"
#include <iostream>
#include <algorithm>

Account::Account(const std::string& full_name, int account_number,
                 int duplicates, const std::string& university_suffix):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    account_number_(account_number)
{
    std::vector<std::string> name = Utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();

    // Constructing e-mail address
    email_ = Utils::to_lower(first_name_);
    email_ += ".";
    if ( duplicates > 0 )
    {
        email_ += std::to_string(duplicates);
        email_ += ".";
    }
    email_ += Utils::to_lower(last_name_);
    email_ += "@";
    email_ += university_suffix;
}

Account::~Account()
{

}

void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email() const
{
    return email_;
}

std::string Account::get_full_name() const
{
    return full_name_;
}

int Account::get_account_number() const
{
    return account_number_;
}

void Account::add_course(Course *course)
{
    signed_courses.push_back(course);
}

void Account::graduate()
/* Vaihtaa käyttäjän valmistuneeksi ja laittaa kaikki
 * jäljelle jääneet kurssit tehdyiksi ja poistaa ne
 * kursseista mihin henkilö on ilmottautunut.
 */
{
    std::cout << GRADUATED << std::endl;

    has_graduated = true;

    while ( !signed_courses.empty() )
    {
        Course* course = signed_courses.front();
        completed_courses.push_back(course);
        signed_courses.erase(signed_courses.begin());
    }
}

void Account::complete_course(Course *course)
/* Jos löytää kurssin koodin avulla kurssin järjestelmästä
 * laittaa se sen suoritettujen joukkoon ja poistaa sen
 * kursseista mihin henkilö on ilmottautunut.
 */
{
    bool found_signup = false;
    for ( auto signed_course : signed_courses )
    {
        if (signed_course->get_code() == course->get_code() )
        {
            std::cout << COMPLETED << std::endl;
            found_signup = true;
            completed_courses.push_back(course);
            signed_courses.erase(std::remove(signed_courses.begin(), signed_courses.end(), course), signed_courses.end());
        }
    }

    if (!found_signup) {
        std::cout << NO_SIGNUPS << std::endl;
        return;
    }
}

void Account::study_state_print()
/* Tulostaa kaikki kurssit mihin henkilö on ilmottautunut.
 * Ja käyttää completed_print() funktiota kertomaan tehdyt kurssit
 * ja opintopisteet.
 */
{
    std::cout << "Current:" << std::endl;
    for ( Course* course : signed_courses )
    {
        std::cout << course->get_code() << " : " << course->get_name() << std::endl;
    }
    std::cout << "Completed:" << std::endl;
    completed_print();
}

void Account::completed_print()
/* Kertoo mitkä kurssit opiskelija on suorittanut
 * ja näistä saadut opintopisteet.
 */
{
    int counter = 0;
    for ( Course* course : completed_courses )
    {
        std::cout << course->get_code() << " : " << course->get_name() << std::endl;
        counter += course->get_credits();
    }
    std::cout << "Total credits: " << counter << std::endl;
}
