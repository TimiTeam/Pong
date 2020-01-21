#include "UserPlayerImpl.hpp"

UserPlayerImpl::UserPlayerImpl(float posX, float posY, int height, int width) :  AbstractPlayer(posX, posY, height, width)
{
	
}

UserPlayerImpl::UserPlayerImpl(std::string name) : AbstractPlayer(name)
{
	
}

UserPlayerImpl::UserPlayerImpl(const UserPlayerImpl& src)
{
	*this = src;
}

UserPlayerImpl::~UserPlayerImpl()
{
	
}

UserPlayerImpl& UserPlayerImpl::operator=(const UserPlayerImpl& src)
{
	return *this;
}

void UserPlayerImpl::updateState(eDirection dir){
	switch (dir)
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