#include "game.h"
#include <stdexcept>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <cmath>

Game::Game() : mWindow(sf::VideoMode(1280, 1024), "SFML window"), mNumberOfAsteroids(6)
{
    if (!mFont.loadFromFile("neuropol_x_rg.ttf"))
        throw std::runtime_error("Can not open neuropol_x_rg.ttf");

    mAllStates.at(static_cast<int>(GameState::State::Welcome)) = new WelcomeState(this);
    mAllStates.at(static_cast<int>(GameState::State::Score)) = new ScoreState(this);
    mAllStates.at(static_cast<int>(GameState::State::Playing)) = new PlayState(this);

    mpGameState = mAllStates.at(static_cast<int>(GameState::State::Welcome));

    mDtFixed = sf::seconds(1.0f / 60.0f);
}
Game::~Game()
{
    free(mAllStates.at(static_cast<int>(GameState::State::Playing)));
    free(mAllStates.at(static_cast<int>(GameState::State::Score)));
    free(mAllStates.at(static_cast<int>(GameState::State::Welcome)));
}
void Game::setState(GameState::State newState)
{
    mpGameState = mAllStates.at(static_cast<int>(newState));
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
        mpGameState->handleEvents(event);
}

void Game::update(sf::Time dt)
{
    mpGameState->update(dt);
}

void Game::render()
{
    mWindow.clear();
    mpGameState->render();
    mWindow.display();
}
