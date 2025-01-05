#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
    string input_file ="";

    cout <<"Input file: ";
    cin >> input_file;

    ifstream tiedosto_olio(input_file);

    if (not tiedosto_olio) {
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {


        string rivi;
        map <string, int> kaverit;


        while (getline(tiedosto_olio, rivi)) {

           size_t jae = rivi.find(':');
           std::string nimi = rivi.substr(0, jae);
           int pisteet = std::stoi(rivi.substr(jae + 1));

           if (kaverit.find(nimi) != kaverit.end()) {
               kaverit[nimi] += pisteet;

           } else {
               kaverit.insert ( {nimi, pisteet});
           }

        }

        tiedosto_olio.close();


        cout << "Final scores:" << endl;
        for (const auto& pair : kaverit) {
                std::cout << pair.first << ": " << pair.second << std::endl;

        }
    }
    return 0;

}
