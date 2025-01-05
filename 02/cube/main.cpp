#include <iostream>

using namespace std;

int main()
{
    int feed = 0;
    cout << "Enter a number: ";
    cin >> feed;
    int cube = feed*feed*feed;
    if (cube >= 0)
        cout << "The cube of " << feed << " is " << cube << "." << endl;
    else
        cout << "Error! The cube of " << feed << " is not " << cube << "." << endl;
}
