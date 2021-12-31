#include "mywidget.h"
#include "ui_mywidget.h"
#include "mylinkstack.h"
#include "mylogin.h"

#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QToolButton>
#include <QMessageBox>

#include <windows.h>

#define  printf(...) qDebug(__VA_ARGS__)
//#define  printf(...)

myWidget::myWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());



    connect(ui->quitBtn, &QPushButton::clicked, [=]{

        outMaze(_outPath);
        killTimer(_tId);
        close();
    });

    connect(ui->setBtn, &QPushButton::clicked, [=]{
        if(!_isChange)
        {
            QMessageBox::warning(this, "警告", "请走完迷宫设置");
        }
        else
        {
            _isChange = false;
            this->hide();
            outMaze(_outPath);
             killTimer(_tId);
            for(int i = 0; i < 8; i++)
            {
                for(int j = 0; j < 11; j++)
                {
                    if(out_maze[i][j] == '#' || out_maze[i][j] == '@')
                    {
                        findButton(i, j, "path.jpg");
                    }
                }
            }

            for(int i = 0; i < 8; i++)
            {
                delete[] out_maze[i];
            }
            delete []out_maze;
            out_maze = nullptr;

//            cout << "ui->setBtn";
            emit enterMaze();
        }
    });

}

myWidget::~myWidget()
{
    if(out_maze)
    {
        for(int i = 0; i < 8; i++)
        {
            delete[] out_maze[i];
        }
        delete []out_maze;
        out_maze = nullptr;
    }

    delete ui;
}

void myWidget::setWall(int**maze)
{

    //设置墙
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            if(maze[i][j]){
//                qDebug() << maze[i][j];
               findButton(i, j, "wall.jpg");
            }
        }
    }

}

void myWidget::setPath()
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            findButton(i, j, "path.jpg");
        }
    }
}

void myWidget::paintEvent(QPaintEvent *event)
{
    //给窗口画背景图
    QPainter p(this);
    QPixmap pixmap(":/image/display_bk.bmp");
    p.drawPixmap(0, 0, this->width(), this->height(), pixmap);
}

void myWidget::timerEvent(QTimerEvent *)
{
    if(_isReady)
    {
         //起点
        findButton(1, 0, "begin.png");
        if(!_qe.isEmpty())
        {
            if(!_qe.front().d)
            {
                out_maze[_qe.front().x ][_qe.front().y] = '#';
                findButton(_qe.front().x, _qe.front().y, "passing.png");

            }else {
                out_maze[_qe.front().x ][_qe.front().y] = '@';
                findButton(_qe.front().x, _qe.front().y, "passed.jfif");
            }
            _qe.removeFirst();
        }else {
//            cout << out_maze[6][9];
            _isChange = true;
            _isReady = false;
            if(out_maze[6][9] == '*')
            {
                QMessageBox::information(this, "Info", "未找到迷宫路径");
                return;
            }
            out_maze[1][0] = '#';
            //终点
            findButton(6, 10, "final.png");
            out_maze[6][9] = out_maze[6][10] = '#';

        }
    }



}

int myWidget::mainMaze(void)
{
    _tId = startTimer(100);
    int**maze = myConf::Instance().get_maze();
    setWall(maze);

    //路径移动辅助数组
    int direction[4][2] = {
        {0,1},
        {1,0},
        {0,-1},
        {-1,0}
    };

    myLinkStack::LinkStack* pTop = nullptr;
    myLinkStack myStack;
    pTop = myStack.InitLkStack();//用来保存路径

    myLinkStack::DataType element;
    element = myStack.create_element(1, 1, -1); //-1保证下一个节点推进是起点方向是0
    pTop = myStack.PushLkStack(pTop, element);//迷宫入口入栈
    int i, j, k;//当前的横坐标，纵坐标以及方向
    int g, h;//潜在的下一个方向

    //保存走过路径
    myLinkStack::DataType flag;
    flag = myStack.create_element(1, 1, 0);
    _qe.push_back(flag);


    while (!myStack.IsEmptyLkMazeStack(pTop)) {
        //获得当前节点的坐标
        i = pTop->data.x;
        j = pTop->data.y;
        k = pTop->data.d+1;
        while (k <= 3) {
            g = i + direction[k][0];
            h = j + direction[k][1];
            if (g == 6 && h == 9 && maze[g][h] == 0) {
//                printf("找到了\n");
                printf("节点位置1是:%d,%d\n", i, j);

                while (!myStack.IsEmptyLkMazeStack(pTop)) {
                    pTop = myStack.PopLkStack(pTop, &element);
                    printf("节点位置2是:%d,%d\n", pTop->data.x, pTop->data.y);

                }
            }

            //判断是否可以前进到下一个节点
            if (maze[g][h] == 0) {
                maze[g][h] = 2;//不要走回头路
                //要将节点路径保留，那么就要入栈
                element = myStack.create_element(g, h, -1);
                pTop = myStack.PushLkStack(pTop, element);

                flag = myStack.create_element(g, h, 0);
                _qe.push_back(flag);
                break;
            }
            k = k + 1;
        }
        //回溯：k大于3说明，所有的当前节点的4个方向都找过，没有通路，所以要退栈，到上一个节点上
        if (k > 3) {
            pTop = myStack.PopLkStack(pTop, &element);//此时element接住上一个在栈中的节点
            flag = element;
            flag.d = 1;
            _qe.push_back(flag);
        }
    }
    myStack.destroyStack(pTop);
//    printf("没有找到通路\n");
     _qe.last().d = 0;

     return 0;
}

void myWidget::readMaze( QString maze)
{
    myConf::Instance().writeConfInfo();
    myConf::Instance().getCfgValue("totalMaze", maze);
}

void myWidget::showWindow(QString outPath)
{
    setPath();
    mainMaze();
    this->show();
    displayMaze();
    _outPath = outPath;
}

void myWidget::outMaze(QString outPath)
{
//    cout << outPath;
    myConf::Instance().writeMazePath((const char**)out_maze, outPath);
}

void myWidget::findButton(int x, int y, QString iconName)
{
    QString str = QString("col%1_%2").arg(x).arg(y);
    QPushButton *button = ui->widget_4->findChild<QPushButton *>(str);
//    QList<QPushButton *> allPButtons = ui->widget_4->findChildren<QPushButton *>();

    QString icon = QString(":/image/%1").arg(iconName);
    button->setIcon(QPixmap(icon));
    button->setAutoDefault(true);

}

void myWidget::displayMaze()
{
   //初始化输出文件的迷宫解的数组
    if(!out_maze)
    {
        out_maze = new char*[8];
        for(int i = 0; i < 8; i++)
        {
            out_maze[i] = new char[11];
        }
    }

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 11; j++)
        {
            out_maze[i][j] = '*';
        }
    }
    //画图开始
    _isReady = true;
}
