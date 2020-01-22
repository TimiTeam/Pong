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
	if (this != &src){
		this->posX = src.posX;
		this->posY = src.posY;
		this->dirX = src.dirX;
		this->dirY = src.dirY;
		this->height = src.height;
		this->width = src.width;
	}
	return *this;
}

bool Ball::checkColision(AbstractPlayer &player){
    bool x = 0;
    bool y = 0;
    int pX = player.getPosX();
    int pY = player.getPosY();

    if (pX <= posX && ((pX + player.getWidth()) >= posX))
        x = 1;
    if (pX >= posX && ((pX + player.getWidth()) <= posX + width))
        x = 1;
    if ((pX <= (posX + width)) && ((pX + player.getWidth()) >= posX + width))
        x = 1;
    if (pY <= posY && ((pY + player.getHeight()) >= posY))
        y = 1;
    if (pY >= posY && ((pY + player.getHeight()) <= (posY +  height)))
        y = 1;
    if ((pY <= (posY +  height)) && ((pY + player.getHeight()) >= (posY +  height)))
        y = 1;
    if (x == 1 && y == 1)
        return (true);
    return (false);
}

AbstractPlayer *Ball::moveBall(int top, int bottom, int leftSide, int rightSide, AbstractPlayer &playerLeft, AbstractPlayer &playerRight){
	AbstractPlayer *ret = NULL;
	AbstractPlayer *check;
	if (posY + dirY <= top || posY + dirY >= bottom){
		dirY *= -1;
	}

	if (posX < rightSide / 2)
		check = &playerLeft;
	else
		check = &playerRight;

	if (checkColision(*check)){
		float part = check->getHeight() / 3;
		int playerPosY = check->getPosY();
		if (posY >= playerPosY && posY <= playerPosY + part){
			dirY = -1;
		}
		else if (posY > playerPosY + part && posY <= playerPosY + check->getHeight() - part){
			dirY = 0;
		}
		else if (posY > playerPosY + check->getHeight() - part && posY <= playerPosY + check->getHeight()){
			dirY = 1;
		}
		dirX *= -1;
	}
	if (posX <= leftSide)
		ret = &playerLeft;
	else if (posX >= rightSide)
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