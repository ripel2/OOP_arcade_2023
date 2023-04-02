/*
** EPITECH PROJECT, 2023
** OOP_arcade_2023 [WSL : Ubuntu]
** File description:
** Main
*/

#include <iostream>

#include "Core.hpp"

void print_help(void)
{
    std::cout << "USAGE" << std::endl;
    std::cout << "\t./arcade lib" << std::endl;
    std::cout << "DESCRIPTION" << std::endl;
    std::cout << "\tlib\tthe library containing the graphical interface" << std::endl;
}

int main(int ac, char **av)
{
    if (ac != 2) {
        print_help();
        return 84;
    }
    try {
        acd::Core core(av[1]);
        core.loadLibsFromFolder("./lib");
        core.startMenu();
        if (core.isReady())
            core.startGame();
    } catch (const std::exception &e) {
        std::cerr << av[0] << ": " << e.what() << std::endl;
        return 84;
    }
    return 0;
}
