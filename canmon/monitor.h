#ifndef __MONITOR_H__
#define __MONITOR_H__

#include <QObject>
#include <QTime>

#include <linux/can.h>
#include <linux/can/raw.h>

typedef struct
{
	int		interface;
	QString	identifier;
	QTime	time;
	QString	content;
} canMessage;

class Monitor : public QObject
{
	Q_OBJECT

public:
	Monitor();
public slots:
	void start();
	void stop();
signals:
	void messageInBuffer(canMessage *msg);
private:
	void sendMsg(struct canfd_frame *frame, int maxdlen);
	int running;
};

#endif
