#include <iostream>

using namespace std;

int main()
{
    int annettu_luku = 0;
    cout << "Enter a positive number: ";
    cin >> annettu_luku;

    int joku_luku = 6;

    if (annettu_luku <= 0)
        cout << "Only positive numbers accepted" << endl;

    else {
        while (annettu_luku%joku_luku!= 0) {
            joku_luku -= 1;

            }

    if (annettu_luku == 6)
        cout << annettu_luku << " = " << 6/3 << " * " << 6/2 << endl;

    else if (annettu_luku/joku_luku < joku_luku)
    cout << annettu_luku << " = " << annettu_luku/joku_luku << " * " << joku_luku << endl;

    else
    cout << annettu_luku << " = " << joku_luku << " * " << annettu_luku/joku_luku << endl;
    }
    return 0;
}
