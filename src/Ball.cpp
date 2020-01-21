#include "Ball.hpp"

Ball *Ball::ball = 0;

Ball::Ball()
{
	dirX = -1;
	dirY = -1;
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

AbstractPlayer *Ball::moveBall(int top, int bottom, AbstractPlayer &playerLeft, AbstractPlayer &playerRight){
	AbstractPlayer *ret = NULL;
	if (posY + dirY <= top || posY + dirY >= bottom){
		dirY *= -1;
	}
	if (posX < playerLeft.getPosX())
		ret = &playerLeft;

	if (posX > playerRight.getPosX())
		ret = &playerRight;
	posX += dirX;
	posY += dirY;
	return ret;
}

void Ball::setPosition(int x, int y){
	posX = x;
	posY = y;
}

eDirection Ball::getDirections(){
	if (dirY < 0)
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

int Ball::getPosX(){
	return posX;
}

int Ball::getPosY(){
	return posY;
}

int Ball::getHeight(){
	return height;
}

int Ball::getWidth(){
	return width;
}

void Ball::setHeight(int height){
	this->height = height;
}
void Ball::setWidth(int width){
	this->width = width;
}