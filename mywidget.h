#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QDialog>
#include <QQueue>

#include "mylinkstack.h"
#include "myconf.h"


namespace Ui {
class myWidget;
}

class myWidget : public QDialog
{
    Q_OBJECT
public:
    int mainMaze(void);
    void findButton( int x, int y, QString iconName);
    void displayMaze();
    void showWindow(QString outPath);
    void readMaze( QString maze);
    void outMaze(QString outPath);
    void setWall(int**maze);
    void setPath();

    char** out_maze = nullptr;
protected:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *);
public:
    explicit myWidget(QWidget *parent = nullptr);
    ~myWidget();


signals:
    void enterMaze();

private:
    Ui::myWidget *ui;

    bool _isReady = false;
    bool _isChange = false;
    int _tId;
    QQueue<myLinkStack::DataType> _qe;
    QString _outPath;
};

#endif // MYWIDGET_H
