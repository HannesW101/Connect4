// Written in project.
#include "main_menu.h"
// 3rd party headers.
// STL.
#include <iostream>

namespace Connect4 {
	namespace GUI {
		/*
		=================
			PRIVATE
		=================
		*/

		MainMenu::MainMenu() :
			sf::RenderWindow(
				sf::VideoMode::getFullscreenModes()[0], // Get vector for the different resolutions then take the 0 index (best resolution).
				"Connect 4", // Title for window.
				sf::Style::None, // Window style.
				sf::State::Fullscreen, // State of the window.
				sf::ContextSettings{ 0u, 0u, 8u }  // depth, stencil, antialiasing.
			)
		{

			// Set fps to refresh rate of monitor.
			this->setVerticalSyncEnabled(true);

			this->load_resources();
		}

		/*
		=================
			PUBLIC
		=================
		*/

		// Get the 1 instance of the main menu class.
		MainMenu& MainMenu::get_instance() {
			static MainMenu instance;
			return instance;
		}

		void MainMenu::load_resources() {
			// Load button images
			if (!this->m_normal_textures_arr[CustomButton::play_offline].loadFromFile("assets/pics/button_offline_normal.png")) {
				std::cerr << "Failed to load button image!\n";
			}
			if (!this->m_hover_textures_arr[CustomButton::play_offline].loadFromFile("assets/pics/button_offline_hover.png")) {
				std::cerr << "Failed to load button image!\n";
			}
			if (!this->m_normal_textures_arr[CustomButton::play_online].loadFromFile("assets/pics/button_online_normal.png")) {
				std::cerr << "Failed to load button image!\n";
			}
			if (!this->m_hover_textures_arr[CustomButton::play_online].loadFromFile("assets/pics/button_online_hover.png")) {
				std::cerr << "Failed to load button image!\n";
			}
			if (!this->m_normal_textures_arr[CustomButton::play_exit].loadFromFile("assets/pics/button_exit_normal.png")) {
				std::cerr << "Failed to load button image!\n";
			}
			if (!this->m_hover_textures_arr[CustomButton::play_exit].loadFromFile("assets/pics/button_exit_hover.png")) {
				std::cerr << "Failed to load button image!\n";
			}

			for (std::size_t i{ 0u }; i < this->m_button_ptrs.size(); ++i) {
				// Set anisotropic filtering.
				this->m_normal_textures_arr[i].setSmooth(true);
				this->m_hover_textures_arr[i].setSmooth(true);

				// Create button using the normal texture.
				this->m_button_ptrs[i] = std::make_unique<Connect4::GUI::Button>(this->m_normal_textures_arr[i]); // Point to the new button

				// Switch to resize and position the different buttons.
				switch (i)
				{
				case CustomButton::play_exit:
					// Resize the button with the chosen scale.
					this->m_button_ptrs[i]->resize(*this, this->m_normal_textures_arr[i], Connect4::Button::MainMenu::SMALL_SCALE); // Resize to % of window size.

					// Set the position of the button using chosen x and y values ( use the windows as anchors so its dynamically sized ).
					// Dont worry the function takes into account the scaling and calculates using that ( thats why you need to pass the texture ).
					this->m_button_ptrs[CustomButton::play_exit]->set_pos(this->m_normal_textures_arr[CustomButton::play_exit], { getSize().x - 180.00f, 100.00f });
					break;
				default:
					// Resize the button with the chosen scale.
					this->m_button_ptrs[i]->resize(*this, this->m_normal_textures_arr[i], Connect4::Button::MainMenu::NORMAL_SCALE); // Resize to % of window size.

					// Set the position of the button using chosen x and y values ( use the windows as anchors so its dynamically sized ).
					// Dont worry the function takes into account the scaling and calculates using that ( thats why you need to pass the texture ).
					this->m_button_ptrs[i]->set_pos(this->m_normal_textures_arr[i], { getSize().x / 2.0f, getSize().y / 2.0f + 10.0f + (static_cast<float>(i) * 200.0f) });
					break;
				}
			}
		}

		void MainMenu::draw_all() {
			// First clear the screen with the background color.
			this->clear(Connect4::Color::DarkPurple); 

			// Assets are added here.
			// First check that they exist to avoid drawing when the pointers are null.

			for (std::size_t i{ 0u }; i < this->m_button_ptrs.size(); ++i) {
				if (this->m_button_ptrs[i]) {
					this->m_button_ptrs[i]->draw(*this);
					this->m_button_ptrs[i]->update(*this, this->m_hover_textures_arr[i], this->m_normal_textures_arr[i], mapPixelToCoords(sf::Mouse::getPosition(*this)));
				}
			}

			// Finally display all thats was been rendered.
			this->display();
		}
	}
}