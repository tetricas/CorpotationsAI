#include "easy_bot.h"
#include "logic.h"
#include <QtDebug>

CEasyBot::CEasyBot(CMapMaker *map, QColor color, EMapTypes type, QObject *parent) :
	QObject(parent),
	m_map(map),
	m_color(color),
	m_type(type),
	m_power(40)
{}

QColor CEasyBot::getColor()
{
	return m_color;
}

EMapTypes CEasyBot::getType()
{
	return m_type;
}

int CEasyBot::getPower()
{
	return m_power;
}

void CEasyBot::makeTurn()
{
	qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
	auto vector = getEnabledFields();
	auto turnPos = vector[qrand()%vector.size()+0];
	int* iTurnPos = &turnPos.first;
	int* jTurnPos = &turnPos.second;

	while(CLogic::checkTurn(*iTurnPos,*jTurnPos,*m_map,m_color, m_type) == ePB_disabled)
		turnPos = vector[qrand()%vector.size()+0];

	emit cellWasCaptured(*iTurnPos,*jTurnPos, m_map->getBlock(*iTurnPos,*jTurnPos).second, m_color);
}

void CEasyBot::takeAwayPower(int i, int j)
{
	m_power += CLogic::calculatePower(i, j, *m_map, m_type);
}

QVector<QPair<int, int>> CEasyBot::getEnabledFields()
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
