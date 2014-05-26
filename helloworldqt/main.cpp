#include <QApplication>
#include <QLabel>
#include <QWidget>

int main(int argc, char *argv[ ])
{
  QApplication app(argc, argv);
  QLabel hello("<center>Hello World</center>");
  hello.setWindowTitle("Hello World from Qt!");
  hello.resize(200, 200);
  hello.show();
  return app.exec();
}

