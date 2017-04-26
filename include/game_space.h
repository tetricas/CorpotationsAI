#ifndef CGAMESPACE_H
#define CGAMESPACE_H

#include <QtQuick/QQuickPaintedItem>
#include <QMouseEvent>
#include <QPainter>

#include "client.h"
#include "server.h"

class CGameSpace : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int blockSideSize WRITE setBlockSideSize)
    Q_PROPERTY(int blocksCount READ blocksCount CONSTANT)
    Q_PROPERTY(bool isConnected READ isConnected NOTIFY isConnectedChanged)

public:
    explicit CGameSpace(QQuickItem* parent = nullptr);

    void setBlockSideSize(int sideSize);
    int blocksCount();
    bool isConnected();

    Q_INVOKABLE void setTurn();
    Q_INVOKABLE void reconnect();
    Q_INVOKABLE void makeServer();

signals:
    void blocksCountChanged();
    void isConnectedChanged();

protected:
    virtual void paint(QPainter* painter);
    virtual void mouseReleaseEvent(QMouseEvent* event);

private:
    CClient m_map;
    CServer* m_server;
    int m_blockSideSize;
    int m_blocksCount;
    int m_iPosX;
    int m_iPosY;
    int m_alpha;
    bool m_isConnected;
};

#endif // CGAMESPACE_H
