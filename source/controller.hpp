#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "partie.hpp"

class controller {
private:
	Partie* partie;
public:
	controller();
	~controller();
	void lancerPartie();
};
#endif