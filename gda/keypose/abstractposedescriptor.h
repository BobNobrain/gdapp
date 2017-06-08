#ifndef ABSTRACTPOSEDESCRIPTOR_H
#define ABSTRACTPOSEDESCRIPTOR_H


class AbstractPoseDescriptor
{
public:
	AbstractPoseDescriptor();
	~AbstractPoseDescriptor();

	virtual float similarTo(AbstractPoseDescriptor* templatePose) = 0;
};

#endif // ABSTRACTPOSEDESCRIPTOR_H
