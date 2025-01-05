#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>

class Player
{
public:
    Player(std::string const&  nimi);

    std::string get_name();

    int get_points();

    bool has_won();

    void add_points(int pts);


private:
    std::string nimi_;
    int points_;
};

#endif // PLAYER_HH
