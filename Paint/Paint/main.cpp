#include <SFML/Graphics.hpp>

int size = 0;

sf::RenderWindow window(sf::VideoMode(1400, 800), "Paint");

sf::CircleShape brush(10);

void brosse(sf::Color couleur) {
	brush.setFillColor(couleur);
}

int main() {
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::MouseButtonPressed:
				brosse(sf::Color::Black);
				break;
			case sf::Event::KeyPressed:
				break;
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
	}
}