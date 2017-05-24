#include "clever_bot.h"
#include "logic.h"
#include <QtDebug>

CCleverBot::CCleverBot(CMapMaker *map, QColor color, EMapTypes type, QObject *parent) :
	CBaseBot(map, color, type, parent)
{}

void CCleverBot::makeTurn()
{
	qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
	auto vector = getEnabledFields();
	auto turnPos = vector[qrand()%vector.size()+0];
	int* iTurnPos = &turnPos.first;
	int* jTurnPos = &turnPos.second;
	char checked;

	int loseCounter = 0;
	while((checked = CLogic::checkTurn(*iTurnPos,*jTurnPos,*m_map,m_color, m_type)) == ePB_disabled)
	{
		if(loseCounter++ > 10000)
			return;
		turnPos = vector[qrand()%vector.size()+0];
	}

	CLogic::increasePower(checked, *m_map, m_type);

	emit cellWasCaptured(*iTurnPos,*jTurnPos, m_map->getBlock(*iTurnPos,*jTurnPos).second, m_color);
}
