#include "client.h"
#include <QtDebug>

CClient::CClient(QTcpSocket *parent) :
    QTcpSocket(parent),
    CMapMaker()
{
    connect(this, SIGNAL(readyRead()), this, SLOT(readSocket()));
}

void CClient::setItemColor(int i, int j)
{
    if(m_gameLogic.ckeckBlock(i,j,m_map,m_color, m_type) != ePB_disabled)
    {
        paintBlock(i, j, m_color);
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);
        QDataStream out(&buffer);
        out << i << j << m_color;
        write(byteArray);
    }
    if( m_gameLogic.checkGame(m_map,m_color) == eWS_win )
        qDebug() << "eWS_win";
    else if( m_gameLogic.checkGame(m_map,m_color) == eWS_lose )
        qDebug() << "eWS_lose";
}

bool CClient::isItTurn()
{
    return m_index == m_currIndex;
}

void CClient::setConnection()
{
    connectToHost(QHostAddress::LocalHost, 33333);
    if (waitForConnected(1000))
        emit connected();
    else
        emit notConnected();
}

void CClient::readSocket()
{
    QByteArray byteArray(readAll());
    QDataStream stream(&byteArray, QIODevice::ReadOnly);
    quint8 type;
    int iIndex, jIndex;
    QColor color;
    quint8 blockType, myType;
    stream >> type;
    switch(type)
    {
    case 0:
        stream >> m_index >> m_color >> myType;
        m_type = static_cast<EMapTypes>(myType);
        for(int i(0); i < m_size*m_size; ++i)
        {
            stream >> iIndex >> jIndex >> blockType >> color;
            setBlock(iIndex, jIndex, static_cast<EMapTypes>(blockType));
            paintBlock(iIndex, jIndex, color);
            emit updateData();
        }
        stream >> m_currIndex;
        break;
    case 1:
        stream >> iIndex >> jIndex >> color >> m_currIndex;
        paintBlock(iIndex, jIndex, color);
        break;
    }
}
