#include "BotPlayerImpl.hpp"

BotPlayerImpl::BotPlayerImpl(float posX, float posY, int height, int width, Ball &ball) : AbstractPlayer(posX, posY, height, width), ball(ball)
{

}

BotPlayerImpl::BotPlayerImpl(std::string name, Ball &ball) : AbstractPlayer(name), ball(ball)
{

}

BotPlayerImpl::BotPlayerImpl(const BotPlayerImpl& src) : ball(src.ball)
{
	*this = src;
}

BotPlayerImpl::~BotPlayerImpl()
{
	
}

BotPlayerImpl& BotPlayerImpl::operator=(const BotPlayerImpl& src)
{
	return *this;
}

void BotPlayerImpl::updateState(eDirection dir)
{
	switch (ball.getDirections())
	{
	case UP:
		setPosY(getPosY() - speed);
		break;
	
	case DOWN:
		setPosY(getPosY() + speed);
		break;
	default:
		break;
	}
}