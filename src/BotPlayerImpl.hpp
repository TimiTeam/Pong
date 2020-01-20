#ifndef __BOTPLAYERIMPL_HPP
# define __BOTPLAYERIMPL_HPP

# include <iostream>
# include "AbstractPlayer.hpp"
# include "Racket.hpp"

class BotPlayerImpl : public AbstractPlayer
{
private:

public:
	BotPlayerImpl();
	BotPlayerImpl(const BotPlayerImpl& src);
	~BotPlayerImpl();
	BotPlayerImpl& operator=(const BotPlayerImpl& src);
};
#endif
