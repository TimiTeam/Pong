#include "UserPlayerImpl.hpp"

UserPlayerImpl::UserPlayerImpl(float posX, float posY, int height, int width) :  AbstractPlayer(posX, posY, height, width)
{
	
}

UserPlayerImpl::UserPlayerImpl(std::string name) : AbstractPlayer(name)
{
	
}

UserPlayerImpl::UserPlayerImpl(const UserPlayerImpl& src) : AbstractPlayer(src)
{
	*this = src;
}

UserPlayerImpl::~UserPlayerImpl()
{
	
}

UserPlayerImpl& UserPlayerImpl::operator=(const UserPlayerImpl& src)
{
	AbstractPlayer::operator=(src);
	return *this;
}

void UserPlayerImpl::updateState(eDirection dir, int top, int bottom){
	switch (dir){
	case UP:
		if (posY - speed > top)
			posY -= speed;
		else
			posY = top;
		break;
	
	case DOWN:
		if (posY + height + speed < bottom)
			posY += speed;
		else
			posY = bottom - height;
		break;
	default:
		break;
	}
}
