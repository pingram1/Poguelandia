// Utils.cpp
#include "Utils.hpp"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

void typeEffect(const string& text, int delayMs) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
    cout << endl;
}
