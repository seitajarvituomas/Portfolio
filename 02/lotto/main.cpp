#include <iostream>

using namespace std;

unsigned long int foo(int number) {
    if (number == 0) {
        return 1;
    } else {
        return (number*foo(number-1));
    }
}


int main()
{

    int ball_amount = 0;
    cout << "Enter the total number of lottery balls: ";
    cin >> ball_amount;

    int drawn_balls = 0;
    cout << "Enter the number of drawn balls: ";
    cin >> drawn_balls;



    if (ball_amount < 0 || drawn_balls < 0) {
        cout << "The number of balls must be a positive number." << endl;

    } else if (ball_amount < drawn_balls) {
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;

    } else {
        unsigned long int the_number = (foo(ball_amount))/((foo(ball_amount-drawn_balls))*(foo(drawn_balls)));
        cout << "The probability of guessing all " << drawn_balls << " balls correctly is 1/" << the_number << endl;

    }
}
