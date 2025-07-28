// Written in project.
#include "main_menu.h"
#include "constants.h"
// 3rd party headers.
#include "SFML/Graphics.hpp"
// STL.

int main()
{   
    auto& main_menu{ Connect4::GUI::MainMenu::get_instance() };

    while (main_menu.isOpen())
    {
        while (auto event{ main_menu.pollEvent() }) {
            main_menu.receive_event(*event);
        }

        main_menu.draw_all();
    }
}