#ifndef CPLAYER_H
#define CPLAYER_H

#include <QObject>

#include "map_maker.h"

class CEasyBot : public QObject
{
	Q_OBJECT
public:
	explicit CEasyBot(CMapMaker* map, QColor color, EMapTypes type, QObject *parent = 0);

	QColor getColor();
	EMapTypes getType();
	int getPower();

	void makeTurn();
	void takeAwayPower(int i, int j);

signals:
	void cellWasCaptured(int i, int j, QColor oldColor, QColor newColor);

public slots:

private:
	QVector<QPair<int, int> > getEnabledFields();

	CMapMaker* m_map;
	QColor m_color;
	EMapTypes m_type;
	int m_power;
};

#endif // CPLAYER_H
