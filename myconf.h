#ifndef MYCONF_H
#define MYCONF_H

#include <QObject>
#include <QDebug>
#include <QWidget>
#include <QString>
#include <QListWidgetItem>

#define cout qDebug() << "[ " << __FILE__ << ":"  << __LINE__ << " ] "
#define CONFDIR        "conf"
#define CONFFILE        "conf/maze.in"     // 配置文件
#define DEFAFILE        "conf/maze.out"     // 配置文件
#include "mylinkstack.h"

class myConf : public QObject
{
    Q_OBJECT
private:
    explicit myConf(QObject *parent = nullptr);
    ~myConf();
public:
    void getCfgValue(QString title, QString key, QString path = CONFFILE);
    void writeConfInfo(QString path = CONFFILE);
    void writeMazePath(const char* maze[], QString path = DEFAFILE);
    int ** get_maze();

public:
    static myConf& Instance();
private:
    int **_mazeTmp = nullptr;
signals:

public slots:
};

#endif // MYCONF_H
