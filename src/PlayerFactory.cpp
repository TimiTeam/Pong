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
	delete [] factory;
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

AbstractPlayer *PlayerFactory::createPlayer(ePlayerType type, std::string name, Ball &ball){
	AbstractPlayer *ret;

	switch (type)
	{
	case ALIVE:
		ret = new UserPlayerImpl(name);
		break;
	case BOT:
		ret = new BotPlayerImpl(name, ball);
		break ;
	default:
		break;
	}
	return ret;
}