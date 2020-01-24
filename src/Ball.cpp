#include "Ball.hpp"
#include <cmath> 

Ball *Ball::ball = NULL;

Ball::Ball()
{
	speed = 10;
	dirX = -1;
	dirY = -1;
	cofUpperSpeed = speed / 2;
}

Ball::Ball(const Ball& src)
{
	*this = src;
}

Ball::~Ball()
{
	
}

void Ball::resetBall(){
	delete ball;
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
		this->speed = src.speed;
	}
	return *this;
}

bool Ball::checkColision(int posX1, int posY1, int height1, int width1, int posX2, int posY2, int hefight2, int width2){
    bool x = 0;
    bool y = 0;

    if (posX2 <= posX1 && ((posX2 + width2) >= posX1))
        x = 1;
    if (posX2 >= posX1 && ((posX2 + width2) <= posX1 + width1))
        x = 1;
    if ((posX2 <= (posX1 + width1)) && ((posX2 + width2) >= posX1 + width1))
        x = 1;
    if (posY2 <= posY1 && ((posY2 +  hefight2) >= posY1))
        y = 1;
    if (posY2 >= posY1 && ((posY2 +  hefight2) <= (posY1 +  height)))
        y = 1;
    if ((posY2 <= (posY1 +  height1)) && ((posY2 +  hefight2) >= (posY1 +  height1)))
        y = 1;
    return (x == 1 && y == 1);
}


void Ball::ricochetFromPlayer(AbstractPlayer &check){

	int part = std::floor(check.getHeight() / 3);
	int playerPosY = check.getPosY();
	int ballCenter = posY + height / 2;

	if (posY + height >= playerPosY && ballCenter < playerPosY + part){
		dirY = -1.f;
	}
	else if (ballCenter >= playerPosY + part && ballCenter <= playerPosY + check.getHeight() - part){
		dirY = 0.f;
	}
	else if (ballCenter > playerPosY + check.getHeight() - part && posY <= playerPosY + check.getHeight()){
		dirY = 1.f;
	}
	dirX *= -1.f;
}

void Ball::moveBall(int top, int bottom, int leftSide, int rightSide, AbstractPlayer &playerLeft, AbstractPlayer &playerRight){
	bool goal = false;

	(void)leftSide;

	if (posY + dirY <= top || posY + height + dirY >= bottom){
		dirY *= -1.1;
	}
	if (posX <= playerLeft.getPosX()){
		playerRight.incrementScore();
		goal = true;
	}
	else if (posX + width >= playerRight.getPosX() + playerRight.getWidth()){
		playerLeft.incrementScore();
		goal = true;
	}
	if (getDirections() == LEFT && !goal){
		if (checkColision(posX + (dirX * speed), posY + (dirY * speed), height, width, playerLeft.getPosX(), playerLeft.getPosY(), playerLeft.getHeight(), playerLeft.getWidth())){
			ricochetFromPlayer(playerLeft);
			speed += cofUpperSpeed;
		}
	}
	else if (!goal){
		if (checkColision(posX + (dirX * speed), posY + (dirY * speed), height, width, playerRight.getPosX(), playerRight.getPosY(), playerRight.getHeight(), playerRight.getWidth())){
			ricochetFromPlayer(playerRight);
			speed += cofUpperSpeed;
		}
	}
	if (goal){
		posX = rightSide / 2 - width / 2;
		posY = bottom / 2 - height / 2;
		dirY = 0.f;
		speed = cofUpperSpeed * 10;
	}else{
		posX = posX + (dirX * speed);
		posY = posY + (dirY * speed);
	}
}

void Ball::setPosition(int x, int y){
	posX = x;
	posY = y;
}

eDirection Ball::getDirections(){
	if (dirX < 0)
		return LEFT;
	else if (dirX > 0)
		return RIGHT;
	return NON;
}

Ball &Ball::getInstance(){
	if (ball == NULL)
		ball = new Ball();
	return *ball;
}


void Ball::setSpeed(float speed){
	this->speed = speed;
	cofUpperSpeed = speed / 10;
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
