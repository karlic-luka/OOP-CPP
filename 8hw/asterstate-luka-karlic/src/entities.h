#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
 
class Entity : public sf::Drawable, public sf::Transformable
{
public:
    Entity(sf::Texture const &texture);
    void setVelocity(sf::Vector2f const &vel) { mVelocity = vel; }
    sf::CircleShape getCircle() const {return mCircle;}
    virtual void update(sf::Time dt = sf::Time::Zero);
    virtual ~Entity() {}
    bool isAlive;

protected:
    sf::Sprite mSprite;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    sf::Vector2f mVelocity;
    sf::CircleShape mCircle;
    float mRadius;
};

class Animation : public Entity
{
public:
    Animation(sf::Texture const &texture, int rows, int cols, int width, int height, float vel);
    virtual void update(sf::Time dt = sf::Time::Zero) override;
private:
    int mRows, mCols, mWidth, mHeight;
    float mSpeed;
    float mCurrentCol;
    int mCurrentRow;
};

class Asteroid : public Entity
{
public:
    Asteroid(sf::Texture const &texture);
    void update(sf::Time dt) override;
    void setRotatingSpeed(float speed) { rotatingSpeed = speed; };
    //how many points you gain if you kill it
    int worth;
private:
    float rotatingSpeed;
};

class Player : public Entity
{
public:
    Player(sf::Texture const &texture);
    void update(sf::Time dt) override;
    void handlePlayerInput(sf::Keyboard::Key code, bool isPressed);
    void setSpeed(const float &speed) { mSpeed = speed; };
private:
    bool mIsAccelerating = false;
    bool mIsDeccelerating = false;
    bool mIsRotatingLeft = false;
    bool mIsRotatingRight = false;
    float mSpeed = 300.0f; // pixel/sec
};

class Bullet : public Entity
{
public:
    Bullet(sf::Texture const &texture);
    void update(sf::Time dt) override;
    void setSpeed(const float &speed) {mSpeed = speed;};
private:
    float mSpeed = 400.0f;
};