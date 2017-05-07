#include "easy_bot.h"

CEasyBot::CEasyBot(CMapMaker *map, QColor color, EMapTypes type, QObject *parent) :
    QObject(parent),
    m_map(map),
    m_color(color),
    m_type(type),
    m_power(1)
{

}

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

int CEasyBot::takeAwayPower(int power)
{
    m_power-= power;
    return m_power;
}
