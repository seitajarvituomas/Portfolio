#include <iostream>

using namespace std;

int main() {
    int amount = 0;
    cout << "How many numbers would you like to have? ";
    cin >> amount;

    int next_number = 0;

    while ( next_number != amount ) {

        next_number += 1;

        if (next_number%3 == 0  && next_number%7==0) {
            cout << "zip boing" << endl;

        } else if (next_number%7 == 0) {
            cout << "boing" << endl;

        } else if (next_number%3==0) {
            cout << "zip" << endl;

        } else {
          cout << next_number << endl;
        }
    }

    return 0;
}
