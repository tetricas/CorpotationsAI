#include "base_bot.h"
#include "logic.h"
#include <QtDebug>

CBaseBot::CBaseBot(CMapMaker *map, QColor color, EMapTypes type, QObject *parent) :
	QObject(parent),
	m_map(map),
	m_color(color),
    m_type(type),
    m_loseCounter(0)
{}

QColor CBaseBot::getColor()
{
	return m_color;
}

EMapTypes CBaseBot::getType()
{
	return m_type;
}

QVector<QPair<int, int>> CBaseBot::getEnabledFields()
{
	QVector<QPair<int, int>> enabledFields;
	for( int i(0); i < m_map->getSize(); ++i)
		for (int j(0); j < m_map->getSize(); ++j)
			if(((j+1 < m_map->getSize() && m_map->getBlock(i,j+1).second == m_color) ||
			   (j > 0 && m_map->getBlock(i,j-1).second == m_color) ||
			   (i+1 < m_map->getSize() && m_map->getBlock(i+1,j).second == m_color) ||
			   (i > 0 && m_map->getBlock(i-1,j).second == m_color)) &&
			   !enabledFields.contains(QPair<int, int>(i,j)))
				enabledFields.push_back(QPair<int, int>(i,j));
	return enabledFields;
}
