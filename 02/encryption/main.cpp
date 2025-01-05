#include <iostream>
#include <string>
#include <cctype>
#include <cstring>

using namespace std;

int encryptor(string encryption_key, string text_to_encrypt) {
    char encryption_key_letter = ' ';
    for( char kirjain = 'a'; kirjain < 'z'; ++kirjain) {
        encryption_key_letter = encryption_key.at(kirjain);
        text_to_encrypt.at(index) = encryption_key_letter;
    }
    return text_to_encrypt;

}


int main()
{
    string encryption_key = "";
    string::size_type apu = 0;

    cout << "Enter the encryption key: ";
    cin >> encryption_key;

    apu = encryption_key.length();

    //if (apu != 26) {
            //cout << "Error! The encryption key must contain 26 characters."<< endl;
            //return 1;
    //}
    string text_to_encrypt = ";";
    cout << "Enter somethin: ";
    cin >> text_to_encrypt;

    cout << encryptor(encryption_key, text_to_encrypt) << endl;




}
