#include <QTime>
#include <QThread>
#include <QDebug>
#include "monitor.h"
#include "msgbuffermodel.h"

MsgBufferModel::MsgBufferModel(QObject *parent)
	:QAbstractTableModel(parent)
{
	/* Object Variables. */
	lastValue = 0;



	/* GUI Refresh. */
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(timerHit()));
	timer->start(1000);

	/* Monitor Threads. */
	QThread *threadx = new QThread;
	Monitor *monitor = new Monitor;

	connect(monitor, SIGNAL(messageInBuffer(canMessage*)), this, SLOT(newMsg(canMessage*)));
	connect(this, SIGNAL(start()), monitor, SLOT(start()));
	connect(this, SIGNAL(stop()), monitor, SLOT(stop()));
	monitor->moveToThread(threadx);
	threadx->start();

	emit start();
}

void MsgBufferModel::timerHit()
{
	if (monitorMsgQueue.isEmpty())
	{
		return;
	}

	while (!monitorMsgQueue.isEmpty())
	{
		dataEntry entry;

		entry.lastMsg = monitorMsgQueue.dequeue();
		entry.key = entry.lastMsg.identifier;
		entry.lastMsgTime = entry.lastMsg.time;
		if (dataMap.contains(entry.key))
		{
			entry.totalMsgCount = dataMap[entry.key].totalMsgCount + 1;
		}
		else
		{
			beginResetModel();
			entry.totalMsgCount = 1;
			dataMap[entry.key] = entry;
			endResetModel();

			emit start();
			return;
		}

		dataMap[entry.key] = entry;
		emit start();
	}

	QModelIndex columnTop = createIndex(0, 0);
	QModelIndex columnBottom = createIndex(dataMap.count(), 4);

	emit dataChanged(columnTop, columnBottom);
}

void MsgBufferModel::newMsg(canMessage *msg)
{
	monitorMsgQueue.enqueue(*msg);
}

int MsgBufferModel::rowCount(const QModelIndex & /*parent*/) const
{
	return dataMap.count();
}

int MsgBufferModel::columnCount(const QModelIndex & /*parent*/) const
{
	return 4;
}

QVariant MsgBufferModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString("Time");
			case 1:
				return QString("Bus/Addr");
			case 2:
				return QString("Total");
			case 3:
				return QString("Last Msg");
			}
		}
	}

	return QVariant();
}

QVariant MsgBufferModel::data(const QModelIndex &index, int role) const
{
	int findCount = 0;
	int row = index.row();
	int column = index.column();
	dataEntry entry;
	int found = 0;

	QMapIterator<QString, dataEntry> i(dataMap);
	while (i.hasNext())
	{
		i.next();
		if (findCount == row)
		{
			entry = i.value();
			found = 1;

			break;
		}
		findCount++;
	}
	if (found == 0)
	{
		return QVariant();
	}

	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
		case 0:
			return entry.lastMsgTime.toString();
		case 1:
			return entry.key;
		case 2:
			return QString("%1").arg(entry.totalMsgCount);
		case 3:
			return entry.lastMsg.content;
		default:
			return QString("N/A");
		}

		//return QString("%1,%2, LV%3")
		//		.arg(row + 1)
		//		.arg(column + 1)
		//		.arg(lastValue);
	}

	return QVariant();
}
