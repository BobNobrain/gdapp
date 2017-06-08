#ifndef ABSTRACTGESTUREDESCRIPTOR_H
#define ABSTRACTGESTUREDESCRIPTOR_H


class AbstractGestureDescriptor
{
public:
	AbstractGestureDescriptor();
	~AbstractGestureDescriptor();

	virtual float similarTo(AbstractGestureDescriptor* templateDesctiptor) = 0;
};

#endif // ABSTRACTGESTUREDESCRIPTOR_H
