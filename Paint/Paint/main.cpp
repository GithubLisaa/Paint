#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <queue>

int brushR = 10;
sf::Color couleur;
int winglobalX = sf::VideoMode::getDesktopMode().width;
int winglobalY = sf::VideoMode::getDesktopMode().height;
int canvasizeX = sf::VideoMode::getDesktopMode().width - 200;
int canvasizeY = sf::VideoMode::getDesktopMode().height - 200;
int canvaoffsetX = 100;
int canvaoffsetY = 110;
int sizebutton = 30;
sf::Vector2i lastMousePosition(-1, -1);
bool draw = false;
bool erase = false;
bool button = false;
bool sliderspeauto = false;
bool buckethold = false;
bool buckethere = false;
bool safetrigger = false;
bool isFullscreen = false;

sf::RenderWindow window(sf::VideoMode(winglobalX, winglobalY), "Paint");

sf::Font police;
sf::Text texte;
sf::Image canvas;
sf::Texture Tbucket;
sf::Sprite Sbucket;
sf::Texture Ttrash;
sf::Sprite Strash;
sf::Sprite Sbucketmouse;
sf::Texture Tsave;
sf::Sprite Ssave;
sf::Texture paper;
sf::Sprite bgSprite;
sf::Texture Tsight;
sf::Sprite Ssight;

sf::Color backgroundColor = sf::Color(220, 220, 220);

sf::RectangleShape barmenu(sf::Vector2f(winglobalX, 100));

sf::RectangleShape sliderbarsaizeB;
sf::CircleShape sliderHandlesizeB(14);
sf::CircleShape colorinfo(10);

sf::RectangleShape blackcolor(sf::Vector2f(sizebutton, sizebutton));
sf::RectangleShape redcolor(sf::Vector2f(sizebutton, sizebutton));
sf::RectangleShape bluecolor(sf::Vector2f(sizebutton, sizebutton));
sf::RectangleShape greencolor(sf::Vector2f(sizebutton, sizebutton));
sf::RectangleShape whitecolor(sf::Vector2f(sizebutton, sizebutton));
sf::RectangleShape purplecolor(sf::Vector2f(sizebutton, sizebutton));

void init() {
    canvas.create(canvasizeX, canvasizeY, sf::Color::White);
    police.loadFromFile("arial.ttf");
    Tbucket.loadFromFile("bucket.png");
    Sbucket.setTexture(Tbucket);
    Sbucketmouse.setTexture(Tbucket);
    Ttrash.loadFromFile("trash.png");
    Strash.setTexture(Ttrash);
    Tsave.loadFromFile("save.png");
    Ssave.setTexture(Tsave);
    Tsight.loadFromFile("cursor.png");
    Ssight.setTexture(Tsight);

    couleur = sf::Color::Black;

    barmenu.setFillColor(sf::Color(192, 192, 192));

    sliderbarsaizeB.setSize(sf::Vector2f(200, 20));
    sliderbarsaizeB.setFillColor(sf::Color::White);
    sliderbarsaizeB.setPosition(200, 40);

    sliderHandlesizeB.setFillColor(sf::Color(128, 128, 128));
    sliderHandlesizeB.setPosition(200, 36);

    colorinfo.setFillColor(couleur);

    texte.setFont(police);
    texte.setPosition(275, 60);
    texte.setFillColor(sf::Color::Black);
    texte.setString(std::to_string(brushR));

    blackcolor.setPosition(15, 17);
    blackcolor.setFillColor(sf::Color::Black);

    whitecolor.setPosition(15, 58);
    whitecolor.setFillColor(sf::Color::White);

    redcolor.setPosition(58, 17);
    redcolor.setFillColor(sf::Color::Red);

    bluecolor.setPosition(58, 58);
    bluecolor.setFillColor(sf::Color::Blue);

    greencolor.setPosition(101, 58);
    greencolor.setFillColor(sf::Color::Green);

    purplecolor.setPosition(101, 17);
    purplecolor.setFillColor(sf::Color::Magenta);

    Sbucket.setScale(0.1f, 0.1f);
    Sbucket.setPosition(500, 20);

    Ssave.setScale(0.1f, 0.1f);
    Ssave.setPosition(1800, 20);

    Strash.setScale(0.1f, 0.1f);
    Strash.setPosition(1400, 20);
}

void affichage() {
    window.clear(backgroundColor);
    paper.loadFromImage(canvas);
    bgSprite.setTexture(paper);
    bgSprite.setPosition(canvaoffsetX, canvaoffsetY);
    window.draw(bgSprite);
    window.draw(colorinfo);
    window.draw(barmenu);
    window.draw(Sbucket);
    window.draw(Sbucketmouse);
    window.draw(sliderbarsaizeB);
    window.draw(sliderHandlesizeB);
    window.draw(texte);
    window.draw(redcolor);
    window.draw(whitecolor);
    window.draw(blackcolor);
    window.draw(bluecolor);
    window.draw(greencolor);
    window.draw(purplecolor);
    window.draw(Ssave);
    window.draw(Strash);
    window.draw(Ssight);
    window.display();
}

void checkpixels(int x, int y, sf::Color oldcolor) {
    if (oldcolor == couleur) return;

    std::queue<sf::Vector2i> pixels;
    pixels.push({ x, y });

    while (!pixels.empty()) {
        sf::Vector2i current = pixels.front();
        pixels.pop();

        int cx = current.x;
        int cy = current.y;

        if (cx < 0 || cx >= canvas.getSize().x || cy < 0 || cy >= canvas.getSize().y)
            continue;

        if (canvas.getPixel(cx, cy) != oldcolor)
            continue;

        canvas.setPixel(cx, cy, couleur);

        pixels.push({ cx + 1, cy });
        pixels.push({ cx - 1, cy });
        pixels.push({ cx, cy + 1 });
        pixels.push({ cx, cy - 1 });
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
    sf::FloatRect trashbutton = Strash.getGlobalBounds();

    sf::FloatRect blackcolorbutton = blackcolor.getGlobalBounds();
    sf::FloatRect redcolorbutton = redcolor.getGlobalBounds();
    sf::FloatRect bluecolorbutton = bluecolor.getGlobalBounds();
    sf::FloatRect greencolorbutton = greencolor.getGlobalBounds();
    sf::FloatRect whitecolorbutton = whitecolor.getGlobalBounds();
    sf::FloatRect purplecolorbutton = purplecolor.getGlobalBounds();

    if (blackcolorbutton.contains(sf::Vector2f(positionSouris)) && button)
    {
        couleur = sf::Color::Black;
        button = false;
    }
    if (redcolorbutton.contains(sf::Vector2f(positionSouris)) && button)
    {
        couleur = sf::Color::Red;
        button = false;
    }
    if (bluecolorbutton.contains(sf::Vector2f(positionSouris)) && button)
    {
        couleur = sf::Color::Blue;
        button = false;
    }
    if (greencolorbutton.contains(sf::Vector2f(positionSouris)) && button)
    {
        couleur = sf::Color::Green;
        button = false;
    }
    if (purplecolorbutton.contains(sf::Vector2f(positionSouris)) && button)
    {
        couleur = sf::Color::Magenta;
        button = false;
    }
    if (whitecolorbutton.contains(sf::Vector2f(positionSouris)) && button)
    {
        couleur = sf::Color::White;
        button = false;
    }
    if (bucketbutton.contains(sf::Vector2f(positionSouris)) && button || buckethold || buckethere)
    {
        button = false;
        buckethold = true;
        if (buckethere)
        {
            buckethere = false;
            buckethold = false;
            if (positionSouris.x < canvaoffsetX || positionSouris.x >= canvas.getSize().x || positionSouris.y < canvaoffsetY || positionSouris.y >= canvas.getSize().y) return;
            checkpixels(positionSouris.x - canvaoffsetX, positionSouris.y - canvaoffsetY, canvas.getPixel(positionSouris.x - canvaoffsetX, positionSouris.y - canvaoffsetY));
        }
    }
    if (trashbutton.contains(sf::Vector2f(positionSouris)) && button && !safetrigger)
    {
        button = false;
        safetrigger = true;
        for (int y = 0; y < canvas.getSize().y; y++)
        {
            for (int x = 0; x < canvas.getSize().x; x++)
            {
                canvas.setPixel(x, y, sf::Color::White);
            }
        }
    }
    if (savebutton.contains(sf::Vector2f(positionSouris)) && button && !safetrigger)
    {
        button = false;
        safetrigger = true;
        canvas.saveToFile(std::string("Paint_saves/test.png"));
    }
    if (slidersizeB.contains(sf::Vector2f(positionSouris)) && button || sliderspeauto)
    {
        button = false;
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

void draw_erase() {
    if (draw) {
        sf::Color tempcolor = couleur;
        if (erase) {
            couleur = sf::Color::White;
        }
        float dT = 0.1f;
        sf::Vector2i positionSouris = sf::Mouse::getPosition(window);
        positionSouris.x -= canvaoffsetX;
        positionSouris.y -= canvaoffsetY;

        if (lastMousePosition.x != -1 && lastMousePosition.y != -1) {
            float distance = std::sqrt(std::pow(positionSouris.x - lastMousePosition.x, 2) + std::pow(positionSouris.y - lastMousePosition.y, 2));
            if (brushR < 10)
            {
                dT = 0.01f;
            }
            else
            {
                dT = 0.1f;
            }

            for (float t = 0; t <= 1; t += dT) {
                int interpolatedX = static_cast<int>(lastMousePosition.x + t * (positionSouris.x - lastMousePosition.x));
                int interpolatedY = static_cast<int>(lastMousePosition.y + t * (positionSouris.y - lastMousePosition.y));

                for (int i = -brushR; i <= brushR; ++i) {
                    for (int j = -brushR; j <= brushR; ++j) {
                        float circleDistance = std::sqrt(std::pow(i, 2) + std::pow(j, 2));
                        if (circleDistance <= brushR &&
                            interpolatedX + i >= 0 && interpolatedX + i < canvasizeX &&
                            interpolatedY + j >= 0 && interpolatedY + j < canvasizeY) {
                            canvas.setPixel(interpolatedX + i, interpolatedY + j, couleur);
                        }
                    }
                }
            }
        }

        for (int i = -brushR; i <= brushR; ++i) {
            for (int j = -brushR; j <= brushR; ++j) {
                float distance = std::sqrt(std::pow(i, 2) + std::pow(j, 2));
                if (distance <= brushR &&
                    positionSouris.x + i >= 0 && positionSouris.x + i < canvasizeX &&
                    positionSouris.y + j >= 0 && positionSouris.y + j < canvasizeY) {
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
        sf::Event event;

        draw_erase();
        witchbuttonpressed();

        while (window.pollEvent(event)) {
            switch (event.type) {
            case sf::Event::MouseButtonPressed:
                if (sf::Mouse::getPosition(window).y >= canvaoffsetY)
                {
                    if (event.mouseButton.button == sf::Mouse::Right)
                    {
                        erase = true;
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
                erase = false;
                button = false;
                sliderspeauto = false;
                if (buckethold && event.mouseButton.button == sf::Mouse::Left)
                {
                    buckethere = true;
                }
                safetrigger = false;
                break;
            case sf::Event::MouseMoved:
                if (sf::Mouse::getPosition(window).y <= canvaoffsetY)
                {
                    if (buckethold)
                    {
                        window.setMouseCursorVisible(false);
                        Sbucketmouse.setPosition(sf::Mouse::getPosition(window).x - (Sbucketmouse.getGlobalBounds().width * 0.5f), sf::Mouse::getPosition(window).y - (Sbucketmouse.getGlobalBounds().height * 0.5f));
                        Sbucketmouse.setScale(0.05f, 0.05f);
                        Sbucketmouse.setColor(couleur);
                        Ssight.setScale(0, 0);
                    }
                    else
                    {
                        window.setMouseCursorVisible(true);
                        colorinfo.setScale(0, 0);
                        Sbucketmouse.setScale(0, 0);
                        Ssight.setScale(0, 0);
                    }
                }
                else
                {
                    window.setMouseCursorVisible(false);
                    if (!buckethold)
                    {
                        colorinfo.setScale(brushR / 10.0f, brushR / 10.0f);
                        colorinfo.setFillColor(couleur);
                        colorinfo.setPosition(sf::Mouse::getPosition(window).x - (colorinfo.getGlobalBounds().width * 0.5f), sf::Mouse::getPosition(window).y - (colorinfo.getGlobalBounds().height * 0.5f));
                        Ssight.setScale(0.09f, 0.09f);
                        if (couleur == sf::Color::Black)
                        {
                            Ssight.setColor(sf::Color(255, 255, 255, 100));
                        }
                        else
                        {
                            Ssight.setColor(sf::Color(0, 0, 0, 200));
                        }
                        Ssight.setPosition(sf::Mouse::getPosition(window).x - (Ssight.getGlobalBounds().width * 0.5f), sf::Mouse::getPosition(window).y - (Ssight.getGlobalBounds().height * 0.5f));
                        Sbucketmouse.setScale(0, 0);
                    }
                    else
                    {
                        colorinfo.setScale(0, 0);
                        Sbucketmouse.setPosition(sf::Mouse::getPosition(window).x - (Sbucketmouse.getGlobalBounds().width * 0.5f), sf::Mouse::getPosition(window).y - (Sbucketmouse.getGlobalBounds().height * 0.5f));
                    }
                }
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::F11)
                {
                    isFullscreen = !isFullscreen;
                    if (isFullscreen) {
                        window.create(sf::VideoMode::getDesktopMode(), "Paint", sf::Style::Fullscreen);
                    }
                    else {
                        window.create(sf::VideoMode(winglobalX, winglobalY), "Paint", sf::Style::Default);
                    }
                }
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