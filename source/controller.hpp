#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "partie.hpp"

class Controller {
private:
	Partie* partie;
public:
	Controller();
	~Controller() { delete partie; }
	const Partie& getPartie() { return *partie; };
	void parametrerPartie();
	void lancerPartie();


};
#endif