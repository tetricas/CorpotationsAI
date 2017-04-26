#ifndef CSERVER_H
#define CSERVER_H

#include <QtNetwork>
#include <QByteArray>

#include "client.h"
#include "map_maker.h"

class CServer : public QTcpServer
{
    Q_OBJECT

public:
    explicit CServer(QObject *parent = 0);
    ~CServer();

private slots:
    void newuser();
    void slotReadClient();

private:
    int getCurrentClient();

    QMap<quint8, QTcpSocket*> m_сlients;
    CMapMaker m_map;
    quint8 m_currentClient;
    int m_size;
};

#endif // CSERVER_H
