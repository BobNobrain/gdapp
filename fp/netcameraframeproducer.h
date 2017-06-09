#ifndef NETCAMERAFRAMEPRODUCER_H
#define NETCAMERAFRAMEPRODUCER_H

#include "common/abstractframeproducer.h"
#include <QTcpServer>
#include <QTcpSocket>

class NetCameraFrameProducer: public AbstractFrameProducer
{
	Q_OBJECT
public:
	NetCameraFrameProducer();
	~NetCameraFrameProducer();

protected:
	QTcpServer* myServer;
	short width;
	short height;
	int temp = 0;
	QVector<char> data;

	bool changePort(int port);
	void startProducing() override;

private:
	void createImageAndNotify();
	void decodeImage();

	QTcpSocket* camera;
	enum COMMAND
	{
		DATA = 0x00,

		HELLO_SERVER = 0x1E,
		HELLO_CLIENT = 0x1A,

		DATA_RECEIVED = 0x2D,

		LENGTH_CHANGE = 0x31,
		FONE_RESET = 0x3F,
		COMAND_EXECUTED = 0x3E,

		GB_SERVER = 0x45,
		GB_CLIENT = 0x4C,

		ERROR = 0x66
	};

	void sendMsg(QString message);

	bool read(int &var);
	bool read(char &var);
	bool read(short &var);

	void findLocalAddress();

	int length;
	int port;

	char command;

	QString adr;
private slots:
	void startServer();
	void stopServer();
	void disconnectUser();
	void readMsg();
	void sendMsg(COMMAND cmd);
	void newConnectionUser();
};

#endif // NETCAMERAFRAMEPRODUCER_H
