#ifndef CLEVER_BOT_H
#define CLEVER_BOT_H

#include "base_bot.h"

class CCleverBot : public CBaseBot
{
	Q_OBJECT
public:
	explicit CCleverBot(CMapMaker* map, QColor color, EMapTypes type, QObject *parent = 0);

	void makeTurn();

signals:
public slots:
};

#endif // CLEVER_BOT_H
