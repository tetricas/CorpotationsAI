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
    void findTarget();
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
	QVector<QVector<int>> m_grid;
    int m_pathLength;
    int m_currentStep;

    const int m_disable;
    const int m_empty;
};

#endif // CLEVER_BOT_H
