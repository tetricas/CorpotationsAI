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
private:
	void findTarget(char& checked);
	void findStart();
	bool leeAlgorithm();
	void prepareGrid();

	int m_searchAreaSize;
	QPair<int, int> m_startCell;
	QPair<int, int> m_targetCell;
	int m_maxPower;
	QVector<QPair<int, int>> m_rejectedCells;

	bool m_isOnWay;

	QVector<QPair<int, int>> m_path;
	QVector<int> m_pathY;
	int m_pathLength;
	QVector<QVector<int>> m_grid;

	const int WALL;
	const int BLANK;
};

#endif // CLEVER_BOT_H
