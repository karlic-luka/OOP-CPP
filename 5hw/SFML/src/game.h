#pragma once
#include <stdexcept>
#include <SFML/Graphics.hpp>
#include <iostream>

class Game
{
public:
    Game();
    void run();

private:
    sf::RenderWindow mWindow;
    sf::Sprite mSprite;
    sf::Texture mTexture;

    void processEvents();
    void update(sf::Time dt);
    void render();
    //helper method that handles keys pressed
    //if the key was pressed, we send true, else false
    void handlePlayerInput(sf::Keyboard::Key code, bool isKeyPressed);
    //pomocna funkcija koja vraca vektor smjera
    //cija norma na kvadrat je mVelocity
    void handleMouse(sf::Vector2f &velocity);
    bool mIsMovingUp = false;
    bool mIsMovingDown = false;
    bool mIsMovingLeft = false;
    bool mIsMovingRight = false;
    bool mFollowCursor = false;

    float mVelocity = 120.0f; //pixel/sec
    sf::Time mDtFixed;
};