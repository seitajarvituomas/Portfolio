#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string input_file ="";
    string output_file ="";

    cout <<"Input file: ";
    cin >> input_file;

    cout <<"Output file: ";
    cin >> output_file;

    ifstream tiedosto_olio(input_file);

    if (not tiedosto_olio) {
        cout << "Error! The file " << input_file << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {

        ofstream output(output_file);

        int repeator = 1;
        string rivi;

        while ( getline(tiedosto_olio, rivi)) {
            rivi = std::to_string(repeator) + " " + rivi;

            output << rivi << endl;

            repeator += 1;

        }

        output.close();
        tiedosto_olio.close();

        return 0;
    }
}
