#pragma once
#include <SFML/Graphics.hpp>
#include "textureHolder.h"
#include "entities.h"
#include <vector>
#include <list>

// Klasu dopuniti po potrebi.

class Game{
public:
    Game();
    void run();
private:
    void processEvents();
    void update(sf::Time dt);
    void render();
    void prepareAsteroids(int numberOfAsteroids);
    void handleBullet();
    void entityTorus(Entity &entity);

    sf::RenderWindow mWindow;
    int numberOfAsteroids;
    TextureHolder mTextureHolder;
    sf::Sprite mBackgroundSprite;  
    std::unique_ptr<Player> mPlayer;
    std::vector<std::unique_ptr<Asteroid>> mAsteroids;
    //ima dosta brisanja pa je isplativija lista
    std::list<std::unique_ptr<Bullet>> mBullets;
    //std::unique_ptr<Animation> mExplosion;

    sf::Time mDtFixed;
};
