#include <iostream>
#include <string>
#include <vector>
#include "carte.h"

ostream& operator<<(ostream& f, const Prix& p) {
	f << "Blanc : " << blanc << "\n";
    f << "Bleu : " << bleu << "\n";
    f << "Vert : " << vert << "\n";
    f << "Noir : " << noir << "\n";
    f << "Rouge : " << rouge << "\n";
    f << "Perle : " << perle << "\n";

    return f;
}