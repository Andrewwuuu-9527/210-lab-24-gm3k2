// Goat.h

#ifndef GOAT_H
#define GOAT_H#include <string>

using namespace std;

class Goat {
    private: string name;
    int age;
    string color;

    public:
        // Default constructor
        Goat() {
            name = "";
            age = 0;
            color = "";
        }

    // Constructor: name only
    Goat(string n) {
        name = n;
        age = 0;
        color = "";
    }

    // Constructor: name + age
    Goat(string n, int a) {
        name = n;
        age = a;
        color = "";
    }

    // Constructor: all parameters
    Goat(string n, int a, string c) {
        name = n;
        age = a;
        color = c;
    }

    // Setters and getters
    void set_name(string n) {
        name = n;
    }
    string get_name() const {
        return name;
    }
    void set_age(int a) {
        age = a;
    }
    int get_age() const {
        return age;
    }
    void set_color(string c) {
        color = c;
    }
    string get_color() const {
        return color;
    }

    // Overloaded < operator: sorts by name, then age
    // Used by std::list::sort()
    bool operator < (const Goat & other) const {
        if (name != other.name)
            return name < other.name;
        return age < other.age;
    }
};
#endif