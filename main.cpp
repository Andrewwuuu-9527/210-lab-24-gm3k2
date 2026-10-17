// COMSC-210 | Lab 24 | Andrew
#include <iostream>

#include <fstream>

#include <set>

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

    set < Goat > trip;
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

// add_goat() randomly generates a goat and inserts it into the set
void add_goat(set<Goat>& trip, string names[], string colors[]) {
    string n = names[rand() % SZ_NAMES];
    int a = rand() % (MAX_AGE + 1);
    string c = colors[rand() % SZ_COLORS];
    // Insert goat into set; check for duplicates
    auto result = trip.insert(Goat(n, a, c));
    if (result.second)
        cout << "Added: " << n << " (" << a << ", " << c << ")\n";
    else
        cout << "Duplicate goat ignored: " << n << " (" << a << ", " << c << ")\n";
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

// select_goat() displays goats with index and returns user's choice (1-based)
int select_goat(set<Goat>& trip) {
    if (trip.empty()) {
        cout << "No goats to select.\n";
        return -1;
    }

    // Display goats with numbering
    int count = 1;
    for (auto it = trip.begin(); it != trip.end(); ++it) {
        cout << "[" << count++ << "] " << it->get_name()
             << " (" << it->get_age() << ", "
             << it->get_color() << ")\n";
    }

    int choice;
    bool valid = false;
    while (!valid) {
        cout << "Select a goat: ";
        cin >> choice;
        if (cin.fail() || choice < 1 || choice > (int)trip.size()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid. Enter 1-" << trip.size() << ".\n";
        } else {
            valid = true;
        }
    }
    return choice;
}

// delete_goat() removes the goat at the chosen index
void delete_goat(set<Goat>& trip) {
    int choice = select_goat(trip);
    if (choice == -1) return;

    // Find the iterator to the chosen goat
    auto it = trip.begin();
    for (int i = 1; i < choice; ++i)
        ++it;

    cout << "Removed: " << it->get_name() << "\n";
    trip.erase(it);
}