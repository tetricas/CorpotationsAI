#ifndef CLOGIC_H
#define CLOGIC_H

#include "enum_types.h"
#include "map_maker.h"

class CLogic
{
public:
	CLogic()
	{}
	static EWinState checkGame(const CMapMaker& map, QColor);
	static int checkTurn(int i, int j, const CMapMaker& map, QColor myColor, EMapTypes myType);
	static int checkBlock(int i, int j, const CMapMaker& map, QColor myColor, EMapTypes myType);
	static void decreasePower(int i, int j, CMapMaker& map, EMapTypes myType);
	static void increasePower(char checked, CMapMaker& map, EMapTypes myType);
};

#endif // CLOGIC_H
