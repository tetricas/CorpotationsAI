#ifndef CGAMESPACE_H
#define CGAMESPACE_H

#include <QtQuick/QQuickPaintedItem>
#include <QQuickItem>
#include <QMouseEvent>
#include <QPainter>

#include "map_maker.h"
#include "logic.h"
#include "easy_bot.h"
#include "clever_bot.h"

class CGameSpace : public QQuickPaintedItem
{
	Q_OBJECT
	Q_PROPERTY(int blockSideSize MEMBER m_blockSideSize)
	Q_PROPERTY(int shift MEMBER m_shift CONSTANT)
	Q_PROPERTY(int blocksCount READ blocksCount CONSTANT)

public:
	explicit CGameSpace(QQuickItem* parent = nullptr);

	Q_INVOKABLE void setTurn();

	int blocksCount();

signals:
	void blocksCountChanged();
	void gameFinished(QColor winner);
	void updateScore(int player, int firstBot, int secondBot);

public slots:
	void cellOwnerChanged(int i, int j, QColor oldColor, QColor newColor);

protected:
	virtual void paint(QPainter* painter);
	virtual void mousePressEvent(QMouseEvent *event);

private:
	int m_blockSideSize;
	int m_blocksCount;
	int m_shift;
	int m_iPosX;
	int m_iPosY;

	QColor m_color;
	EMapTypes m_type;

	CMapMaker m_map;
	CEasyBot m_easyBot;
	CCleverBot m_cleverBot;
};

#endif // CGAMESPACE_H
