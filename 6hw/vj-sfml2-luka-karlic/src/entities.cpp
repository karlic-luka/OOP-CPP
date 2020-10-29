#include "entities.h"
#include <iostream>

const double pi = std::acos(-1);
// Dopuniti po potrebi.

Entity::Entity(sf::Texture const &texture)
{
    mSprite.setTexture(texture);
    auto lb = mSprite.getLocalBounds();
    mSprite.setOrigin(lb.width / 2, lb.height / 2);
    mVelocity.x = mVelocity.y = 30.0f;
    isAlive = true;

    mRadius = 1.0 * std::min(lb.width / 2, lb.height / 2);
    mCircle.setRadius(mRadius);
    mCircle.setFillColor(sf::Color(0, 255, 0, 0));
    mCircle.setOutlineThickness(1);
    mCircle.setOutlineColor(sf::Color::Yellow);
    mCircle.setOrigin(mRadius, mRadius);
}

void Entity::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
    //    target.draw(mCircle, states);
}

void Entity::update(sf::Time dt)
{
    auto pos = getPosition();
    float x = pos.x + mVelocity.x * dt.asSeconds();
    float y = pos.y + mVelocity.y * dt.asSeconds();
    setPosition(x, y);
}

Animation::Animation(sf::Texture const &texture, int rows, int cols, int width, int height, float vel)
    : Entity(texture), mRows(rows), mCols(cols), mWidth(width / cols), mHeight(height / rows), mSpeed(vel),
      mCurrentCol(0.0f), mCurrentRow(0) {}

void Animation::update(sf::Time dt)
{
    if (!isAlive)
        return;
    mCurrentCol += mSpeed;
    if (static_cast<int>(mCurrentCol) == mCols)
    {
        mCurrentCol = 0.0f;
        ++mCurrentRow;
    }
    if (mCurrentRow == mRows)
    {
        mCurrentCol = 0.0f;
        mCurrentRow = 0;
        isAlive = false;
        return;
    }

    int i = mCurrentCol;
    int j = mCurrentRow;
    mSprite.setTextureRect(sf::IntRect(i * mWidth, j * mHeight, mWidth, mHeight));
}

Player::Player(sf::Texture const &texture) : Entity(texture){}

void Player::update(sf::Time dt)
{
    //trenunto je implementirano tako da se strelicom prema gore kreće unaprijed
    //a strelicom prema dolje unazad. Primjerice, dok avion stoji i stisnemo strelicu prema dolje,
    //avion se krece unazad
    if (mIsAccelerating)
        move(sin(getRotation() * pi / 180) * mSpeed * dt.asSeconds(),
             -1.0f * cos(getRotation() * pi / 180) * mSpeed * dt.asSeconds());
    if (mIsDeccelerating)
        move(-1.0f * sin(getRotation() * pi / 180) * mSpeed * dt.asSeconds(),
             cos(getRotation() * pi / 180) * mSpeed * dt.asSeconds());
    if (mIsRotatingRight)
        rotate(60 * dt.asSeconds());
    if (mIsRotatingLeft)
        rotate(-60 * dt.asSeconds());
}

void Player::handlePlayerInput(sf::Keyboard::Key code, bool isPressed)
{
    //trenunto je implementirano tako da se strelicom prema gore kreće unaprijed
    //a strelicom prema dolje unazad. Primjerice, dok avion stoji i stisnemo strelicu prema dolje,
    //avion se krece unazad
    if (code == sf::Keyboard::Key::Up)
        mIsAccelerating = isPressed;
    if (code == sf::Keyboard::Key::Down)
        mIsDeccelerating = isPressed;
    if (code == sf::Keyboard::Key::Left)
        mIsRotatingLeft = isPressed;
    if (code == sf::Keyboard::Key::Right)
        mIsRotatingRight = isPressed;
}

Asteroid::Asteroid(sf::Texture const &texture) : Entity(texture) {}

void Asteroid::update(sf::Time dt)
{
    rotate(rotatingSpeed * dt.asSeconds());
    //neka se krecu u smjeru mVelocity
    //alternativno sam mogao normirati mVelocity te imati privatnu varijablu mSpeed,
    //no svejedno je, moze i ovako
    float speed = 1.0f;
    //ovih 10 je nebitno, gotovo uvijek ce biti vece pa ga zelim skalirat
    if ((mVelocity.x * mVelocity.x + mVelocity.y * mVelocity.y) > 10)
        speed *= 0.1f;
    move(mVelocity * speed * dt.asSeconds());
}

Bullet::Bullet(sf::Texture const &texture) : Entity(texture) {}

void Bullet::update(sf::Time dt) {
    move(mVelocity * mSpeed * dt.asSeconds());
}

