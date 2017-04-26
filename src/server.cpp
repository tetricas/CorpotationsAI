#include "server.h"
#include <QtDebug>

CServer::CServer(QObject *parent):
    QTcpServer(parent),
    m_currentClient(2)
{
    connect(this, SIGNAL(newConnection()), this, SLOT(newuser()));
    if (!listen(QHostAddress::LocalHost, 33333))
        qDebug() << QObject::tr("Unable to start the server: %1.").arg(errorString());
    else
        qDebug() << isListening() << "TCPSocket listen on port";
}

void CServer::newuser()
{
    qDebug() << QString::fromUtf8("У нас новое соединение!");
    QTcpSocket* clientSocket = nextPendingConnection();
    quint8 idusersocs = clientSocket->socketDescriptor();
    m_сlients[idusersocs] = clientSocket;
    connect(m_сlients[idusersocs],SIGNAL(readyRead()),this, SLOT(slotReadClient()));

    QByteArray byteArray;
    QDataStream out(&byteArray,QIODevice::WriteOnly);

    quint8 type = 0;
    QColor color;
    EMapTypes eType;
    switch(m_сlients.size())
    {
    case 1:
        color = QColor(idusersocs, 0, 0, 128);
        eType = eMT_gold;
        break;
    case 2:
        color = QColor(0, idusersocs, 0, 128);
        eType = eMT_silver;
        break;
    case 3:
        color = QColor(0, 0, idusersocs, 128);
        eType = eMT_cuper;
        break;
    }
    quint8 iRand = qrand()%10, jRand = qrand()%10;
    m_map.paintBlock(iRand, jRand, color);

    out << type << idusersocs << color << static_cast<quint8>(eType);
    for( int i(0); i < 10; ++i)
        for ( int j(0); j < 10; ++j)
            out << i << j << static_cast<quint8>(m_map.getBlock(i,j).first) << m_map.getBlock(i,j).second;
    out << m_сlients.begin().key();
    m_сlients[idusersocs]->write(byteArray);
}

void CServer::slotReadClient()
{
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    int idusersocs = clientSocket->socketDescriptor();
    QByteArray data = clientSocket->readAll();

    int type = 1;
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);

    out << type << data << getCurrentClient();
    foreach(QTcpSocket *socket, m_сlients)
        if ( socket->socketDescriptor() != idusersocs )
            socket->write(byteArray);
}

int CServer::getCurrentClient()
{
    if(m_currentClient == 2)
        m_currentClient = 0;
    else
        ++m_currentClient;
    return (m_сlients.begin()+m_currentClient).key();
}

CServer::~CServer()
{
    foreach(int i, m_сlients.keys())
    {
        QTextStream os(m_сlients[i]);
        os.setAutoDetectUnicode(true);
        os << QDateTime::currentDateTime().toString() << "\n";
        m_сlients[i]->close();
        m_сlients.remove(i);
    }
    close();
    qDebug() << QString::fromUtf8("Сервер остановлен!");
}
