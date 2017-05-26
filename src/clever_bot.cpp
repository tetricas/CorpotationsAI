#include "clever_bot.h"
#include "logic.h"
#include <QtDebug>

CCleverBot::CCleverBot(CMapMaker *map, QColor color, EMapTypes type, QObject *parent) :
	CBaseBot(map, color, type, parent),
	m_searchAreaSize(3),
	m_maxPower(0),
	m_isOnWay(false),
    m_path(),
	m_grid(m_map->getSize(),QVector<int>(m_map->getSize())),
    m_pathLength(0),
    m_currentStep(0),
    m_disable(-1),
    m_empty(-2)
{
}

void CCleverBot::makeTurn()
{
	m_rejectedCells.clear();
    QPair<int, int> nextStep;
    if(!m_isOnWay)
    {
        m_loseCounter = 0;
        do
        {
            m_isOnWay = true;
            m_path.clear();
            findTarget();
            findStart();
            prepareGrid();
            m_currentStep = 0;

            if(m_loseCounter++ > 100)
                return;
        }while(!leeAlgorithm());
    }

    if(m_currentStep == m_path.size())
        return;
    nextStep = m_path.at(m_currentStep++);
    if(m_currentStep == m_pathLength)
        m_isOnWay = false;

    CLogic::increasePower(CLogic::checkTurn(nextStep.first, nextStep.second,*m_map,m_color, m_type),
                          m_map, m_type);
    emit cellWasCaptured(nextStep.first, nextStep.second,
                         m_map->getBlock(nextStep.first, nextStep.second).second, m_color);
}

void CCleverBot::findTarget()
{
	CMapMaker* originMap = m_map;
	CMapMaker copyMap(*originMap);
	m_map = &copyMap;
	m_maxPower = 0;

    char checked = 0;
	int power = 0;
	for(int edge(MAX_POWER); edge > 0; --edge)
	{
		for(int i(0); i < m_searchAreaSize; ++i)
		{
            auto vector = getEnabledFields();
			foreach (auto cell, vector)
			{
                checked = CLogic::checkTurn(cell.first,cell.second,*m_map,m_color, m_type);
				if(checked != ePB_disabled)
				{
					if((checked&ePB_grass) == ePB_grass)
						power = MAX_POWER-2;
					else if((checked&ePB_badMine) == ePB_badMine )
						power = MAX_POWER-1;
					else if((checked&ePB_yourMine) == ePB_yourMine)
						power = MAX_POWER;

					if(m_maxPower < power && !m_rejectedCells.contains(cell))
					{
						m_targetCell = cell;
						m_maxPower = power;
					}
					if(m_maxPower == edge)
						break;
				}
			}
			if(m_maxPower == edge)
				break;
			foreach (auto cell, vector)
				m_map->paintBlock(cell.first,cell.second,m_color);
		}
		if(m_maxPower == edge)
			break;
		copyMap = *originMap;
	}

	m_map = originMap;
}

void CCleverBot::findStart()
{
	CMapMaker* originMap = m_map;
	CMapMaker copyMap(*originMap);
	m_map = &copyMap;

	QColor white(255,255, 255, 255);

	for(int i(0); i < m_map->getSize(); ++i)
		for(int j(0); j < m_map->getSize(); ++j)
			if(m_map->getBlock(i,j).second == m_color)
				m_map->paintBlock(i,j,white);

	m_map->paintBlock(m_targetCell.first,m_targetCell.second,m_color);
	for(int i(0); i < m_searchAreaSize; ++i)
	{
		auto vector = getEnabledFields();
		foreach (auto cell, vector)
		{
			if(m_map->getBlock(cell.first, cell.second).second == white)
			{
				m_startCell = cell;
				m_map = originMap;
				return;
			}

		}
		foreach (auto cell, vector)
			m_map->paintBlock(cell.first,cell.second,m_color);
	}

	m_map = originMap;
}

bool CCleverBot::leeAlgorithm()
{
    QVector<QPair<int, int>> delta = {QPair<int, int>(1,0),
                                      QPair<int, int>(0, 1),
                                      QPair<int, int>(-1, 0),
                                      QPair<int, int>(0, -1)};
    int x, y, k;
	bool stop;

    int distance = 0;
    m_grid[m_startCell.first][m_startCell.second] = 0;
	do {
        stop = true;
        for ( x = 0; x < m_map->getSize(); ++x )
            for ( y = 0; y < m_map->getSize(); ++y )
                if ( m_grid[x][y] == distance )
				{
                    for ( k = 0; k < 4; ++k )
                    {
                        int ix = x + delta[k].first, iy=y + delta[k].second;
                        if ( ix >= 0 && ix < m_map->getSize() &&
                             iy >= 0 && iy < m_map->getSize() &&
                             m_grid[ix][iy] == m_empty )
						{
                            stop = false;
                            m_grid[ix][iy] = distance + 1;
						}
					}
				}
        distance++;
    } while ( !stop && m_grid[m_targetCell.first][m_targetCell.second] == m_empty );

    if (m_grid[m_targetCell.first][m_targetCell.second] == m_empty)
	{
		m_rejectedCells.push_back(m_targetCell);
        return false;
	}

    m_pathLength = m_grid[m_targetCell.first][m_targetCell.second];
	if(m_pathLength > m_searchAreaSize)
	{
		m_rejectedCells.push_back(m_targetCell);
        return false;
	}

    x = m_targetCell.first;
    y = m_targetCell.second;
    if(m_pathLength < 1)
    {
        m_rejectedCells.push_back(m_targetCell);
        return false;
    }
    distance = m_pathLength;
    while ( distance > 0 )
	{
        m_path.push_front(QPair<int, int>(x,y));
        distance--;
		for (k = 0; k < 4; ++k)
        {
            int ix = x + delta[k].first, iy=y + delta[k].second;
            if ( ix >= 0 && ix < m_map->getSize() &&
                 iy >= 0 && iy < m_map->getSize() &&
                 m_grid[ix][iy] == distance)
			{
                x = x + delta[k].first;
                y = y + delta[k].second;
				break;
			}
        }
    }
	return true;
}

void CCleverBot::prepareGrid()
{
	for(int i(0); i < m_map->getSize(); ++i)
		for(int j(0); j < m_map->getSize(); ++j)
		{
            QColor emptyColor(0,0,0,0);
            if(m_map->getBlock(i,j).second == emptyColor&&
			   (m_map->getBlock(i,j).first != eMT_mountain) &&
			   (m_map->getBlock(i,j).first != eMT_rock) &&
			   (m_map->getBlock(i,j).first != eMT_tree))
                m_grid[i][j] = m_empty;
			else
                m_grid[i][j] = m_disable;
		}
}
