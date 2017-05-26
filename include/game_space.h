#ifndef CGAMESPACE_H
#define CGAMESPACE_H

#include <QtQuick/QQuickPaintedItem>
#include <QQuickItem>
#include <QMouseEvent>
#include <QPainter>
#include <QSharedPointer>

#include "map_maker.h"
#include "logic.h"
#include "base_bot.h"
#include "easy_bot.h"
#include "clever_bot.h"

class CGameSpace : public QQuickPaintedItem
{
	Q_OBJECT
	Q_PROPERTY(int blockSideSize MEMBER m_blockSideSize)
	Q_PROPERTY(int shift MEMBER m_shift CONSTANT)
	Q_PROPERTY(int blocksCount READ blocksCount CONSTANT)
    Q_PROPERTY(QString gameMode READ gameMode WRITE setGameMode NOTIFY gameModeChanged)

public:
	explicit CGameSpace(QQuickItem* parent = nullptr);
    ~CGameSpace();

	Q_INVOKABLE void setTurn();

	int blocksCount();
    QString gameMode();
    void setGameMode(QString mode);

signals:
	void blocksCountChanged();
	void gameFinished(QColor winner);
	void updateScore(int player, int firstBot, int secondBot);
    void gameModeChanged();

public slots:
	void cellOwnerChanged(int i, int j, QColor oldColor, QColor newColor);

protected:
	virtual void paint(QPainter* painter);
	virtual void mousePressEvent(QMouseEvent *event);

private:
    void startNew();

	int m_blockSideSize;
	int m_blocksCount;
	int m_shift;
	int m_iPosX;
	int m_iPosY;

    QString m_mode;

	QColor m_color;
	EMapTypes m_type;

    CMapMaker* m_map;
    CBaseBot* m_firstBot;
    CBaseBot* m_secondBot;
};

#endif // CGAMESPACE_H
