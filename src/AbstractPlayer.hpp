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
	int posX;
	int posY;
	float speed;
	int score;

public:
	AbstractPlayer();
	AbstractPlayer(const AbstractPlayer& src);
	~AbstractPlayer();
	AbstractPlayer& operator=(const AbstractPlayer& src);
	virtual void updateState() const = 0;
	void changePos(eDirection e);
	void incrementScore();
	int getScore();
};
#endif
