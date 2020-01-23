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
	float speed;
	float cofUpperSpeed;
	int height;
	int width;
	
	Ball();
	Ball(const Ball& src);
	bool checkColision(int posX1, int posY1, int height1, int width1, int posX2, int posY2, int hefight2, int width2);
	void ricochetFromPlayer(AbstractPlayer &player);

public:
	~Ball();
	Ball& operator=(const Ball& src);
	void moveBall(int top, int bottom, int leftSide, int rightSide, AbstractPlayer &playerLeft, AbstractPlayer &playerRight);
	eDirection getDirections();
	int getPosX();
	int getPosY();
	int getHeight();
	int getWidth();
	void setHeight(int height);
	void setWidth(int width);
	void setPosition(int x, int y);
	void setSpeed(float speed);
	static Ball& getInstance();
};
#endif
