#ifndef __ABSTRACTPLAYER_HPP
# define __ABSTRACTPLAYER_HPP

# include <iostream>

enum eDirection{
	NON,
	UP,
	DOWN
};

class AbstractPlayer
{
private:

protected:
	std::string name;
	float posX;
	float posY;
	int height;
	int width;
	float speed;
	int score;

public:
	AbstractPlayer();
	AbstractPlayer(std::string name);
	AbstractPlayer(float posX, float posY, int height, int width);
	AbstractPlayer(const AbstractPlayer& src);
	~AbstractPlayer();
	AbstractPlayer& operator=(const AbstractPlayer& src);
	virtual void updateState(eDirection dir, int top, int bottom) = 0;
	void setPosX(float x);
	void setPosY(float y);
	float getPosX();
	float getPosY();
	int getWidth();
	int getHeight();
	float getSpeed();
	void setHeight(int height);
	void setWidth(int width);
	void incrementScore();
	int getScore();
	void setSpeed(float speed);
};
#endif
