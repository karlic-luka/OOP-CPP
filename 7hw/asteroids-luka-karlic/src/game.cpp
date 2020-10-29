#include "game.h"
#include <stdexcept>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>

const double pi = std::acos(-1);

Game::Game() : mWindow(sf::VideoMode(1280, 1024), "SFML window"), mNumberOfAsteroids(6), mGameIsRunning(true)
{
    mBackgroundSprite.setTexture(mTextureHolder.getTexture(Textures::background));
    if (!mFont.loadFromFile("neuropol_x_rg.ttf"))
        throw std::runtime_error("Can not open neuropol_x_rg.ttf");
    textSetup();
    //stvaram igraca
    mPlayer.reset(new Player(mTextureHolder.getTexture(Textures::player)));
    mPlayer->setPosition(mWindow.getSize().x / 2, mWindow.getSize().y / 2);
    //stvaram asteroide
    prepareAsteroids(mNumberOfAsteroids);

    mDtFixed = sf::seconds(1.0f / 60.0f);
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
                if (mGameIsRunning)
                    handleBullet();
                else
                    restartGame();
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
    if (gameIsOver())
    {
        //inace mi je zadnja eksplozija ostala neucitana do kraja
        for (auto explosion = mExplosions.begin(); explosion != mExplosions.end(); ++explosion)
            (*explosion)->update();
        mGameIsRunning = false;
        return;
    }
    entityTorus(*mPlayer);
    //treba provjeriti kolizije
    handleAllCollisions();
    //updejtaj sve
    mPlayer->update(dt);
    for (auto asteroid = mAsteroids.begin(); asteroid != mAsteroids.end(); ++asteroid)
        (*asteroid)->update(dt);
    for (auto bullet = mBullets.begin(); bullet != mBullets.end(); ++bullet)
        (*bullet)->update(dt);
    for (auto explosion = mExplosions.begin(); explosion != mExplosions.end(); ++explosion)
        (*explosion)->update();
    //zelim izbrisati one asteroide koji su razneseni
    mAsteroids.erase(std::remove_if(mAsteroids.begin(), mAsteroids.end(),
                                    [&](std::unique_ptr<Asteroid> &asteroid) { return !asteroid->isAlive; }),
                     mAsteroids.end());
    //zelim izbrisati one eksplozije koje su se nacrtale
    mExplosions.erase(std::remove_if(mExplosions.begin(), mExplosions.end(),
                                     [&](std::unique_ptr<Animation> &explosion) { return !explosion->isAlive; }),
                      mExplosions.end());
    //zelim izbrisati one koji su izasli iz prozora
    mBullets.erase(std::remove_if(mBullets.begin(), mBullets.end(),
                                  [&](std::unique_ptr<Bullet> &bullet) { return bullet->getPosition().x < 0 ||
                                                                                bullet->getPosition().x > 1280 || bullet->getPosition().y < 0 || bullet->getPosition().y > 1024; }),
                   mBullets.end());
    //provjeri je li se smanjio size
    //   std::cout << "mBullets: " << mBullets.size() << " " << std::endl;
    //   std::cout << "mExplosions: " << mExplosions.size() << " " << std::endl;
    //   std::cout << "mAsteroids: " << mAsteroids.size() << " "<< std::endl;
}

void Game::render()
{
    // Clear screen
    mWindow.clear();
    mWindow.draw(mBackgroundSprite);
    
    mWindow.draw(*mPlayer);

    for (auto &asteroid : mAsteroids)
        mWindow.draw(*asteroid);
    for (auto &bullet : mBullets)
        mWindow.draw(*bullet);
    for (auto &explosion : mExplosions)
        mWindow.draw(*explosion);

    mWindow.draw(mUpperLeftText);
    mWindow.draw(mUpperRightText);
    updateText();
    mWindow.display();
}

void Game::prepareAsteroids(int numberOfAsteroids)
{
    srand((unsigned)time(0));
    for (int i = 0; i < numberOfAsteroids; ++i)
    {
        //random velicina iz [4, 11] u Textures::ID
        Textures::ID size = static_cast<Textures::ID>(rand() % 8 + 4);
        std::unique_ptr<Asteroid> temp(new Asteroid(mTextureHolder.getTexture(size)));
        if (4 <= size && size <= 7) //ako je veliki meteor
            temp->worth = 10;
        else if (size == 8 || size == 9) //ako je srednji meteor
            temp->worth = 20;
        else
            temp->worth = 40; //inace je mali meteor

        //sada ga zelim random pozicionirati
        int width = rand() % mWindow.getSize().x;
        int height = rand() % mWindow.getSize().y;
        temp->setPosition(width, height);

        //random brzina okretanja
        //+150 je da se barem za toliko okrece
        temp->setRotatingSpeed(rand() % 360 + 150);

        //random orijentacija
        float orientationX = ((rand() % 2) == 0) ? 1.0f : -1.0f;
        float orientationY = ((rand() % 2) == 0) ? 1.0f : -1.0f;
        //random smjer - mVelocity
        //+250 da sam siguran da ne stoji u mjestu
        int x = rand() % mWindow.getSize().x + 250;
        int y = rand() % mWindow.getSize().y + 250;
        temp->setVelocity(sf::Vector2f(x * orientationX, y * orientationY));
        mAsteroids.push_back(std::move(temp));
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

bool Game::entitiesAreInCollision(const Entity &first, const Entity &second)
{
    auto circle1 = first.getCircle();
    auto circle2 = second.getCircle();
    auto radius1 = circle1.getRadius();
    auto radius2 = circle2.getRadius();

    return !(norm2(first.getPosition(), second.getPosition()) > (radius1 + radius2));
}

double Game::norm2(sf::Vector2f first, sf::Vector2f second)
{
    sf::Vector2f temp = first - second;
    return sqrt(temp.x * temp.x + temp.y * temp.y);
}

void Game::playerGotHit()
{
    if (alreadySubtractedLife)
        return;
    else
    {
        mNumberOfLives--;
        alreadySubtractedLife = true;
        handleAnimation(mPlayer->getPosition());

        if (mNumberOfLives == 0){
            mPlayer->isAlive = false;
            return;
        }
        else
            mPlayer->setPosition(mWindow.getSize().x / 2, mWindow.getSize().y / 2);
    }
}

void Game::asteroidGotHit(Asteroid &asteroid, Bullet &bullet)
{
    srand((unsigned)time(0));
    asteroid.isAlive = false;
    bullet.isAlive = false;
    handleAnimation(bullet.getPosition());
    mScore += asteroid.worth;
    if (asteroid.worth == 10)
    { //pogodio sam velikog
        std::unique_ptr<Asteroid> new1(new Asteroid(mTextureHolder.getTexture(Textures::meteorSmall1)));
        new1->setRotatingSpeed(rand() % 360 + 120);
        new1->setPosition(bullet.getPosition().x - 2, bullet.getPosition().y);
        int x = rand() % mWindow.getSize().x + 10;
        int y = rand() % mWindow.getSize().y + 10;
        new1->setVelocity(sf::Vector2f(x, y));
        new1->worth = 40;

        std::unique_ptr<Asteroid> new2(new Asteroid(mTextureHolder.getTexture(Textures::meteorSmall1)));
        new2->setRotatingSpeed(rand() % 360 + 120);
        new2->setPosition(bullet.getPosition().x + 2, bullet.getPosition().y);
        x = rand() % mWindow.getSize().x + 10;
        y = rand() % mWindow.getSize().y + 10;
        new2->setVelocity(sf::Vector2f(-x, -y));
        new2->worth = 40;

        mAsteroids.push_back(std::move(new1));
        mAsteroids.push_back(std::move(new2));
    }
}

void Game::textSetup()
{
    mUpperRightText.setFont(mFont);
    mUpperRightText.setPosition(1050, 10);
    mUpperRightText.setCharacterSize(25);

    mUpperLeftText.setFont(mFont);
    mUpperLeftText.setPosition(40, 10);
    mUpperLeftText.setCharacterSize(25);
}

void Game::updateText()
{
    mUpperRightText.setString("Score: " + std::to_string(mScore));
    if (mGameIsRunning)
        mUpperLeftText.setString("Lives: " + std::to_string(mNumberOfLives));
    else
        mUpperLeftText.setString("GAME OVER!\nPress space to restart!");
}

bool Game::gameIsOver()
{
    return mNumberOfLives == 0 || mAsteroids.size() == 0;
}

void Game::restartGame()
{
    mPlayer.reset(new Player(mTextureHolder.getTexture(Textures::player)));
    mPlayer->setPosition(mWindow.getSize().x / 2, mWindow.getSize().y / 2);

    while (mAsteroids.begin() != mAsteroids.end())
        mAsteroids.erase(mAsteroids.begin()++);
    while (mBullets.begin() != mBullets.end())
        mBullets.erase(mBullets.begin()++);
    while (mExplosions.begin() != mExplosions.end())
        mExplosions.erase(mExplosions.begin()++);
    mNumberOfAsteroids = 6;
    prepareAsteroids(mNumberOfAsteroids);
    mNumberOfLives = 3;
    mScore = 0;
    mGameIsRunning = true;
}

void Game::handleAnimation(const sf::Vector2f &position)
{
    std::unique_ptr<Animation> temp(new Animation(mTextureHolder.getTexture(Textures::explosion), 4, 4, 256, 256, 0.2f));
    temp->setPosition(position);
    mExplosions.push_back(std::move(temp));
}

void Game::handleAllCollisions()
{
    for (auto asteroid = mAsteroids.begin(); asteroid != mAsteroids.end();)
    {
        bool collision = false;
        entityTorus(**asteroid);
        for (auto bullet = mBullets.begin(); bullet != mBullets.end();)
        {
            if (entitiesAreInCollision(**asteroid, **bullet))
            {
                asteroidGotHit(**asteroid, **bullet);
                mBullets.erase(bullet++);
                collision = true;
                break;
            }
            else
                ++bullet;
        }
        if (entitiesAreInCollision(**asteroid, *mPlayer))
        {
            alreadySubtractedLife = false;
            (*asteroid)->isAlive = false;
            playerGotHit();
            collision = true;
            break;
        }
        if (!collision)
            ++asteroid;
        else
            mAsteroids.erase(asteroid++);
    }
}