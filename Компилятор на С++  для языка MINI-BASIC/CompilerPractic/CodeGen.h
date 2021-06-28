#pragma once
#include "Syntax.h"

class Generator : public SyntAuto
{
	int numstr; //Номер текущей строки. Для метки возврата из процедуры
	int NTX=705;

public:
	void Start(char*, char*);
	void getCountNTXA();
	void getCountNTtemp();
};
