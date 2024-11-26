#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

int brushR = 10;
sf::Color couleur;
int winsizeX = 1920;
int winsizeY = 1080;
int sizebutton = 30;
sf::Vector2i lastMousePosition(-1, -1);
bool draw = false;
bool errase = false;
bool button = false;
bool sliderspeauto = false;
bool buckethold = false;
bool buckethere = false;
bool savetrigger = false;

sf::RenderWindow window(sf::VideoMode(winsizeX, winsizeY), "Paint");

sf::Font police;
sf::Text texte;
sf::Image canvas;
sf::Texture Tbucket;
sf::Sprite Sbucket;
sf::Texture Tsave;
sf::Sprite Ssave;
sf::Texture background;
sf::Sprite bgSprite;

sf::RectangleShape barmenu(sf::Vector2f(winsizeX, 100));

sf::RectangleShape sliderbarsaizeB;
sf::CircleShape sliderHandlesizeB(14);

sf::RectangleShape blackcolor(sf::Vector2f(sizebutton, sizebutton));
sf::RectangleShape redcolor(sf::Vector2f(sizebutton, sizebutton));
sf::RectangleShape bluecolor(sf::Vector2f(sizebutton, sizebutton));
sf::RectangleShape greencolor(sf::Vector2f(sizebutton, sizebutton));

void init() {
    canvas.create(window.getSize().x, window.getSize().y, sf::Color::White);
    police.loadFromFile("arial.ttf");
    Tbucket.loadFromFile("bucket.png");
    Sbucket.setTexture(Tbucket);
    Tsave.loadFromFile("save.png");
    Ssave.setTexture(Tsave);
    couleur = sf::Color::Black;

    barmenu.setFillColor(sf::Color(211, 211, 211));

    sliderbarsaizeB.setSize(sf::Vector2f(200, 20));
    sliderbarsaizeB.setFillColor(sf::Color::White);
    sliderbarsaizeB.setPosition(200, 40);

    sliderHandlesizeB.setFillColor(sf::Color(128, 128, 128));
    sliderHandlesizeB.setPosition(200, 36);

    texte.setFont(police);
    texte.setPosition(275, 60);
    texte.setFillColor(sf::Color::Black);
    texte.setString(std::to_string(brushR));

    blackcolor.setPosition(15, 17);
    blackcolor.setFillColor(sf::Color::Black);

    redcolor.setPosition(15, 58);
    redcolor.setFillColor(sf::Color::Red);

    bluecolor.setPosition(58, 17);
    bluecolor.setFillColor(sf::Color::Blue);

    greencolor.setPosition(58, 58);
    greencolor.setFillColor(sf::Color::Green);

    Sbucket.setScale(0.10f, 0.10f);
    Sbucket.setPosition(500, 20);

    Ssave.setScale(0.10f, 0.10f);
    Ssave.setPosition(1800, 20);
}

void affichage() {
    window.draw(bgSprite);
    window.draw(barmenu);
    window.draw(Sbucket);
    window.draw(sliderbarsaizeB);
    window.draw(sliderHandlesizeB);
    window.draw(texte);
    window.draw(redcolor);
    window.draw(blackcolor);
    window.draw(bluecolor);
    window.draw(greencolor);
    window.draw(Ssave);
    window.display();
}

void checkpixels(int x, int y, sf::Color oldcolor) {
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (y + i >= 100 && y + i < winsizeY && x + j >= 0 && x + j < winsizeX) {
                if (canvas.getPixel(x, y) == oldcolor) {
                    if (canvas.getPixel(x + i, y + j) == oldcolor)
                    {
                        canvas.setPixel(x + i, y + j, couleur);
                        checkpixels(x + j, y + i, oldcolor);
                    }
                    else {
                        canvas.setPixel(x, y, couleur);
                    }
                }
            }
        }
    }
}

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

void witchbuttonpressed() {
    sf::Vector2i positionSouris = sf::Mouse::getPosition(window);

    sf::FloatRect slidersizeB = sliderbarsaizeB.getGlobalBounds();

    sf::FloatRect bucketbutton = Sbucket.getGlobalBounds();
    sf::FloatRect savebutton = Ssave.getGlobalBounds();

    sf::FloatRect blackcolorbutton = blackcolor.getGlobalBounds();
    sf::FloatRect redcolorbutton = redcolor.getGlobalBounds();
    sf::FloatRect bluecolorbutton = bluecolor.getGlobalBounds();
    sf::FloatRect greencolorbutton = greencolor.getGlobalBounds();

    if (blackcolorbutton.contains(sf::Vector2f(positionSouris)) && button)
    {
        couleur = sf::Color::Black;
    }
    if (redcolorbutton.contains(sf::Vector2f(positionSouris)) && button)
    {
        couleur = sf::Color::Red;
    }
    if (bluecolorbutton.contains(sf::Vector2f(positionSouris)) && button)
    {
        couleur = sf::Color::Blue;
    }
    if (greencolorbutton.contains(sf::Vector2f(positionSouris)) && button)
    {
        couleur = sf::Color::Green;
    }
    if (bucketbutton.contains(sf::Vector2f(positionSouris)) && button || buckethold || buckethere)
    {
        buckethold = true;
        if (buckethere)
        {
            buckethere = false;
            checkpixels(positionSouris.x, positionSouris.y, canvas.getPixel(positionSouris.x, positionSouris.y));
        }
        /*for (int y = 0; y < canvas.getSize().y; y++)
        {
            for (int x = 0; x < canvas.getSize().x; x++)
            {
                canvas.setPixel(x, y, couleur);
            }
        }*/
    }
    if (savebutton.contains(sf::Vector2f(positionSouris)) && button && !savetrigger)
    {
        savetrigger = true;
        canvas.saveToFile(std::string("Saves/test.png"));
    }
    if (slidersizeB.contains(sf::Vector2f(positionSouris)) && button || sliderspeauto)
    {
        sliderspeauto = true;
        if (slidersizeB.contains(positionSouris.x, slidersizeB.getPosition().y))
        {
            sliderHandlesizeB.setPosition(positionSouris.x - sliderHandlesizeB.getRadius(), sliderHandlesizeB.getPosition().y);
        }
        else
        {
            if (positionSouris.x < slidersizeB.getPosition().x)
            {
                sliderHandlesizeB.setPosition((sliderbarsaizeB.getPosition().x - sliderHandlesizeB.getRadius()), sliderHandlesizeB.getPosition().y);
            }
            else
            {
                sliderHandlesizeB.setPosition((sliderbarsaizeB.getPosition().x + sliderbarsaizeB.getSize().x - sliderHandlesizeB.getRadius()), sliderHandlesizeB.getPosition().y);
            }
        }
        brushR = std::max<int>(1, std::min<int>(100, (positionSouris.x - sliderbarsaizeB.getPosition().x) / sliderbarsaizeB.getSize().x * 100));
        texte.setString(std::to_string(brushR));
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
                        if (circleDistance <= brushR && interpolatedX + i >= 0 && interpolatedX + i < winsizeX && interpolatedY + j >= 100 && interpolatedY + j < winsizeY) {
                            canvas.setPixel(interpolatedX + i, interpolatedY + j, couleur);
                        }
                    }
                }
            }
        }

        for (int i = -brushR; i <= brushR; ++i) {
            for (int j = -brushR; j <= brushR; ++j) {
                float distance = std::sqrt(std::pow(i, 2) + std::pow(j, 2));
                if (distance <= brushR && positionSouris.x + i >= 0 && positionSouris.x + i < winsizeX && positionSouris.y + j >= 100 && positionSouris.y + j < winsizeY) {
                    canvas.setPixel(positionSouris.x + i, positionSouris.y + j, couleur);
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

int main() {
    init();
    while (window.isOpen()) {
        background.loadFromImage(canvas);
        bgSprite.setTexture(background);
        sf::Event event;

        draw_errase();
        witchbuttonpressed();

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
                    button = true;
                }
                break;
            case sf::Event::MouseButtonReleased:
                draw = false;
                errase = false;
                button = false;
                sliderspeauto = false;
                if (buckethold)
                {
                    buckethold = false;
                    buckethere = true;
                }
                savetrigger = false;
                break;
            case sf::Event::Closed:
                window.close();
                break;
            default:
                //Erreurlist(1);
                break;
            }
        }
        affichage();
    }
}