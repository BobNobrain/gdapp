#ifndef ABSTRACTGDA_H
#define ABSTRACTGDA_H

#include <QObject>
#include "common/abstractframeconsumer.h"
#include "common/abstractgesturedetector.h"
#include "common/gesturelibrary.h"
#include "gda/common/abstractgesturedescriptor.h"

// Here you can see some hack to avoid multiple inheritance from QObject:
// AbstractGDA is presented as composition of AbstractGDA and AbstractGDAEmitter
// AbstractGDA does all work of image processing and gesture detection while
// AbstractGDAEmitter is used to emit signals of gesture detection that is done
// by AbstractGDA

class AbstractGDA;

class AbstractGDAEmitter: public AbstractGestureDetector
{
public:
	AbstractGDAEmitter(AbstractGDA* parent)
	{
		this->parent = parent;
	}

	void emitGestureDetected(int gestureId)
	{
		onGestureDetected(gestureId);
	}

	std::string& getGestureName(int gestureId) override;

private:
	AbstractGDA* parent;
	static std::string& getErrorName()
	{
		static std::string en = "(no gesture library provided)";
		return en;
	}
};

class AbstractGDA: public AbstractFrameConsumer
{
	Q_OBJECT
public:
	AbstractGDA(std::string glibFilename);
	~AbstractGDA();

	AbstractGestureDetector* getDetector();
	std::string& getGestureName(int gestureId);

protected:
	/**
	 * @brief Call this method every time you obtained a gesture descriptor.
	 * It will call internally GestureLibrary::match to chech if the candidate
	 * is a predefined gesture. If a match found, it will emit signal
	 * GESTURE_DETECTED internally.
	 * @param candidate - the obtained descriptor that can be a predefined gesture.
	 */
	void onGestureCandidate(AbstractGestureDescriptor* candidate);

	virtual int classifyGesture(AbstractGestureDescriptor* gesture);

	/**
	 * @brief Variable is used to compare gesture candidates with gesture models in library
	 */
	float matchingAccuracy;

	GestureLibrary glib;

private:
	AbstractGDAEmitter emitter;
};

#endif // ABSTRACTGDA_H
