#ifndef CLOGIC_H
#define CLOGIC_H

#include "enum_types.h"
#include "map_maker.h"

class CLogic
{
public:
	CLogic()
	{}
	static EWinState checkGame(CMapMaker map, QColor);
	static int checkTurn(int i, int j, CMapMaker map, QColor myColor, EMapTypes myType);
	static int checkBlock(int i, int j, CMapMaker map, QColor myColor, EMapTypes myType);
	static int calculatePower(int i, int j, CMapMaker map, EMapTypes myType);
};

#endif // CLOGIC_H
