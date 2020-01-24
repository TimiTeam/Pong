#include "BotPlayerImpl.hpp"
# include <chrono>

BotPlayerImpl::BotPlayerImpl(float posX, float posY, int height, int width, Ball &ball) : AbstractPlayer(posX, posY, height, width), ball(ball)
{
}

BotPlayerImpl::BotPlayerImpl(std::string name, Ball &ball) : AbstractPlayer(name), ball(ball)
{
}

BotPlayerImpl::BotPlayerImpl(const BotPlayerImpl& src) : AbstractPlayer(src), ball(src.ball)
{
	*this = src;
}

BotPlayerImpl::~BotPlayerImpl()
{
	
}

BotPlayerImpl& BotPlayerImpl::operator=(const BotPlayerImpl& src)
{
	AbstractPlayer::operator=(src);
	return *this;
}

void BotPlayerImpl::updateState(eDirection dir, int top, int bottom)
{
	(void)dir;
	static auto start = std::chrono::system_clock::now();
	auto end = std::chrono::system_clock::now();

	std::chrono::duration<double> diff = end - start; 
	if (diff.count() > 0.06)
	{
		start = end;
		float ballPosY = ball.getPosY();
		if (ball.getDirections() == RIGHT){
			if  (ballPosY < posY){
				if (posY - speed > top)
					posY -= speed;
				else
					posY = top;
			}
			else if (ballPosY > posY && ballPosY > posY + height){
				if (posY + height + speed < bottom)
					posY += speed;
				else
					posY = bottom - height;	
			}
		}
	}
}