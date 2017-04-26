#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QtNetwork>
#include <QByteArray>

#include "map_maker.h"
#include "logic.h"

class CClient : public QTcpSocket, public CMapMaker
{
Q_OBJECT

public:
    explicit CClient(QTcpSocket *parent = Q_NULLPTR);

    void setItemColor(int i, int j);
    bool isItTurn();

    Q_INVOKABLE void setConnection();

signals:
    void updateData();
    void connected();
    void notConnected();

private slots:
    void readSocket();

private:
    quint8 m_index;
    quint8 m_currIndex;
    QColor m_color;
    EMapTypes m_type;
    CLogic m_gameLogic;
};

#endif // CLIENT_H
