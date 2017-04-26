#ifndef CMAPMAKER_H
#define CMAPMAKER_H

#include <QString>

#include "enum_types.h"

class CMapMaker
{
public:
	explicit CMapMaker();

	QPair<EMapTypes, QColor> getBlock(int i, int j) const;
	void setBlock(int i, int j, EMapTypes type);
	void paintBlock(int i, int j, QColor color);

private:
	void makeNew();

	MyMapContainer m_map;
	int m_size;
};

#endif // CMAPMAKER_H
