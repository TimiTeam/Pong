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

void BotPlayerImpl::updateState(eDirection dir, int top, int bottom)
{
	eDirection ballDir = ball.getDirections();
	switch (ballDir)
	{
	case UP:
		if (posY - speed > top)
			setPosY(posY - speed);
		break;
	
	case DOWN:
		if (posY + height + speed < bottom)
			setPosY(posY + speed);
		break;
	default:
		break;
	}
}