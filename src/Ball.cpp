#include "Ball.hpp"

Ball *Ball::ball = 0;

Ball::Ball()
{
	
}

Ball::Ball(const Ball& src)
{
	*this = src;
}

Ball::~Ball()
{
	
}

Ball& Ball::operator=(const Ball& src)
{
	return *this;
}

void Ball::moveBall(){
	this->posX += dirX;
	this->posY += dirY;
}

eDirection Ball::getDirections(){
	if (dirX < 0)
		return UP;
	else if (dirY > 0)
		return DOWN;
	return NON;
}


Ball& Ball::getInstance(){
	if (ball == NULL)
		ball = new Ball();
	return *ball;
}