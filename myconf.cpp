#include <QFile>
#include <QMap>
#include <QDir>
#include <QTime>
#include <QFileInfo>
#include <QDateTime>
#include <QJsonArray>
#include <QJsonObject>
#include <QApplication>
#include <QJsonDocument>
#include <QFileInfoList>

#include <QVector>
#include "myconf.h"

myConf::myConf(QObject *parent) : QObject(parent)
{
    Q_UNUSED(parent);
    QDir dir(CONFDIR);
    if(!dir.exists())
    {
        dir.mkpath(CONFDIR);
        cout << CONFDIR << "创建成功！！！";
    }

    if(_mazeTmp)
    {
        qDebug() << "[error] _mazeTmp != nullptr";
        free(_mazeTmp);
    }
    _mazeTmp = new int*[8];
    for(int j = 0; j < 8; j++)
    {
        _mazeTmp[j] = new int[11];
    }

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            _mazeTmp[i][j] = -1;
        }
    }
}

myConf::~myConf()
{
    if(_mazeTmp)
        delete [] _mazeTmp;
}


/* -------------------------------------------*/
/**
 *  title     配置文件title名称[title]
 *  key       key
 *  path      配置文件路径
 *
 */
/* -------------------------------------------*/
void myConf::getCfgValue(QString title, QString key, QString path)
{    
    QFile file(path);

    // 只读方式打开
    if( false == file.open(QIODevice::ReadOnly) )
    {
        // 打开失败
        cout << "file open err";
        return;
    }

    QByteArray json = file.readAll(); // 读取所有内容
    file.close(); // 关闭文件

    QJsonParseError error;

    // 将来源数据json转化为JsonDocument
    // 由QByteArray对象构造一个QJsonDocument对象，用于我们的读写操作
    QJsonDocument doc = QJsonDocument::fromJson(json, &error);
    if (error.error == QJsonParseError::NoError) // 没有出错
    {
        if (doc.isNull() || doc.isEmpty())
        {
            cout << "doc.isNull() || doc.isEmpty()";
            return;
        }

        if( doc.isObject()) // 如果对象不为空
        {
            // QJsonObject json对象，描述json数据中{}括起来部分
            QJsonObject obj = doc.object();// 取得最外层这个大对象

            QJsonObject tmp = obj.value( title ).toObject();
            QStringList list = tmp.keys(); // 取出key列表
            for(int i = 0; i < list.size(); ++i)
            {
                if( list.at(i) == key )
                {
                    QString ret = tmp.value( list.at(i) ).toString();
                    QStringList list = ret.split("},{");
//                    QChar ch_t('1'); //49
//                    QChar ch_f('0'); //48

                    int count = 0;
                    for(int m = 1; count < 12; m++)
                    {
                        if(list.at(0).at(m).unicode() == 49)
                            (_mazeTmp[0][count]) = 1;
                        else if(list.at(0).at(m).unicode() == 48){
                            (_mazeTmp[0][count]) = 0;
                        }else {
                            continue;
                        }
                        count++;
                    }

                    count = 0;
                    for(int m = 1; m < 8; m++)
                    {
                        for(int n = 0, count = 0; count < 11; n++)
                        {
                            if(list.at(m).at(n).unicode() == 49)
                            {
                                (_mazeTmp[m][count]) = 1;
                            }
                            else if(list.at(m).at(n).unicode() == 48){
                                (_mazeTmp[m][count]) = 0;
                            }else {
                                continue;
                            }
                            count++;
                        }
                    }

//                    for(int i = 0; i < 8; i++)
//                    {
//                        for(int j = 0; j < 11; j++)
//                        {
//                            qDebug() << "l<" << i << "> c<" << j << "> " << _mazeTmp[i][j];
//                        }
//                    }

                    return ;
                }
            }

        }
    }
    else
    {
        cout << "err = " << error.errorString();
    }



    return;
}

// 写入配置文件
void myConf::writeConfInfo(QString path)
{
    //迷宫
//    int maze[][11] = {
//        {1,1,1,1,1,1,1,1,1,1,1},
//        {1,0,1,0,0,1,1,1,0,0,1},
//        {1,0,0,0,0,0,1,0,0,1,1},
//        {1,0,1,1,1,0,0,0,0,1,1},
//        {1,0,0,0,1,0,1,1,0,0,1},
//        {1,1,0,0,1,0,1,0,1,0,1},
//        {1,1,1,0,0,0,0,0,1,0,1},
//        {1,1,1,1,1,1,1,1,1,1,1}
//    };



    QMap<QString, QVariant> maze;
    maze.insert("maze1", "{1,1,1,1,1,1,1,1,1,1,1},"
    "{1,0,1,0,0,1,1,1,0,0,1},"
    "{1,0,0,0,0,0,1,0,0,1,1},"
    "{1,0,1,1,1,0,0,0,1,1,1},"
    "{1,0,0,0,1,0,1,1,0,1,1},"
    "{1,1,0,0,1,0,1,0,0,0,1},"
    "{1,1,1,0,0,0,0,0,1,0,1},"
    "{1,1,1,1,1,1,1,1,1,1,1}"
    );

    maze.insert("maze2",
       "{1,1,1,1,1,1,1,1,1,1,1},"
       "{1,0,1,0,0,1,1,1,0,0,1},"
       "{1,0,0,0,0,0,1,0,0,1,1},"
       "{1,0,1,1,1,0,0,0,0,1,1},"
       "{1,0,0,0,1,0,1,1,0,0,1},"
       "{1,1,0,0,1,0,1,0,1,0,1},"
       "{1,1,1,0,0,0,0,0,1,0,1},"
       "{1,1,1,1,1,1,1,1,1,1,1}"
    );

    maze.insert("maze3",
       "{1,1,1,1,1,1,1,1,1,1,1},"
       "{1,0,1,0,0,1,1,1,0,0,1},"
       "{1,0,0,0,0,0,1,0,0,1,1},"
       "{1,0,1,1,1,0,0,0,1,1,1},"
       "{1,0,0,1,0,0,1,1,0,0,1},"
       "{1,1,0,0,0,1,0,0,0,1,1},"
       "{1,1,1,0,0,0,0,1,0,0,1},"
       "{1,1,1,1,1,1,1,1,1,1,1}"
    );

    maze.insert("maze4",
       "{1,1,1,1,1,1,1,1,1,1,1},"
       "{1,0,1,0,0,1,1,1,0,0,1},"
       "{1,0,0,0,0,0,1,0,0,1,1},"
       "{1,0,1,1,0,1,0,0,1,1,1},"
       "{1,0,0,0,1,0,1,0,0,1,1},"
       "{1,1,0,0,1,0,1,0,0,0,1},"
       "{1,1,1,0,0,0,0,0,1,0,1},"
       "{1,1,1,1,1,1,1,1,1,1,1}"
    );

    maze.insert("maze5",
       "{1,1,1,1,1,1,1,1,1,1,1},"
       "{1,0,1,0,0,1,1,1,0,0,1},"
       "{1,0,0,0,0,0,1,0,0,1,1},"
       "{1,0,1,1,1,0,0,0,0,1,1},"
       "{1,0,0,0,1,0,1,1,0,1,1},"
       "{1,1,0,0,1,0,1,0,1,0,1},"
       "{1,1,1,0,0,0,0,0,1,0,1},"
       "{1,1,1,1,1,1,1,1,1,1,1}"
    );

    QMap<QString, QVariant> json;
    json.insert("totalMaze", maze);
    QJsonDocument jsonDocument = QJsonDocument::fromVariant(json);
    if ( jsonDocument.isNull() == true)
    {
        cout << " QJsonDocument::fromVariant(json) err";
        return;
    }

    QFile file(path);

    if( false == file.open(QIODevice::WriteOnly) )
    {
        cout << "file open err";
        return;
    }


    //json内容写入文件
    file.write(jsonDocument.toJson());
    file.close();
}

void myConf::writeMazePath(const char* maze[],  QString path)
{
    if(path.isEmpty())
        path = QString(DEFAFILE);

    QFile file(path);
    if( false == file.open(QIODevice::WriteOnly) )
    {
        cout << "file open err";
        return;
    }

    QString str;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            str.append("    ");
            str.append(QChar(maze[i][j]));
        }
        str.append("\n");
    }


    file.write(str.toUtf8());
    file.flush();
    file.close();
}

int **myConf::get_maze()
{
    return _mazeTmp;
}

myConf& myConf::Instance()
{
    static myConf ins;
    return ins;
}
