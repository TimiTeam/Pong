#include "Ball.hpp"

Ball *Ball::ball = 0;

Ball::Ball()
{
	speed = 0;
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
    if (x == 1 && y == 1)
        return (true);
    return (false);
}


void Ball::ricochetFromPlayer(AbstractPlayer &check){
	float part = check.getHeight() / 3;
	int playerPosY = check.getPosY();
	int ballCenter = posY + height / 2;
	if (ballCenter > playerPosY && ballCenter <= playerPosY + part){
		dirY = -1.f;
	}
	else if (ballCenter > playerPosY + part && ballCenter < playerPosY + check.getHeight() - part){
		dirY = 0;
	}
	else if (ballCenter >= playerPosY + check.getHeight() - part && ballCenter < playerPosY + check.getHeight()){
		dirY = 1.1;
	}
	dirX *= -1;
}

void Ball::moveBall(int top, int bottom, int leftSide, int rightSide, AbstractPlayer &playerLeft, AbstractPlayer &playerRight){
	//AbstractPlayer *check;
	bool goal = false;

	(void)leftSide;
	if (posY <= top){
		posY = top;
		dirY = 1.1f;
	}
	else if (posY + height >= bottom){
		posY = bottom - height;
		dirY = -1.f;
	}
	if (posX <= playerLeft.getPosX()){
		playerRight.incrementScore();
		goal = true;
	}
	else if (posX + width >= playerRight.getPosX() + playerRight.getWidth()){
		playerLeft.incrementScore();
		goal = true;
	}
	if (posX + width / 2 < rightSide / 2 && !goal){
		if (checkColision(posX, posY, height, 0, playerLeft.getPosX(), playerLeft.getPosY(), playerLeft.getHeight(), playerLeft.getWidth())){
			ricochetFromPlayer(playerLeft);
			speed += 0.05;
		}
	}
	else if (!goal){
		if (checkColision(posX , posY, height, width + speed, playerRight.getPosX(), playerRight.getPosY(), playerRight.getHeight(), 0)){
			ricochetFromPlayer(playerRight);
			speed += 0.05;
		}
	}
	if (goal){
		posX = rightSide / 2 - width / 2;
		posY = bottom / 2 - height / 2;
		dirY = 0.f;
		speed = 0;
	}else{
		posX = posX + dirX + speed;
		posY = posY + dirY ;
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