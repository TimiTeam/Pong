#ifndef __BALL_HPP
# define __BALL_HPP

# include <iostream>
# include "AbstractPlayer.hpp"

class Ball
{
private:
    static Ball *ball;
	float posX;
	float posY;
	float dirX;
	float dirY;
	int height;
	int width;
	Ball();
	Ball(const Ball& src);

public:
	~Ball();
	Ball& operator=(const Ball& src);
	void moveBall();
	eDirection getDirections();
	static Ball& getInstance();
};
#endif
