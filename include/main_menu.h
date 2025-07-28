#pragma once
// Written in project.
#include "button.h"
#include "constants.h"
// 3rd party headers.
#include "SFML/Graphics.hpp"
// STL.
#include <memory>
#include <array>

namespace Connect4 {
	namespace GUI {
		// Class to setup the main menu.
		// Uses singlton pattern.
		class MainMenu final : public sf::RenderWindow {
		private:
			// To add more buttons make an enum, add + 1 to the arrays and load the new image. 
			enum CustomButton {
				play_offline,
				play_online,
				play_exit
			};

			// Arrays to hold textures and pointers to buttons.
			// The magic number is the total number of buttons on the main menu.
			std::array<sf::Texture, 3> m_normal_textures_arr;
			std::array<sf::Texture, 3> m_hover_textures_arr;
			std::array<std::unique_ptr<Connect4::GUI::Button>, 3> m_button_ptrs;

			// Private constructor to prevent making more main menus.
			// Initializes window with default settings for the game.
			MainMenu();

			// Default destructor.
			~MainMenu() = default;
		public:
			// Deleted copy/move operations
			MainMenu(const MainMenu&) = delete;
			MainMenu& operator=(const MainMenu&) = delete;
			MainMenu(MainMenu&&) = delete;
			MainMenu& operator=(MainMenu&&) = delete;

			// Get the 1 instacne of the MainMenu.
			static MainMenu& get_instance();

			// Load the assets from the assets directory.
			// Create the assets pointers.
			void load_resources();

			// Draw the assets onto the current window.
			void draw_all();

			// Receive events happening on the main menu.
			void receive_event(sf::Event& event);
		};
	}
}