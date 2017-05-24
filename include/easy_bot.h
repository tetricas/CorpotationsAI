#ifndef CPLAYER_H
#define CPLAYER_H

#include "base_bot.h"

class CEasyBot : public CBaseBot
{
	Q_OBJECT
public:
	explicit CEasyBot(CMapMaker* map, QColor color, EMapTypes type, QObject *parent = 0);

	void makeTurn();

signals:
public slots:
};

#endif // CPLAYER_H
