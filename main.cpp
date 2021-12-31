#include "mywidget.h"
#include <QApplication>
#include <QElapsedTimer>
#include "mylogin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    myWidget w;
    myLogin w;
    w.show();


    return a.exec();
}
