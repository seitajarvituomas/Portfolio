#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <vector>

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters

    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;

    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }

        // TODO: implement your solution here

        std::string::size_type length = word.length();


        if (length > 3) {
            std::vector<char> kirjaimet;


            for (char kirjain : word) {
                kirjaimet.push_back(kirjain);
            }

            std::vector<char>::iterator  alku = kirjaimet.begin();
            std::vector<char>::iterator  loppu = kirjaimet.end();


            shuffle(alku +1, loppu -1, generator);

            std::string word = "";


            for (char i : kirjaimet) {
                word.push_back(i);


            }

            std::cout << word << std::endl;
        } else {
            std::cout << word << std::endl;
        }


    }
    return 0;
}
