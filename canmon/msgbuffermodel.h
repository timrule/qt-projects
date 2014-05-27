#ifndef __MSGBUFFERMODEL_H__
#define __MSGBUFFERMODEL_H__

#include <QAbstractTableModel>
#include <QTimer>
#include <QQueue>
#include "monitor.h"

typedef struct
{
	QString		key;
	canMessage	lastMsg;
	QTime		lastMsgTime;
	int			totalMsgCount;
} dataEntry;

class MsgBufferModel : public QAbstractTableModel
{
	Q_OBJECT
public:
	MsgBufferModel(QObject *parent);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
public slots:
    void timerHit();
    void newMsg(canMessage *msg);
signals:
	void start();
	void stop();
private:
    QTimer *timer;
    int lastValue;
    QQueue<canMessage> monitorMsgQueue;
    QMap<QString, dataEntry> dataMap;
};

#endif
