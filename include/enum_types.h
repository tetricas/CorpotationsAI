#ifndef ENUM_TYPES_H
#define ENUM_TYPES_H

#include <QVector>
#include <QPair>
#include <QColor>

enum EMapTypes
{
	eMT_gold = 0,
	eMT_silver = 1,
	eMT_cuper = 2,

	eMT_mountain = 3,
	eMT_rock = 4,
	eMT_tree = 5,

	eMT_grass = 6
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

#define MAX_POWER 3
typedef QVector<QVector<QPair<EMapTypes, QColor>>> MyMapContainer ;

#endif // ENUM_TYPES_H
