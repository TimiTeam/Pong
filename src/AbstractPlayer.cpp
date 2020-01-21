#include "AbstractPlayer.hpp"

AbstractPlayer::AbstractPlayer()
{
	
}

AbstractPlayer::AbstractPlayer(std::string name) : name(name)
{
	speed = 10;
}


AbstractPlayer::AbstractPlayer(float posX, float posY, int height, int width) : posX(posX), posY(posY), height(height), width(width)
{
	speed = 10;
	score = 0;
}

AbstractPlayer::AbstractPlayer(const AbstractPlayer& src)
{
	*this = src;
}

AbstractPlayer::~AbstractPlayer()
{
	
}

AbstractPlayer& AbstractPlayer::operator=(const AbstractPlayer& src)
{
	return *this;
}

void AbstractPlayer::incrementScore(){
	++score;
}

int AbstractPlayer::getScore(){
	return score;
}


void AbstractPlayer::setSpeed(float speed){
	this->speed = speed;
}

void AbstractPlayer::setPosX(float posX){
	this->posX = posX;
}

void AbstractPlayer::setPosY(float posY){
	this->posY = posY;
}

float AbstractPlayer::getPosX(){
	return posX;
}

float AbstractPlayer::getPosY(){
	return posY;
}

void AbstractPlayer::setHeight(int height){
	this->height = height;
}

void AbstractPlayer::setWidth(int width){
	this->width = width;
}


int AbstractPlayer::getWidth(){
	return width;
}

int AbstractPlayer::getHeight(){
	return height;
}

float AbstractPlayer::getSpeed(){
	return speed;
}