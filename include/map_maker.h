#ifndef CMAPMAKER_H
#define CMAPMAKER_H

#include <QString>
#include <QDateTime>
#include <QMap>

#include "enum_types.h"

class CMapMaker
{
public:
	explicit CMapMaker();

	QPair<EMapTypes, QColor> getBlock(int i, int j) const;
	void setBlock(int i, int j, EMapTypes type);
	void paintBlock(int i, int j, QColor color);

	int getSize();

	void addNewPower(EMapTypes type);
	int getPower(EMapTypes type);
	int getPower(int i, int j);
	void changePower(EMapTypes type, int powerDelta);

private:
	void makeNew();

	MyMapContainer m_map;
	int m_size;
	QMap<EMapTypes, int> m_powerMatches;
};

#endif // CMAPMAKER_H
