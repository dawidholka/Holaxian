#include "Player.h"

int const PlayerSpeed = 10;

Player::Player()
{
    Position.x = 0;
    Position.y = 0;
}

void Player::SetPositionX(int X)
{
    Position.x = X;
}

void Player::SetPositionY(int Y)
{
    Position.y = Y;
}

int Player::GetPositionX()
{
    return Position.x;
}

int Player::GetPositionY()
{
    return Position.y;
}

void Player::MoveLeft()
{
    Position.x-=PlayerSpeed;
}

void Player::MoveRight()
{
    Position.x+=PlayerSpeed;
}
