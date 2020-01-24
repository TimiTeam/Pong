#include "PlayerFactory.hpp"


PlayerFactory *PlayerFactory::factory = 0;

PlayerFactory::PlayerFactory()
{
	
}

PlayerFactory::PlayerFactory(const PlayerFactory& src)
{
	*this = src;
}

PlayerFactory::~PlayerFactory()
{
}

void PlayerFactory::resetPlayerFactory(){
	delete factory;
}

PlayerFactory& PlayerFactory::operator=(const PlayerFactory& src)
{
	(void)src;
	return *this;
}

PlayerFactory &PlayerFactory::getInstance(){
	if (factory == NULL)
		factory = new PlayerFactory();
	return *factory;
}

AbstractPlayer *PlayerFactory::createPlayer(ePlayerType type, std::string name){
	AbstractPlayer *ret;

	switch (type)
	{
	case ALIVE:
		ret = new UserPlayerImpl(name);
		break;
	case BOT:
		ret = new BotPlayerImpl(name, Ball::getInstance());
		break ;
	default:
		break;
	}
	return ret;
}