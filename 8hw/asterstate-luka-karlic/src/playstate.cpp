#include "playstate.h"

const double pi = std::acos(-1);

PlayState::PlayState(Game *pGame) : GameState(pGame)
{
    mBackgroundSprite.setTexture(mTextureHolder.getTexture(Textures::background));
    textSetup();
    restartGame();
}
void PlayState::handleEvents(sf::Event event)
{
    // Close window : exit
    switch (event.type)
    {
    case sf::Event::Closed:
        mpGame->getWindow()->close();
        break;
    case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Space)
            handleBullet();
        mPlayer->handlePlayerInput(event.key.code, true);
        break;
    case sf::Event::KeyReleased:
        mPlayer->handlePlayerInput(event.key.code, false);
        break;
    }
}
void PlayState::init()
{
    restartGame();
}

void PlayState::update(sf::Time dt)
{
    if (gameIsOver())
    {
        //inace mi je zadnja eksplozija ostala neucitana do kraja
        for (auto explosion = mExplosions.begin(); explosion != mExplosions.end(); ++explosion)
            (*explosion)->update();
        mpGame->setState(GameState::State::Score);
        //cak nije redundancija sto imam mScore i u game.h jer je ovo jedino mjesto na kojem ga koristim
        //a tako mogu na lak nacin doci do scora u scorestate preko game-a
        mpGame->mScore = mScore;
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

void PlayState::render()
{
    mpGame->getWindow()->draw(mBackgroundSprite);

    mpGame->getWindow()->draw(*mPlayer);

    for (auto &asteroid : mAsteroids)
        mpGame->getWindow()->draw(*asteroid);
    for (auto &bullet : mBullets)
        mpGame->getWindow()->draw(*bullet);
    for (auto &explosion : mExplosions)
        mpGame->getWindow()->draw(*explosion);

    mpGame->getWindow()->draw(mUpperLeftText);
    mpGame->getWindow()->draw(mUpperRightText);
    updateText();
}
void PlayState::prepareAsteroids(int numberOfAsteroids)
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
        int width = rand() % mpGame->getWindow()->getSize().x;
        int height = rand() % mpGame->getWindow()->getSize().y;
        temp->setPosition(width, height);

        //random brzina okretanja
        //+150 je da se barem za toliko okrece
        temp->setRotatingSpeed(rand() % 360 + 150);

        //random orijentacija
        float orientationX = ((rand() % 2) == 0) ? 1.0f : -1.0f;
        float orientationY = ((rand() % 2) == 0) ? 1.0f : -1.0f;
        //random smjer - mVelocity
        //+250 da sam siguran da ne stoji u mjestu
        int x = rand() % mpGame->getWindow()->getSize().x + 250;
        int y = rand() % mpGame->getWindow()->getSize().y + 250;
        temp->setVelocity(sf::Vector2f(x * orientationX, y * orientationY));
        mAsteroids.push_back(std::move(temp));
    }
}

void PlayState::handleBullet()
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

void PlayState::entityTorus(Entity &entity)
{
    sf::Vector2f position = entity.getPosition();
    if (position.x >= mpGame->getWindow()->getSize().x)
        position.x = 0.0f;
    else if (position.x <= 0.0f)
        position.x = mpGame->getWindow()->getSize().x - 1.0f;
    if (position.y <= 0.0f)
        position.y = mpGame->getWindow()->getSize().y - 1;
    else if (position.y >= mpGame->getWindow()->getSize().y)
        position.y = 0.0f;
    entity.setPosition(position);
}

bool PlayState::entitiesAreInCollision(const Entity &first, const Entity &second)
{
    auto circle1 = first.getCircle();
    auto circle2 = second.getCircle();
    auto radius1 = circle1.getRadius();
    auto radius2 = circle2.getRadius();

    return !(norm2(first.getPosition(), second.getPosition()) > (radius1 + radius2));
}

double PlayState::norm2(sf::Vector2f first, sf::Vector2f second)
{
    sf::Vector2f temp = first - second;
    return sqrt(temp.x * temp.x + temp.y * temp.y);
}

void PlayState::playerGotHit()
{
    if (alreadySubtractedLife)
        return;
    else
    {
        mNumberOfLives--;
        alreadySubtractedLife = true;
        handleAnimation(mPlayer->getPosition());

        if (mNumberOfLives == 0)
        {
            mPlayer->isAlive = false;
            return;
        }
        else
            mPlayer->setPosition(mpGame->getWindow()->getSize().x / 2, mpGame->getWindow()->getSize().y / 2);
    }
}

void PlayState::asteroidGotHit(Asteroid &asteroid, Bullet &bullet)
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
        int x = rand() % mpGame->getWindow()->getSize().x + 10;
        int y = rand() % mpGame->getWindow()->getSize().y + 10;
        new1->setVelocity(sf::Vector2f(x, y));
        new1->worth = 40;

        std::unique_ptr<Asteroid> new2(new Asteroid(mTextureHolder.getTexture(Textures::meteorSmall1)));
        new2->setRotatingSpeed(rand() % 360 + 120);
        new2->setPosition(bullet.getPosition().x + 2, bullet.getPosition().y);
        x = rand() % mpGame->getWindow()->getSize().x + 10;
        y = rand() % mpGame->getWindow()->getSize().y + 10;
        new2->setVelocity(sf::Vector2f(-x, -y));
        new2->worth = 40;

        mAsteroids.push_back(std::move(new1));
        mAsteroids.push_back(std::move(new2));
    }
}

void PlayState::textSetup()
{
    mUpperRightText.setFont(mpGame->mFont);
    mUpperRightText.setPosition(1050, 10);
    mUpperRightText.setCharacterSize(25);

    mUpperLeftText.setFont(mpGame->mFont);
    mUpperLeftText.setPosition(40, 10);
    mUpperLeftText.setCharacterSize(25);
}

void PlayState::updateText()
{
    mUpperRightText.setString("Score: " + std::to_string(mScore));
    mUpperLeftText.setString("Lives: " + std::to_string(mNumberOfLives));
}

bool PlayState::gameIsOver()
{
    return mNumberOfLives == 0 || mAsteroids.size() == 0;
}

void PlayState::restartGame()
{
    mPlayer.reset(new Player(mTextureHolder.getTexture(Textures::player)));
    mPlayer->setPosition(mpGame->getWindow()->getSize().x / 2, mpGame->getWindow()->getSize().y / 2);

    while (mAsteroids.begin() != mAsteroids.end())
        mAsteroids.erase(mAsteroids.begin()++);
    while (mBullets.begin() != mBullets.end())
        mBullets.erase(mBullets.begin()++);
    while (mExplosions.begin() != mExplosions.end())
        mExplosions.erase(mExplosions.begin()++);
    prepareAsteroids(mpGame->mNumberOfAsteroids);
    mNumberOfLives = 3;
    mScore = 0;
}

void PlayState::handleAnimation(const sf::Vector2f &position)
{
    std::unique_ptr<Animation> temp(new Animation(mTextureHolder.getTexture(Textures::explosion), 4, 4, 256, 256, 0.2f));
    temp->setPosition(position);
    mExplosions.push_back(std::move(temp));
}

void PlayState::handleAllCollisions()
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