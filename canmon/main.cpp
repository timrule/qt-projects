#include <QApplication>
#include <QTableView>
#include "msgbuffermodel.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTableView view;
	MsgBufferModel model(0);

	view.setModel(&model);
	view.show();

	return a.exec();
}

