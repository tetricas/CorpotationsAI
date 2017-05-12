#include "logic.h"

#include <QVector>
#include <QColor>
#include <QtDebug>

EWinState CLogic::checkGame(CMapMaker map, QColor myColor)
{
	QVector<QColor> vec;
	for(int i(0); i < map.getSize(); ++i)
		for(int j(0); j < map.getSize(); ++j)
			if(!vec.contains(map.getBlock(i,j).second))
				vec.push_back( map.getBlock(i,j).second );
	if(vec.size() > 2)
		return eWS_continue;
	if(vec.contains(myColor))
		return eWS_win;
	else
		return eWS_lose;
}

int CLogic::checkTurn(int i, int j, CMapMaker map, QColor myColor, EMapTypes myType)
{
	if(((j+1 < map.getSize() && map.getBlock(i,j+1).second != myColor)&&
	   (j > 0 && map.getBlock(i,j-1).second != myColor) &&
	   (i+1 < map.getSize() && map.getBlock(i+1,j).second != myColor)&&
	   (i > 0 && map.getBlock(i-1,j).second != myColor))||
	   map.getBlock(i,j).second == myColor)
		return ePB_disabled;

	return CLogic::checkBlock(i, j, map, myColor, myType);
}

int CLogic::checkBlock(int i, int j, CMapMaker map, QColor myColor, EMapTypes myType)
{
	int result = ePB_disabled;

	if(map.getBlock(i,j).second != myColor &&
	   map.getBlock(i,j).second != QColor(0,0,0,0))
		result|=ePB_foreign;

	if(map.getBlock(i,j).first == eMT_gold ||
	   map.getBlock(i,j).first == eMT_silver ||
	   map.getBlock(i,j).first == eMT_cuper )
	{
		if( map.getBlock(i,j).first == myType )
			result|=ePB_yourMine;
		else
			result|=ePB_badMine;
	}
	else if(map.getBlock(i,j).first == eMT_grass)
		result|=ePB_grass;
	else
		result=ePB_disabled;

	return result;
}

int CLogic::calculatePower(int i, int j, CMapMaker map, EMapTypes myType)
{
	int power = 0;
	EMapTypes type = map.getBlock(i,j).first;
	if(type == myType)
		power-=3;
	if((myType != eMT_gold&&type == eMT_gold)||
	   (myType != eMT_silver&&type == eMT_silver)||
	   (myType != eMT_cuper&&type == eMT_cuper))
		power-=2;
	if(type == eMT_grass)
		power-=1;

	return power;
}
