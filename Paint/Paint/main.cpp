#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

float brushR = 10;
sf::Color couleur;
int winsizeX = 1920;
int winsizeY = 1080;
sf::Vector2i lastMousePosition(-1, -1);
bool draw = false;
bool errase = false;

sf::RenderWindow window(sf::VideoMode(winsizeX, winsizeY), "Paint");

sf::Image canvas;
sf::Texture background;
sf::Sprite bgSprite;

sf::RectangleShape redcolor(sf::Vector2f(50, 50));

void Erreurlist(int iderreur) {
	switch (iderreur)
	{
	case 1:
		std::cout << "Erreur, event windows inconnu" << std::endl;
		break;
	default:
		break;
	}
}

void draw_errase() {
    if (draw) {
        sf::Color tempcolor = couleur;
        if (errase) {
            couleur = sf::Color::White;
        }

        sf::Vector2i positionSouris = sf::Mouse::getPosition(window);

        if (lastMousePosition.x != -1 && lastMousePosition.y != -1) {
            float distance = std::sqrt(std::pow(positionSouris.x - lastMousePosition.x, 2) +
                std::pow(positionSouris.y - lastMousePosition.y, 2));

            for (float t = 0; t <= 1; t += 0.1f) {
                int interpolatedX = static_cast<int>(lastMousePosition.x + t * (positionSouris.x - lastMousePosition.x));
                int interpolatedY = static_cast<int>(lastMousePosition.y + t * (positionSouris.y - lastMousePosition.y));

                for (int i = -brushR; i <= brushR; ++i) {
                    for (int j = -brushR; j <= brushR; ++j) {
                        float circleDistance = std::sqrt(std::pow(i, 2) + std::pow(j, 2));
                        if (circleDistance <= brushR) {
                            int pixelX = interpolatedX + i;
                            int pixelY = interpolatedY + j;

                            if (pixelX >= 0 && pixelX < winsizeX && pixelY >= 100 && pixelY < winsizeY) {
                                canvas.setPixel(pixelX, pixelY, couleur);
                            }
                        }
                    }
                }
            }
        }

        for (int i = -brushR; i <= brushR; ++i) {
            for (int j = -brushR; j <= brushR; ++j) {
                float distance = std::sqrt(std::pow(i, 2) + std::pow(j, 2));
                if (distance <= brushR) {
                    int pixelX = positionSouris.x + i;
                    int pixelY = positionSouris.y + j;

                    if (pixelX >= 0 && pixelX < winsizeX && pixelY >= 100 && pixelY < winsizeY) {
                        canvas.setPixel(pixelX, pixelY, couleur);
                    }
                }
            }
        }

        lastMousePosition = positionSouris;

        couleur = tempcolor;
    }
    else {
        lastMousePosition = sf::Vector2i(-1, -1);
    }
}

void init() {
	canvas.create(window.getSize().x, window.getSize().y, sf::Color::White);
	couleur = sf::Color::Black;
    redcolor.setPosition(50, 50);
    redcolor.setFillColor(sf::Color::Red);
}

int main() {
	init();
	while (window.isOpen()) {
		background.loadFromImage(canvas);
		bgSprite.setTexture(background);
		sf::Event event;

		draw_errase();

		while (window.pollEvent(event)) {
			switch (event.type) {
			case sf::Event::MouseButtonPressed:
                if (sf::Mouse::getPosition(window).y >= 100)
                {
                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        errase = true;
                    }
                    draw = true;
                }
                else
                {
                    if (sf::Mouse::getPosition(window).y >= 10)
                    {

                    }
                }
				break;
			case sf::Event::MouseButtonReleased:
				draw = false;
				errase = false;
				break;
			case sf::Event::Closed:
				window.close();
				break;
			default:
				//Erreurlist(1);
				break;
			}
		}
		window.draw(bgSprite);
        window.draw(redcolor);
		window.display();
	}
}