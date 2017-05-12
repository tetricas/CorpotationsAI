#include "game_space.h"

#include <QImage>
#include <QPoint>
#include <QtDebug>

CGameSpace::CGameSpace(QQuickItem* parent):
	QQuickPaintedItem(parent),
	m_blockSideSize(1),
	m_shift(1),
	m_iPosX(0),
	m_iPosY(0),
	m_color(QColor(255, 0, 0, 100)),
	m_type(eMT_gold),
	m_power(1),
	m_blocksCount(10),
	m_easyBot(&m_map, QColor(0, 0, 255, 100), eMT_silver)
{
	setAcceptedMouseButtons(Qt::AllButtons);

	qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);;
	quint8 iRand = qrand()%10+0, jRand = qrand()%10+0;
	while((CLogic::checkBlock(iRand,jRand,m_map,m_color, m_type)&ePB_grass) != ePB_grass)
	{
		iRand = qrand()%10+0;
		jRand = qrand()%10+0;
	}
	m_map.paintBlock(iRand, jRand, m_color);

	while(((CLogic::checkBlock(iRand,jRand,m_map,m_easyBot.getColor(), m_easyBot.getType())&ePB_grass) != ePB_grass) ||
		  ((CLogic::checkBlock(iRand,jRand,m_map,m_easyBot.getColor(), m_easyBot.getType())&ePB_foreign) == ePB_foreign))
	{
		iRand = qrand()%10+0;
		jRand = qrand()%10+0;
	}
	m_map.paintBlock(iRand, jRand, m_easyBot.getColor());

	connect(&m_easyBot , &CEasyBot::cellWasCaptured, this, &CGameSpace::cellOwnerChanged);
}

void CGameSpace::setTurn()
{
	char checked = CLogic::checkTurn(m_iPosX,m_iPosY,m_map,m_color, m_type);

	if((int)checked==ePB_disabled)
		return;

	if(((checked&ePB_foreign)==ePB_foreign)&&(m_power < m_easyBot.getPower()))
		return;

	int cellPower = 0;
	if((checked&ePB_grass) == ePB_grass)
		cellPower+=1;
	else if((checked&ePB_badMine) == ePB_badMine )
		cellPower+=2;
	else if((checked&ePB_yourMine) == ePB_yourMine)
		cellPower+=3;

	m_power += cellPower;
	cellOwnerChanged(m_iPosX, m_iPosY, m_map.getBlock(m_iPosX, m_iPosY).second, m_color);

	m_easyBot.makeTurn();
}

int CGameSpace::blocksCount()
{
	return m_blocksCount;
}

void CGameSpace::cellOwnerChanged(int i, int j, QColor oldColor, QColor newColor)
{
	if(oldColor == m_color)
		m_power += CLogic::calculatePower(i, j, m_map, m_type);
	if(oldColor == m_easyBot.getColor())
		m_easyBot.takeAwayPower(i, j);

	m_map.paintBlock(i, j, newColor);
	update();

	if(CLogic::checkGame(m_map,newColor) == eWS_win)
		emit gameFinished(newColor);
}

void CGameSpace::paint(QPainter* painter)
{
	//border
	QRect border(0, 0, width(), height());
	painter->fillRect(border, QBrush(QColor("#036D19")));
	//field
	int fieldShift = ( width() - m_blockSideSize*10 ) / 2;
	for( int i(0); i < m_blocksCount; ++i)
		for (int j(0); j < m_blocksCount; ++j)
		{
			QImage blockImg;
			switch(m_map.getBlock(i,j).first)
			{
			case eMT_gold:
				blockImg = QImage(":/images/gold_mine.jpg");
				break;
			case eMT_silver:
				blockImg = QImage(":/images/silver_mine.jpg");
				break;
			case eMT_cuper:
				blockImg = QImage(":/images/cuper_mine.jpg");
				break;
			case eMT_mountain:
				blockImg = QImage(":/images/mountain.jpg");
				break;
			case eMT_rock:
				blockImg = QImage(":/images/rock.jpg");
				break;
			case eMT_tree:
				blockImg = QImage(":/images/tree.jpg");
				break;
			case eMT_grass:
				blockImg = QImage(":/images/grass.jpg");
				break;
			}

			blockImg = blockImg.scaled(m_blockSideSize, m_blockSideSize, Qt::KeepAspectRatio);
			painter->drawImage(i*m_blockSideSize + fieldShift, j*m_blockSideSize + fieldShift, blockImg);

			QRect rect(i*m_blockSideSize + fieldShift, j*m_blockSideSize + fieldShift, m_blockSideSize, m_blockSideSize);
			painter->fillRect(rect, QBrush(QColor(m_map.getBlock(i,j).second)));
		}
	//player pointer
	QPen pen(Qt::blue, 2);
	painter->setPen(pen);
	painter->drawRect(m_iPosX*m_blockSideSize + fieldShift, m_iPosY*m_blockSideSize + fieldShift, m_blockSideSize, m_blockSideSize);
}

void CGameSpace::mousePressEvent(QMouseEvent* event)
{
	m_iPosX = int(event->localPos().x())/m_blockSideSize;
	m_iPosY = int(event->localPos().y())/m_blockSideSize;
	update();
}
