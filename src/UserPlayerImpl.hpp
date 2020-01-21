#ifndef __USERPLAYERIMPL_HPP
# define __USERPLAYERIMPL_HPP

# include <iostream>
# include "AbstractPlayer.hpp"

class UserPlayerImpl : public AbstractPlayer
{
private:

public:
	UserPlayerImpl(std::string name);
	UserPlayerImpl(float posX, float posY, int height, int width);
	UserPlayerImpl(const UserPlayerImpl& src);
	~UserPlayerImpl();
	UserPlayerImpl& operator=(const UserPlayerImpl& src);
	void updateState(eDirection dir, int top, int bottom);
};
#endif
