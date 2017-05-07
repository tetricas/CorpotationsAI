#ifndef ENUM_TYPES_H
#define ENUM_TYPES_H

#include <QVector>
#include <QPair>
#include <QColor>

enum EMapTypes
{
    eMT_gold,
    eMT_silver,
    eMT_cuper,

    eMT_mountain,
    eMT_rock,
    eMT_tree,

    eMT_grass
};

enum EWinState
{
    eWS_win,
    eWS_lose,
    eWS_continue
};

enum EPowerBoost
{
    ePB_disabled = 0,
    ePB_foreign = 1,
    ePB_grass = 2,
    ePB_badMine = 4,
    ePB_yourMine = 8
};

typedef QVector<QVector<QPair<EMapTypes, QColor>>> MyMapContainer ;

#endif // ENUM_TYPES_H
