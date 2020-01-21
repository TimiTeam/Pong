#ifndef __BOTPLAYERIMPL_HPP
# define __BOTPLAYERIMPL_HPP

# include <iostream>
# include "AbstractPlayer.hpp"
# include "Ball.hpp"

class BotPlayerImpl : public AbstractPlayer
{
private:
	Ball &ball;
public:
	BotPlayerImpl(std::string name, Ball &ball);
	BotPlayerImpl(float posX, float posY, int height, int width, Ball &ball);
	BotPlayerImpl(const BotPlayerImpl& src);
	~BotPlayerImpl();
	BotPlayerImpl& operator=(const BotPlayerImpl& src);
	virtual void updateState(eDirection dir, int top, int bottom);
};
#endif
