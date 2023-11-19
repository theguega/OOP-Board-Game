#ifndef CONTROLLER_H
#define CONTROLLER_H

class controller {
private:
	Partie* partie;
public:
	controller();
	~controller();
	void lancerPartie();
};
#endif