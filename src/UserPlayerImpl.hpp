#ifndef __USERPLAYERIMPL_HPP
# define __USERPLAYERIMPL_HPP

# include <iostream>

class UserPlayerImpl
{
private:

public:
	UserPlayerImpl();
	UserPlayerImpl(const UserPlayerImpl& src);
	~UserPlayerImpl();
	UserPlayerImpl& operator=(const UserPlayerImpl& src);
};
#endif
