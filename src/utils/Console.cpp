//
// Created by rprec on 30.05.2021.
//

#include "Console.h"
#include <iostream>

using namespace std;

Console::Console(std::string name) {
    this->name = name;
}

void Console::write(std::string text) {
    cout << "[" << name << "]: " << text << endl;
}


