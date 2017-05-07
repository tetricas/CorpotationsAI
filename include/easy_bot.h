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
    int takeAwayPower(int power);

signals:

public slots:

private:
    CMapMaker* m_map;
    QColor m_color;
    EMapTypes m_type;
    int m_power;
};

#endif // CPLAYER_H
