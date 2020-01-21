#ifndef __PLAYERFACTORY_HPP
# define __PLAYERFACTORY_HPP

# include <iostream>
# include "UserPlayerImpl.hpp"
# include "BotPlayerImpl.hpp"
# include "Ball.hpp"

enum ePlayerType{
	ALIVE,
	BOT
};

class PlayerFactory
{
private:
	PlayerFactory();
	static PlayerFactory *factory;
public:
	PlayerFactory(const PlayerFactory& src);
	~PlayerFactory();
	PlayerFactory& operator=(const PlayerFactory& src);
	static PlayerFactory& getInstance();
	AbstractPlayer *createPlayer(ePlayerType tyep, std::string name, Ball &ball);
};
#endif
