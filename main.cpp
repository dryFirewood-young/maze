#include "mywidget.h"
#include <QApplication>
#include <QElapsedTimer>
#include "mylogin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    int delayTime = 5;
//    QElapsedTimer timer;
//    timer.start();
//    while(timer.elapsed() < (delayTime * 1000))
//    {
//         a.processEvents();
//    }

//    myWidget w;
    myLogin w;
    w.show();


    return a.exec();
}
