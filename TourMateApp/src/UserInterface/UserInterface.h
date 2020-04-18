#ifndef TOURMATEAPP_USERINTERFACE_H
#define TOURMATEAPP_USERINTERFACE_H

#include <iostream>

using namespace std;

class UserInterface {
    private:

    public:
        UserInterface();
        int showMainMenu();
        void mainMenuSelection(int selected);
};

int readOption(int min, unsigned int max);
double readOption(double min, double max);

#endif //TOURMATEAPP_USERINTERFACE_H
