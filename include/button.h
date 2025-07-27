#pragma once
// Written in project.
// 3rd party headers.
#include "SFML/Graphics.hpp"
// STL.
#include <iostream>
#include <Windows.h>

namespace Connect4 {
	namespace GUI {
		class Button final {
		private:
			// Sprite for the button.
			sf::Sprite m_sprite;

			// Scale for the button.
			sf::Vector2f m_scale;

			// Bool to hold if the user is hovering or not.
			bool m_is_hovering;
		public:
			// Constructor takes in a texture and position for the button.
			Button(const sf::Texture& texture);

			// Default destructor.
			~Button() = default;

			// Draw the button on the window passed by reference.
			void draw(sf::RenderWindow& window) const;

			// Check if a point is inside the bounds of the button in 2D co-ordinates.
			bool contains(sf::Vector2f point) const;

			// Resizes the button to a specified factor.
			// The factor represents a percentage of the screen size for e.g. 0.2f is 20% of the screen width.
			void resize(sf::RenderWindow& window, const sf::Texture& texture, float factor);

			// Set the position of the button.
			void set_pos(const sf::Texture& texture, sf::Vector2f position_vector);

			// Updates the buttons texture based on the mouse position ( is the user hovering over the button? ).
			// Needs the window to update the cursor for that window.
			void update(sf::RenderWindow& window, sf::Texture& hover_texture, sf::Texture& normal_texture, sf::Vector2f mouse_position);
		};
	}
}