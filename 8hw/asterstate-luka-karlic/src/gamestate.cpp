#include "gamestate.h"
#include "game.h"
#include <iostream>

WelcomeState::WelcomeState(Game *pGame) : GameState(pGame)
{
    init();
}

void WelcomeState::handleEvents(sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        mpGame->setState(GameState::State::Playing);
        break;
    case sf::Event::Closed:
        mpGame->getWindow()->close();
        break;
    }
}

void WelcomeState::update(sf::Time dt)
{
    mText.setString("Asteroids clone by Luka Karlic\n Press any key to continue.");
}

void WelcomeState::init()
{
    mText.setFont(mpGame->mFont);
    mText.setPosition(400, 350);
    mText.setCharacterSize(25);
}

void WelcomeState::render()
{
    mpGame->getWindow()->draw(mText);
}
ScoreState::ScoreState(Game *pGame) : GameState(pGame)
{
    init();
}
void ScoreState::init()
{
    mText.setFont(mpGame->mFont);
    mText.setPosition(400, 350);
    mText.setCharacterSize(25);
}

void ScoreState::handleEvents(sf::Event event)
{
    switch (event.type)
    {
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Escape)
            mpGame->getWindow()->close();
        else if(event.key.code == sf::Keyboard::Return)
            mpGame->setState(GameState::State::Playing);
            //u init mi se nalazi metoda restartGame()
            mpGame->mpGameState->init();
        break;
    case sf::Event::Closed:
        mpGame->getWindow()->close();
        break;
    }
}

void ScoreState::update(sf::Time dt)
{
    mText.setString("Score = " + std::to_string(mpGame->mScore) + "\n Enter to continue, Esc to finish.");
}

void ScoreState::render()
{
    mpGame->getWindow()->draw(mText);
}
