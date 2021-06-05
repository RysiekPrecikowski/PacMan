//
// Created by rprec on 30.05.2021.
//

#ifndef CPP_CONSOLE_H
#define CPP_CONSOLE_H

#include <string>

class Console {
    std::string name;
public:
    Console(std::string name = "NAME");

    void write(std::string text);
};

#endif //CPP_CONSOLE_H
