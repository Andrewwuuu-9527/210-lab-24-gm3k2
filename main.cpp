// COMSC-210 | Lab 23 | Andrew
#include <iostream>

#include <fstream>

#include <list>

#include <string>

#include <cstdlib>

#include <ctime>

#include "Goat.h"

using namespace std;

const int SZ_NAMES = 200,
    SZ_COLORS = 25,
    MAX_AGE = 20;

int select_goat(list < Goat > & trip);
void delete_goat(list < Goat > & trip);
void add_goat(list < Goat > & trip, string names[], string colors[]);
void display_trip(list < Goat > trip);
int main_menu();

int main() {
    srand(time(0));

    // Read names into array
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();

    // Read colors into array
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    list < Goat > trip;
    bool again = true;
    while (again) {
        int choice = main_menu();
        switch (choice) {
        case 1:
            add_goat(trip, names, colors);
            break;
        case 2:
            delete_goat(trip);
            break;
        case 3:
            display_trip(trip);
            break;
        case 4:
            again = false;
            break;
        }
    }

    return 0;
}

// main_menu() displays menu, validates, returns choice
int main_menu() {
    int choice;
    bool valid = false;
    while (!valid) {
        cout << "\n*** GOAT MANAGER 3001 ***\n";
        cout << "[1] Add a goat\n";
        cout << "[2] Delete a goat\n";
        cout << "[3] List goats\n";
        cout << "[4] Quit\n";
        cout << "Choice --> ";
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid choice. Enter 1-4.\n";
        } else {
            valid = true;
        }
    }
    return choice;
}

// add_goat() randomly generates a goat and adds it to the trip
void add_goat(list < Goat > & trip, string names[], string colors[]) {
    string n = names[rand() % SZ_NAMES];
    int a = rand() % (MAX_AGE + 1);
    string c = colors[rand() % SZ_COLORS];
    trip.push_back(Goat(n, a, c));
    cout << "Added: " << n << " (" << a << ", " << c << ")\n";
}

// display_trip() shows all goats with numbering
void display_trip(list < Goat > trip) {
    if (trip.empty()) {
        cout << "No goats in the trip.\n";
        return;
    }
    int count = 1;
    for (auto it = trip.begin(); it != trip.end(); ++it) {
        cout << "[" << count++ << "] " << it -> get_name() <<
            " (" << it -> get_age() << ", " <<
            it -> get_color() << ")\n";
    }
}

// select_goat() shows submenu and returns user's 1-based choice
int select_goat(list < Goat > & trip) {
    if (trip.empty()) {
        cout << "No goats to select.\n";
        return -1;
    }
    display_trip(trip);
    int choice;
    bool valid = false;
    while (!valid) {
        cout << "Select a goat: ";
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > (int) trip.size()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid. Enter 1-" << trip.size() << ".\n";
        } else {
            valid = true;
        }
    }
    return choice;
}

// delete_goat() selects and removes a goat by position
void delete_goat(list < Goat > & trip) {
    int choice = select_goat(trip);
    if (choice == -1) return;

    auto it = trip.begin();
    advance(it, choice - 1);
    cout << "Removed: " << it -> get_name() << "\n";
    trip.erase(it);
}