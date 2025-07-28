// Written in project.
#include "button.h"
// 3rd party headers.
// STL.

namespace Connect4 {
	namespace GUI {
		/*
		=================
			PRIVATE
		=================
		*/

		/*
		=================
			PUBLIC
		=================
		*/

		Button::Button(const sf::Texture& texture) : 
			m_sprite(texture),
			m_scale({0.0f, 0.0f}),
			m_is_hovering(false)
		{
			this->m_sprite.setTexture(texture);
		}

		void Button::draw(sf::RenderWindow& window) const {
			window.draw(this->m_sprite);
		}

		bool Button::contains(sf::Vector2f point) const {
			return this->m_sprite.getGlobalBounds().contains(point); // Check that the bounds containes the given point.
		}

		void Button::resize(sf::RenderWindow& window, const sf::Texture& texture, float factor) {
			float scale_x{ (window.getSize().x * factor) / texture.getSize().x }; // Factor dictates % of screen width.
			float scale_y{ scale_x }; // Maintain aspect ratio.

			// Set the scale to the new scale.
			this->m_scale = { scale_x, scale_y };

			this->m_sprite.setScale(sf::Vector2f(scale_x, scale_y)); // Simply set the scale.
		}

		void Button::set_pos(const sf::Texture& texture, sf::Vector2f position_vector) {

			// Get the transformed x and y which takes into account the scale value along with the size of the actual button.
			float transformed_x{ position_vector.x - (texture.getSize().x * this->m_scale.x) / 2 };
			float transformed_y{ position_vector.y - (texture.getSize().y * this->m_scale.y) / 2 };

			// Set the scaled dimensions of the sprite.
			this->m_sprite.setPosition({ transformed_x , transformed_y});
		}

		void Button::update(sf::RenderWindow& window, sf::Texture& hover_texture, sf::Texture& normal_texture, sf::Vector2f mouse_position) {
			if (this->contains(mouse_position) && m_is_hovering == false) {
				m_sprite.setTexture(hover_texture);
				m_is_hovering = true;
				window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Hand));
			}

			if (!this->contains(mouse_position) && m_is_hovering == true) {
				m_sprite.setTexture(normal_texture);
				m_is_hovering = false;
				window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
			}
		}

		void Button::set_on_click(std::function<void()> func) {
			this->m_on_click = std::move(func);
		}

		void Button::on_click(const sf::Event& event, sf::RenderWindow& window) {
			// Get pointer to mouse button pressed event.
			if (auto mb{ event.getIf<sf::Event::MouseButtonPressed>() }) {
				// Only handle left clicks.
				if (mb->button == sf::Mouse::Button::Left) {
					// Get position of mouse
					sf::Vector2f mouse_pos(static_cast<float>(mb->position.x), static_cast<float>(mb->position.y));
					// Check if mouse is in bounds of the button and that m_on_click exists.
					if (this->contains(mouse_pos) && this->m_on_click) {
						// Finally call the on click method.
						this->m_on_click();
						// Set the cursor back to the arrow.
						window.setMouseCursor(sf::Cursor(sf::Cursor::Type::Arrow));
					}
				}
			}
		}
	}
}