#pragma once
#include <SFML/Graphics.hpp>
#include "textureHolder.h"
#include "entities.h"
#include <vector>
#include <list>
#include "playstate.h"
#include "gamestate.h"
#include <array>

/**
 * Klasa u kojoj je implementirana igra Asteroids.
 */ 
class Game {
public:
    /**
     * Konstruktor klase.
     */ 
    Game();
    /**
     * Pokreće igru.
     */ 
    void run();
    /**
     * Setter za trenutno stanje.
     */ 
    void setState(GameState::State newState);
    /**
     * Getter za mWindow
     */ 
    sf::RenderWindow *getWindow() {return &mWindow;};

    ~Game();
    friend class WelcomeState;
    friend class ScoreState;
    friend class PlayState;

private:
    /**
     * Procesuira vanjske događaje poput pritiska na tipkovnici i slično.
     */ 
    void processEvents();
    /**
     * Ažurira sve elemente koji će biti prikazani na zaslonu.
     * @param dt Promjena vremena.
     */ 
    void update(sf::Time dt);
    /**
     * Slika sve elemente na zaslon.
     * @param dt Promjena vremena.
     */ 
    void render();
    
    /**
     * Prozor na kojem se sve odražava.
     */ 
    sf::RenderWindow mWindow;
    /**
     * Broj asteroida kojim počinje igra.
     */ 
    int mNumberOfAsteroids;
    /**
     * Pokazivac na trenutno stanje igre.
     */ 
    GameState *mpGameState;
    /**
     * Fiksno vrijeme promjene.
     */ 
    sf::Time mDtFixed;

    std::array<GameState*, 3> mAllStates;
    /**
     * Font za ispis teksta.
     */ 
    sf::Font mFont;
    /**
     * Score koji služi kao posrednik između PlayState i ScoreState
     */ 
    int mScore;
};
