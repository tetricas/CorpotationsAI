#include "clever_bot.h"
#include "logic.h"
#include <QtDebug>

CCleverBot::CCleverBot(CMapMaker *map, QColor color, EMapTypes type, QObject *parent) :
	CBaseBot(map, color, type, parent),
	m_searchAreaSize(3),
	m_maxPower(0),
	m_isOnWay(false),
	m_path(m_map->getSize()),
	m_grid(m_map->getSize(),QVector<int>(m_map->getSize())),
	WALL(-1),
	BLANK(-2)
{
}

void CCleverBot::makeTurn()
{
	char checked = 0;
	m_rejectedCells.clear();
	do
	{
		findTarget(checked);
		findStart();
		prepareGrid();
	}while(!leeAlgorithm());

	CLogic::increasePower(checked, *m_map, m_type);
	emit cellWasCaptured(m_targetCell.first, m_targetCell.second,
						 m_map->getBlock(m_targetCell.first, m_targetCell.second).second, m_color);
}

void CCleverBot::findTarget(char& checked)
{
	CMapMaker* originMap = m_map;
	CMapMaker copyMap(*originMap);
	m_map = &copyMap;
	m_maxPower = 0;

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
	int dx[4] = {1, 0, -1, 0};   // смещения, соответствующие соседям ячейки
	int dy[4] = {0, 1, 0, -1};   // справа, снизу, слева и сверху
	int x, y, k;
	bool stop;

	// распространение волны
	int d = 0;
	m_grid[m_startCell.second][m_startCell.first] = 0;            // стартовая ячейка помечена 0
	do {
		stop = true;               // предполагаем, что все свободные клетки уже помечены
		for ( y = 0; y < m_map->getSize(); ++y )
			for ( x = 0; x < m_map->getSize(); ++x )
				if ( m_grid[y][x] == d )                         // ячейка (x, y) помечена числом d
				{
					for ( k = 0; k < 4; ++k )                    // проходим по всем непомеченным соседям
					{
						int iy=y + dy[k], ix = x + dx[k];
						if ( iy >= 0 && iy < m_map->getSize() && ix >= 0 && ix < m_map->getSize() &&
							 m_grid[iy][ix] == BLANK )
						{
							stop = false;              // найдены непомеченные клетки
							m_grid[iy][ix] = d + 1;      // распространяем волну
						}
					}
				}
		d++;
	} while ( !stop && m_grid[m_targetCell.second][m_targetCell.first] == BLANK );

	if (m_grid[m_targetCell.second][m_targetCell.first] == BLANK)
	{
		m_rejectedCells.push_back(m_targetCell);
		return false;  // путь не найден
	}

	// восстановление пути
	m_pathLength = m_grid[m_targetCell.second][m_targetCell.first]; // длина кратчайшего пути из startCell в target
	if(m_pathLength > m_searchAreaSize)
	{
		m_rejectedCells.push_back(m_targetCell);
		return false;  // путь не найден
	}

	x = m_targetCell.second;
	y = m_targetCell.first;
	d = m_pathLength;
	while ( d > 0 )
	{
		m_path[d] = QPair<int, int>(x,y);
		d--;
		for (k = 0; k < 4; ++k)
		{
			int iy=y + dy[k], ix = x + dx[k];
			if ( iy >= 0 && iy < m_map->getSize() && ix >= 0 && ix < m_map->getSize() &&
				 m_grid[iy][ix] == d)
			{
				x = x + dx[k];
				y = y + dy[k];           // переходим в ячейку, которая на 1 ближе к старту
				break;
			}
		}
	}
	m_path[0] = QPair<int, int>(m_startCell.first, m_startCell.second);
	return true;
}

void CCleverBot::prepareGrid()
{
	for(int i(0); i < m_map->getSize(); ++i)
		for(int j(0); j < m_map->getSize(); ++j)
		{
			if(m_map->getBlock(i,j).second == QColor(0,0,0,0)&&
			   (m_map->getBlock(i,j).first != eMT_mountain) &&
			   (m_map->getBlock(i,j).first != eMT_rock) &&
			   (m_map->getBlock(i,j).first != eMT_tree))
				m_grid[j][i] = BLANK;
			else
				m_grid[j][i] = WALL;
		}
}
