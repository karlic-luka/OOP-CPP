#include "game.h"
#include <stdexcept>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>

// Kod dopuniti/promijeniti po potrebi.

const double pi = std::acos(-1);

Game::Game() : mWindow(sf::VideoMode(1280, 1024), "SFML window"), numberOfAsteroids(4)
{
    mBackgroundSprite.setTexture(mTextureHolder.getTexture(Textures::background));
    //stvaram igraca
    mPlayer.reset(new Player(mTextureHolder.getTexture(Textures::player)));
    mPlayer->setPosition(mWindow.getSize().x / 2, mWindow.getSize().y / 2);

    //stvaram asteroide
    prepareAsteroids(numberOfAsteroids);

    mDtFixed = sf::seconds(1.0f / 60.0f);

    /*     mExplosion.reset(
        new Animation(mTextureHolder.getTexture(Textures::explosion), 4, 4, 256, 256, 0.2f));
    mExplosion->setPosition(200, 700); */
}

void Game::run()
{
    // Start the game loop
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

void Game::processEvents()
{
    // Process events
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        // Close window : exit
        switch (event.type)
        {
        case sf::Event::Closed:
            mWindow.close();
            break;
        case sf::Event::KeyPressed:
            if (event.key.code == sf::Keyboard::Space)
                //zelim stvoriti bullet
                handleBullet();
            mPlayer->handlePlayerInput(event.key.code, true);
            break;
        case sf::Event::KeyReleased:
            mPlayer->handlePlayerInput(event.key.code, false);
            break;
        }
    }
}

void Game::update(sf::Time dt)
{
    entityTorus(*mPlayer);
    mPlayer->update(dt);
    for (int i = 0; i < numberOfAsteroids; i++)
    {
        entityTorus(*mAsteroids.at(i));
        mAsteroids.at(i)->update(dt);
    }

    for (auto iter = mBullets.begin(); iter != mBullets.end(); ++iter)
        (*iter)->update(dt);

    //zelim izbrisati one koji su izasli iz prozora
    auto iter = mBullets.begin();
    while (iter != mBullets.end())
    {
        auto x = (*iter)->getPosition().x;
        auto y = (*iter)->getPosition().y;
        if (x < 0 || x > mWindow.getSize().x || y < 0 || y > mWindow.getSize().y)
        {
            iter->reset(nullptr);
            mBullets.erase(iter++);
        }
        else
            ++iter;
    }
    //provjeri je li se smanjio size
    //std::cout << mBullets.size() << " " << std::endl;

    //mExplosion->update();
}

void Game::render()
{
    // Clear screen
    mWindow.clear();
    mWindow.draw(mBackgroundSprite);
    // Draw the player
    mWindow.draw(*mPlayer);

    for (int i = 0; i < numberOfAsteroids; i++)
        mWindow.draw(*mAsteroids.at(i));

    for (auto iter = mBullets.begin(); iter != mBullets.end(); ++iter)
        mWindow.draw(**iter);

    //mWindow.draw(*mExplosion);
    // Update the window
    mWindow.display();
}

void Game::prepareAsteroids(int numberOfAsteroids)
{
    mAsteroids.resize(numberOfAsteroids);

    srand((unsigned)time(0));

    for (int i = 0; i < numberOfAsteroids; ++i)
    {
        //random velicina iz [4, 11] u Textures::ID
        Textures::ID size = static_cast<Textures::ID>(rand() % 8 + 4);
        mAsteroids.at(i).reset(new Asteroid(mTextureHolder.getTexture(size)));

        //sada ga zelim random pozicionirati
        int width = rand() % mWindow.getSize().x;
        int height = rand() % mWindow.getSize().y;
        mAsteroids.at(i)->setPosition(width, height);

        //random brzina okretanja
        //+60 je da se barem za toliko okrece
        mAsteroids.at(i)->setRotatingSpeed(rand() % 360 + 60);

        //random orijentacija
        float orientationX = ((rand() % 2) == 0) ? 1.0f : -1.0f;
        float orientationY = ((rand() % 2) == 0) ? 1.0f : -1.0f;
        //random smjer - mVelocity
        //+10 da sam siguran da ne stoji u mjestu
        int x = rand() % mWindow.getSize().x + 10;
        int y = rand() % mWindow.getSize().y + 10;
        mAsteroids.at(i)->setVelocity(sf::Vector2f(x * orientationX, y * orientationY));
    }
}

void Game::handleBullet()
{
    std::unique_ptr<Bullet> temp(new Bullet(mTextureHolder.getTexture(Textures::bullet)));
    sf::Vector2f tempVel;
    tempVel.x = sin(mPlayer->getRotation() * pi / 180);
    tempVel.y = -1.0f * cos(mPlayer->getRotation() * pi / 180);
    temp->setVelocity(tempVel);
    temp->setPosition(mPlayer->getPosition());
    //+90 jer je slicica bulleta horizontalna, zelim da gleda prema gore
    temp->setRotation(mPlayer->getRotation() + 90);
    mBullets.push_back(std::move(temp));
}

void Game::entityTorus(Entity &entity)
{
    sf::Vector2f position = entity.getPosition();
    if (position.x >= mWindow.getSize().x)
        position.x = 0.0f;
    else if (position.x <= 0.0f)
        position.x = mWindow.getSize().x - 1.0f;
    if (position.y <= 0.0f)
        position.y = mWindow.getSize().y - 1;
    else if (position.y >= mWindow.getSize().y)
        position.y = 0.0f;
    entity.setPosition(position);
}