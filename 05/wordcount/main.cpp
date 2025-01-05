#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

void splitline(const string& rivi, vector<string>& sanat) {
    string sana;
    size_t alku = 0;
    size_t vali = rivi.find(' ');

    while (vali != string::npos) {
        sana = rivi.substr(alku, vali - alku);
        sanat.push_back(sana);

        alku = vali+1;
        vali = rivi.find(' ', alku);
    }

    sana = rivi.substr(alku);
    sanat.push_back(sana);
}



int main()
{
    string input_file ="";

    cout <<"Input file: ";
    cin >> input_file;

    ifstream tiedosto_olio(input_file);

    if (not tiedosto_olio) {
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }

    string rivi;

    map <string, map<int, int>> song;

    int repeator = 1;

    while (getline(tiedosto_olio, rivi)) {
       vector<string> sanat;

       splitline(rivi, sanat);

       for (const auto& sana : sanat) {
           song[sana][repeator]++;
       }

       ++ repeator;

    }

    tiedosto_olio.close();

    for (const auto& pair : song) {
        cout << pair.first << " " << pair.second.size() << ": ";

        if (!pair.second.empty()) {
            auto it = pair.second.begin();
            cout << it->first;
            ++it;

            for (; it != pair.second.end(); ++it) {
                cout << ", " << it->first;
            }
        }

        cout << endl;
    }

    return EXIT_SUCCESS;
}
