#include "Utils.h"

bool isUnix() {
#ifdef __unix__
    return true;
#else
    return false;
#endif
}

double safeDivision(double numerator, double denominator, double subst) {
    denominator = denominator == 0 ? subst : denominator;
    return numerator / denominator;
}

double checkNumber() {
    double input;
    while (true) {
        try {
            cout << "[EXIT -1] ";
            cin >> input;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                throw WrongInput_option("Invalid Input. Please enter an integer");

            } else
                return input;
        }
        catch (WrongInput_option &error) {
            cout << error.getInfo() << endl;
            continue;
        }
    }
}

void wait() {
    cout << endl << "[PRESS ENTER]";
    cin.ignore();
    while (cin.get() != '\n') {};
}

void clear_screen() {
#ifdef WINDOWS
    std::system("cls");
#else
    std::system("clear");
#endif
}