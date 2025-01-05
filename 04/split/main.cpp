#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function


std::vector< std::string > split(std::string line, char separator,bool param = false) {
    std::vector< std::string > new_vector;
    std::string::size_type pituus = line.length();
    std::string::size_type index = 0;


    for (std::string::size_type kirjain = 0; kirjain <= pituus; ++kirjain) {
        if (kirjain == pituus || line.at(kirjain) == separator) {
            std::string kohta = line.substr(index, kirjain - index);

            if (!(param && kohta == "")) {
                new_vector.push_back(kohta);

            }

            index = kirjain+1;
        }

    }
    return new_vector;

}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}

