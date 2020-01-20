#include "AbstractPlayer.hpp"

AbstractPlayer::AbstractPlayer()
{
	
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

void AbstractPlayer::changePos(eDirection e){
	switch (e)
	{
	case UP:
		posY += speed;
		break;
	case DOWN:
		posY -= speed;
		break;
	default:
		break;
	}
}

void AbstractPlayer::incrementScore(){
	++score;
}

int AbstractPlayer::getScore(){
	return score;
}
