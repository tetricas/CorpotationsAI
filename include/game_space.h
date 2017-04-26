#ifndef CGAMESPACE_H
#define CGAMESPACE_H

#include <QtQuick/QQuickPaintedItem>
#include <QMouseEvent>
#include <QPainter>

#include "map_maker.h"

class CGameSpace : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int blockSideSize WRITE setBlockSideSize)
	Q_PROPERTY(int blocksCount READ blocksCount CONSTANT)

public:
    explicit CGameSpace(QQuickItem* parent = nullptr);

    void setBlockSideSize(int sideSize);
	int blocksCount();

	Q_INVOKABLE void setTurn();

signals:
	void blocksCountChanged();

protected:
    virtual void paint(QPainter* painter);
    virtual void mouseReleaseEvent(QMouseEvent* event);

private:
    int m_blockSideSize;
    int m_blocksCount;
    int m_iPosX;
    int m_iPosY;
	int m_alpha;
	CMapMaker m_map;
};

#endif // CGAMESPACE_H
