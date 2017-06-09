#ifndef GESTURELIBRARY_H
#define GESTURELIBRARY_H

#include <string>
#include <vector>
#include "gda/common/abstractgesturedescriptor.h"

class GestureLibrary
{
public:
	GestureLibrary();
	~GestureLibrary();

	void load(std::string filename);

	int match(AbstractGestureDescriptor* gesture, float accuracy);

	std::string& getGestureName(int gestureId);

protected:
	std::vector<AbstractGestureDescriptor*> contents;
};

#endif // GESTURELIBRARY_H
