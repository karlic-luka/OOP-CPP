#include "game.h"
#include <math.h>

Game::Game() : mWindow(sf::VideoMode(400, 400), "SFML window")
{
    if (!mTexture.loadFromFile("/mnt/c/Users/Luka/Desktop/PMF-math/3.godina/ObjektnoC++/zadace/5dz/SFML/data/cb.bmp"))
        throw std::runtime_error("Cannot open file cb.bmp!");
    mSprite.setTexture(mTexture);
    mDtFixed = sf::seconds(1.0f / 60.0f);
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        processEvents();
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate >= mDtFixed)
        {
            timeSinceLastUpdate -= mDtFixed;
            processEvents();
            update(mDtFixed);
        }
        render();
    }
}
void Game::handlePlayerInput(sf::Keyboard::Key code, bool isKeyPressed)
{
    switch (code)
    {
    case sf::Keyboard::Up:
        mIsMovingUp = isKeyPressed;
        break;
    case sf::Keyboard::Down:
        mIsMovingDown = isKeyPressed;
        break;
    case sf::Keyboard::Left:
        mIsMovingLeft = isKeyPressed;
        break;
    case sf::Keyboard::Right:
        mIsMovingRight = isKeyPressed;
        break;
    }
}
void Game::processEvents()
{
    // Process events
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            mWindow.close();
            break;
        case sf::Event::KeyPressed:
            handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            handlePlayerInput(event.key.code, false);
            break;
        case sf::Event::Resized:
            /*
            std::cout << "new width: " << event.size.width << std::endl;
            std::cout << "new height: " << event.size.height << std::endl;
            std::cout << "new window bounds: (" << mWindow.getSize().x << ","
            << mWindow.getSize().y << ")" << std::endl;
            std::cout << "new sprite position: (" << mSprite.getPosition().x << ","
            << mSprite.getPosition().y << ")" << std::endl;
            std::cout << "new sprite bounds: (" << mSprite.getGlobalBounds().width << ","
            << mSprite.getGlobalBounds().height << ")" << std::endl;
            std::cout << "new mouse position: (" << sf::Mouse::getPosition(mWindow).x << ","
            << sf::Mouse::getPosition(mWindow).x << ")" << std::endl;
            */

            // update the view to the new size of the window
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            mWindow.setView(sf::View(visibleArea));
            break;
        }
    }
    sf::FloatRect spriteBounds = mSprite.getGlobalBounds();
    //da bi me bilo briga je li mis stisnut, prvo se moram pozicionirat(ako prethodno nisam)
    if (!mFollowCursor && spriteBounds.contains(sf::Mouse::getPosition(mWindow).x, sf::Mouse::getPosition(mWindow).y))
        mFollowCursor = true;
}

void Game::update(sf::Time dt)
{
    sf::Vector2f velocity(0.f, 0.f);
    if (mIsMovingUp)
        velocity.y -= mVelocity;
    if (mIsMovingDown)
        velocity.y += mVelocity;
    if (mIsMovingRight)
        velocity.x += mVelocity;
    if (mIsMovingLeft)
        velocity.x -= mVelocity;
    if (mFollowCursor)
    {
        //provjeravam je li stisnut mis samo kad se vec nalazim unutar spritea
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Mouse::isButtonPressed(sf::Mouse::Right))
            handleMouse(velocity); //prima referencu
        //vise nije stisnut mis pa mi nije bitno nalazi li se unutar spritea, stoga ga vracam na false tako
        //da mogu opet skuziti kada se mis nalazi nad spriteom
        else
            mFollowCursor = false;
    }
    mSprite.move(velocity * dt.asSeconds());
}

void Game::render()
{
    // Clear screen
    mWindow.clear();
    // Draw the sprite
    mWindow.draw(mSprite);
    // Update the window
    mWindow.display();
}

void Game::handleMouse(sf::Vector2f &velocity)
{
    velocity.x = sf::Mouse::getPosition(mWindow).x - mSprite.getPosition().x;
    velocity.y = sf::Mouse::getPosition(mWindow).y - mSprite.getPosition().y;
    //zelim dobiti jedinicni vektor u smjeru kursora
    float modulus = (float)std::sqrt((velocity.x * velocity.x + velocity.y * velocity.y));
    if (std::abs(modulus - 0.0f) < 1e-4)
        modulus = 1.0f; //ne zelim nulu
    velocity *= (1.0f / modulus);
    //nula se pojavljuje akko su kursor i sprite na istoj lokaciji - u tom slucaju nista nemoj ciniti
    velocity *= mVelocity; //skaliram tako da se pomicem uvijek istom brzinom
}