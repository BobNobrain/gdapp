#ifndef KEYPOSEGDA_H
#define KEYPOSEGDA_H

#include <QObject>
#include "gda/abstractgda.h"
#include "abstractposedescriptor.h"
#include "keyposegesturedescriptor.h"

class KeyPoseGDA : public AbstractGDA
{
	Q_OBJECT
public:
	KeyPoseGDA();
	~KeyPoseGDA();
};

#endif // KEYPOSEGDA_H
