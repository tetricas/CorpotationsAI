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

EPowerBoost CLogic::ckeckBlock(int i, int j, MyMapContainer map,
                               QColor myColor, EMapTypes myType)
{
    if( (j+1 < map[i].size() && map[i][j+1].second != myColor)&&
            (j > 0 &&  map[i][j-1].second != myColor) &&
            (i+1 < map.size() && map[i+1][j].second != myColor)&&
            (i > 0 && map[i-1][j].second != myColor))
        return ePB_disabled;

    if(map[i][j].second == myColor)
        return ePB_foreign;
    if(map[i][j].first == eMT_gold ||
            map[i][j].first == eMT_silver ||
            map[i][j].first == eMT_cuper )
    {
        if( map[i][j].first == myType )
            return ePB_yourMine;
        else
            return ePB_badMine;
    }
    if(map[i][j].first == eMT_grass)
        return ePB_grass;

    return ePB_disabled;
}
