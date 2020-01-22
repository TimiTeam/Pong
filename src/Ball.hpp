#ifndef __BALL_HPP
# define __BALL_HPP

# include <iostream>
# include "AbstractPlayer.hpp"

class Ball
{
private:
    static Ball *ball;
	int posX;
	int posY;
	int dirX;
	int dirY;
	int height;
	int width;
	Ball();
	Ball(const Ball& src);
	bool checkColision(AbstractPlayer &player);

public:
	~Ball();
	Ball& operator=(const Ball& src);
	AbstractPlayer *moveBall(int top, int bottom, int leftSide, int rightSide, AbstractPlayer &playerLeft, AbstractPlayer &playerRight);
	eDirection getDirections();
	int getPosX();
	int getPosY();
	int getHeight();
	int getWidth();
	void setHeight(int height);
	void setWidth(int width);
	void setPosition(int x, int y);
	static Ball& getInstance();
};
#endif
