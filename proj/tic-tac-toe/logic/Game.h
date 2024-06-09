#pragma once
#include "API.h"


#pragma once
class EXPORT_API Game
{
public:
	Game();



	int result();
	//zwraca liczbe gdy:
	//-2 nic
	//-1 remis
	// 0 kó³ko wygra³o
	// 1 krzy¿yk wygra³


	void reset();

	void setElement(int e, int i, int j);
	int getElement(int i, int j);


private:
	int n_matrix[3][3];
};



