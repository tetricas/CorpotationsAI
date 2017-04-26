#include "game_space.h"

#include <QImage>
#include <QPoint>
#include <QtDebug>

CGameSpace::CGameSpace(QQuickItem* parent):
	QQuickPaintedItem(parent),
	m_blockSideSize(1),
	m_iPosX(0),
	m_iPosY(0),
	m_alpha(0),
	m_blocksCount(10)
{
	setAcceptedMouseButtons(Qt::AllButtons);
}

void CGameSpace::setBlockSideSize(int blockSideSize)
{
	m_blockSideSize = blockSideSize;
}

int CGameSpace::blocksCount()
{
	return m_blocksCount;
}

void CGameSpace::setTurn()
{
	//m_map.setItemColor(m_iPosX, m_iPosY);
	update();
}

void CGameSpace::paint(QPainter* painter)
{
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
			painter->drawImage(i*m_blockSideSize, j*m_blockSideSize, blockImg);

			QRect rect(i*m_blockSideSize, j*m_blockSideSize, m_blockSideSize, m_blockSideSize);
			painter->fillRect(rect, QBrush(QColor(m_map.getBlock(i,j).second)));
		}
	QPen pen(Qt::blue, 2);
	painter->setPen(pen);
	painter->drawRect(m_iPosX*m_blockSideSize, m_iPosY*m_blockSideSize, m_blockSideSize, m_blockSideSize);
}

void CGameSpace::mouseReleaseEvent(QMouseEvent* event)
{
	m_iPosX = int(event->localPos().x())/m_blockSideSize;
	m_iPosY = int(event->localPos().y())/m_blockSideSize;
	update();
}
