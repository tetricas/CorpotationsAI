#include "map_maker.h"
#include <QtDebug>

CMapMaker::CMapMaker():
	m_size(10)
{
	makeNew();
}

void CMapMaker::makeNew()
{
	qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);;
	for( int i(0); i< m_size; ++i)
	{
		QVector<QPair<EMapTypes, QColor>> line;
		for( int j(0); j< m_size; ++j)
		{
			int rand = qrand()%10;
			EMapTypes enumed;
			if( rand >= 8 && rand <= 9 )
			{
				rand = qrand()%3;
				switch (rand)
				{
				case 0:
					enumed = eMT_gold;
					break;
				case 1:
					enumed = eMT_silver;
					break;
				case 2:
					enumed = eMT_cuper;
					break;
				}
			}
			else if ( rand >= 6 && rand <= 7)
			{
				rand = qrand()%3;
				switch (rand)
				{
				case 0:
					enumed = eMT_mountain;
					break;
				case 1:
					enumed = eMT_rock;
					break;
				case 2:
					enumed = eMT_tree;
					break;
				}
			}
			else if ( rand >= 0 && rand <= 5)
			{
				enumed = eMT_grass;
			}
			else
				Q_ASSERT("CMapMaker error");

			line.push_back({enumed, QColor(0,0,0,0)});
		}
		m_map.push_back(line);
	}
}

QPair<EMapTypes, QColor> CMapMaker::getBlock(int i, int j) const
{
	return m_map.at(i).at(j);
}

void CMapMaker::setBlock(int i, int j, EMapTypes type)
{
	m_map[i][j].first = type;
}

void CMapMaker::paintBlock(int i, int j, QColor color)
{
	m_map[i][j].second = color;
}

int CMapMaker::getSize()
{
	return m_size;
}

void CMapMaker::addNewPower(EMapTypes type)
{
	m_powerMatches[type] = 1;
	qDebug() << "addNewPower[" << type << "]" << m_powerMatches[type];
}

int CMapMaker::getPower(EMapTypes type)
{
	qDebug() << "getPower[" << type << "]" << m_powerMatches[type];
	return m_powerMatches[type];
}

int CMapMaker::getPower(int i, int j)
{
	qDebug() << "getPower[" << i << "," << j << "]" << m_powerMatches[m_map[i][j].first];
	return m_powerMatches[m_map[i][j].first];
}

void CMapMaker::changePower(EMapTypes type, int powerDelta)
{
	m_powerMatches[type] += powerDelta;
	qDebug() << "changePower[" << type << "]" << m_powerMatches[type];
}
