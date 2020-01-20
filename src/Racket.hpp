#ifndef __RACKET_HPP
# define __RACKET_HPP

# include <iostream>

class Racket
{
private:
	int posX;
	int posY;
	int height;
	int width;
	
public:
	Racket();
	Racket(const Racket& src);
	~Racket();
	Racket& operator=(const Racket& src);
};
#endif
