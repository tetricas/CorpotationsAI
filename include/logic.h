#ifndef CLOGIC_H
#define CLOGIC_H

#include "enum_types.h"

class CLogic
{
public:
    CLogic()
    {}
    EWinState checkGame(MyMapContainer map, QColor);
    EPowerBoost ckeckBlock(int i, int j, MyMapContainer map,
                           QColor myColor, EMapTypes myType);
};

#endif // CLOGIC_H
