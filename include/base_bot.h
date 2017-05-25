#ifndef BASE_BOT_H
#define BASE_BOT_H

#include <QObject>

#include "map_maker.h"

class CBaseBot : public QObject
{
	Q_OBJECT
public:
	explicit CBaseBot(CMapMaker* map, QColor color, EMapTypes type, QObject *parent = 0);

	QColor getColor();
	EMapTypes getType();

signals:
	void cellWasCaptured(int i, int j, QColor oldColor, QColor newColor);

public slots:

protected:
	QVector<QPair<int, int> > getEnabledFields();

	CMapMaker* m_map;
	QColor m_color;
	EMapTypes m_type;
};
#endif // BASE_BOT_H
