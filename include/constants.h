#pragma once
// Written in project.
// 3rd party headers.
#include "SFML/Graphics.hpp"
// STL.

namespace Connect4 {
	namespace Color {
		inline constexpr sf::Color DarkPurple{ 85u, 88u, 121u };          // #555879
		inline constexpr sf::Color LightPurple{ 152u, 161u, 188u };       // #98A1BC
		inline constexpr sf::Color LightPurpleHover{ 236u, 239u, 246u };  // #ECEFF6
		inline constexpr sf::Color DarkCream{ 222u, 221u, 196u };         // #DEDDC4
		inline constexpr sf::Color LightCream{ 244u, 235u, 211u };        // #F4EBD3
	}

	namespace Button {
			namespace MainMenu {
				inline constexpr float LOGO_SCALE{ 0.2f }; // 20% of window size
				inline constexpr float NORMAL_SCALE{ 0.1f }; // 10% of window size
				inline constexpr float SMALL_SCALE{ 0.05f }; // 5% of window size
			}
	}
}