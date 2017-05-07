#include "logic.h"

#include <QVector>
#include <QColor>
#include <QtDebug>

EWinState CLogic::checkGame(MyMapContainer map, QColor myColor)
{
	QVector<QColor> vec;
	for(int i(0); i < map.size(); ++i)
		for(int j(0); j < map[i].size(); ++j)
			if(!vec.contains(map[i][j].first))
				vec.push_back( map[i][j].first );
	if(vec.size() > 2)
		return eWS_continue;
	if(vec.contains(myColor))
		return eWS_win;
	else
		return eWS_lose;
}

char CLogic::ckeckBlock(int i, int j, MyMapContainer map,
                        QColor myColor, EMapTypes myType)
{
    char result = ePB_disabled;
	if( (j+1 < map[i].size() && map[i][j+1].second != myColor)&&
		(j > 0 &&  map[i][j-1].second != myColor) &&
		(i+1 < map.size() && map[i+1][j].second != myColor)&&
		(i > 0 && map[i-1][j].second != myColor))
        return result;

    if(map[i][j].second != myColor)
        result|=ePB_foreign;

	if(map[i][j].first == eMT_gold ||
	   map[i][j].first == eMT_silver ||
	   map[i][j].first == eMT_cuper )
	{
		if( map[i][j].first == myType )
            result|=ePB_yourMine;
		else
            result|=ePB_badMine;
	}
    else if(map[i][j].first == eMT_grass)
        result|=ePB_grass;
    else
        result&=ePB_disabled;

    return result;
}
