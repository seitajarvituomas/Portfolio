#include "course.hh"
#include "account.hh"
#include <iostream>

Course::Course(const std::string& code, const std::string& name, int credits):
    course_code_(code), name_(name), credits_(credits)
{
}

Course::~Course()
{

}

void Course::print_info(bool print_new_line)
{
    std::cout << course_code_ << " : " << name_;
    if ( print_new_line )
    {
        std::cout << std::endl;
    }
}

void Course::print_long_info()
{
    std::cout << "* Course name: " << name_ << std::endl
              << "* Code: " << course_code_ << std::endl;
    print_staff();
}

void Course::print_staff()
{
    std::cout << "* Staff: " << std::endl;
    for (auto member : course_staff_ )
    {
        member->print();
    }
}

void Course::add_staff(Account *new_staff_member)
{
    // Checking if account is already a staff member
    for ( unsigned int i = 0; i < course_staff_.size(); ++i )
    {
        if ( course_staff_.at(i) == new_staff_member )
        {
            std::cout << STAFF_EXISTS << std::endl;
            return;
        }
    }

    course_staff_.push_back(new_staff_member);
    std::cout << STAFF_ADDED << std::endl;
}

const std::string Course::get_code() const
{
    return course_code_;
}

int Course::get_credits() const
{
    return credits_;
}

void Course::add_student(Account *signed_student)
/* Tarkastaa onko oppilas suorittanut jo kurssin, onko oppilas
 * olemassa ja jos on lisää kurssin suorittajiin.
 */
{
    for ( unsigned int i = 0; i < completed_students.size(); ++i )
    {
        if ( completed_students.at(i) == signed_student )
        {
            std::cout << STUDENT_COMPLETED << std::endl;
            return;
        }
    }

    for ( unsigned int i = 0; i < signed_students.size(); ++i )
    {
        if ( signed_students.at(i) == signed_student )
        {
            std::cout << STUDENT_EXISTS << std::endl;
            return;
        }
    }

    signed_students.push_back(signed_student);
    std::cout << SIGNED_UP << std::endl;
}

void Course::add_completed_student(Account *completed_student)
// Lisää oppilaan kurssin suorittaneisiin
{
    completed_students.push_back(completed_student);
}

std::string Course::get_code()
{
    return course_code_;
}

std::string Course::get_name()
{
    return name_;
}

void Course::print_students()
// Tulostaa oppilaiden opiskelijanumerot, nimen ja sähköpostin.
{
    for (auto student : signed_students) {
        std::cout << student->get_account_number() <<": " << student->get_full_name() <<", "
        << student->get_email() << std::endl;
    }
}
