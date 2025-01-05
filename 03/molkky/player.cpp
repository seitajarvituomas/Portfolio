#include "player.hh"
#include <iostream>
#include <string>


Player::Player(std::string const&  nimi):
    nimi_(nimi)
{
    points_ = 0;
}

std::string Player::get_name() {
    return nimi_;
}

int Player::get_points() {
    return points_;
}

bool Player::has_won() {
    if (points_ == 50) {
        return true;

    } else {
        return false;
    }
}

void Player::add_points(int pts_) {
    points_ += pts_;

    if (points_ > 50) {
        std::cout << nimi_ << " gets penalty points!" << std::endl;
        points_ = 25;
    }
}
