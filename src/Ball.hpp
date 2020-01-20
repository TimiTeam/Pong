#ifndef __BALL_HPP
# define __BALL_HPP

# include <iostream>

class Ball
{
private:

public:
	Ball();
	Ball(const Ball& src);
	~Ball();
	Ball& operator=(const Ball& src);
	void moveBall();
};
#endif
