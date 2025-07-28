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
			),
			m_current_screen(Connect4::GUI::Screens::main_menu)
		{

			// Set fps to refresh rate of monitor.
			this->setVerticalSyncEnabled(true);

			this->load_resources();
		}

		void MainMenu::draw_main_menu() {
			// Draw buttons
			for (std::size_t i = 0; i < m_button_ptrs.size(); ++i) {
				if (m_button_ptrs[i]) {
					m_button_ptrs[i]->draw(*this);
					m_button_ptrs[i]->update(*this, m_hover_textures_arr[i], m_normal_textures_arr[i],
						mapPixelToCoords(sf::Mouse::getPosition(*this)));
				}
			}

			// Draw logo (cache this texture to avoid reloading every frame!)
			static sf::Texture logo_texture;
			static bool loaded = false;
			if (!loaded) {
				logo_texture.setSmooth(true);
				if (!logo_texture.loadFromFile("assets/pics/logo.png")) {
					std::cerr << "Failed to load logo image!\n";
				}
				loaded = true;
			}

			Connect4::GUI::Button logo(logo_texture);
			logo.resize(*this, logo_texture, Connect4::Button::MainMenu::LOGO_SCALE);
			logo.set_pos(logo_texture, { getSize().x / 2.0f, getSize().y / 2.0f + 10.0f - 500.0f });
			logo.draw(*this);
		}

		void MainMenu::draw_offline_menu() {

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

					// Set the on click event for the button.
					this->m_button_ptrs[CustomButton::play_exit]->set_on_click([this]() {
						this->close();
					});
					break;
				case CustomButton::play_offline:
					// Resize the button with the chosen scale.
					this->m_button_ptrs[i]->resize(*this, this->m_normal_textures_arr[i], Connect4::Button::MainMenu::NORMAL_SCALE); // Resize to % of window size.

					// Set the position of the button using chosen x and y values ( use the windows as anchors so its dynamically sized ).
					// Dont worry the function takes into account the scaling and calculates using that ( thats why you need to pass the texture ).
					this->m_button_ptrs[i]->set_pos(this->m_normal_textures_arr[i], { getSize().x / 2.0f, getSize().y / 2.0f + 50.0f + (static_cast<float>(i) * 400.0f) });

					// Set the on click event for the button.
					this->m_button_ptrs[CustomButton::play_offline]->set_on_click([this]() {
						this->m_current_screen = Screens::offline_menu;
					});
					break;
				default:
					// Resize the button with the chosen scale.
					this->m_button_ptrs[i]->resize(*this, this->m_normal_textures_arr[i], Connect4::Button::MainMenu::NORMAL_SCALE); // Resize to % of window size.

					// Set the position of the button using chosen x and y values ( use the windows as anchors so its dynamically sized ).
					// Dont worry the function takes into account the scaling and calculates using that ( thats why you need to pass the texture ).
					this->m_button_ptrs[i]->set_pos(this->m_normal_textures_arr[i], { getSize().x / 2.0f, getSize().y / 2.0f + 50.0f + (static_cast<float>(i) * 400.0f) });
					break;
				}
			}
		}

		void MainMenu::draw_all() {
			// First clear the screen with the background color.
			this->clear(Color::DarkPurple); 

			// Assets are added here depending on which screen we are on.
			// First check that they exist to avoid drawing when the pointers are null.
			switch (this->m_current_screen)
			{
			case (Screens::main_menu):
				this->draw_main_menu();
				break;
			default:
				break;
			}
			
			// Finally display all thats was been rendered.
			this->display();
		}

		void MainMenu::receive_event(sf::Event& event) {
			// Pass th event to every button to check if one of them is clicked.
			for (std::size_t i{ 0u }; i < this->m_button_ptrs.size(); ++i) {
				this->m_button_ptrs[i]->on_click(event);
			}
		}
	}
}