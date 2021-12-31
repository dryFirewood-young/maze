#include "mylogin.h"
#include "ui_mylogin.h"
#include "mywidget.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

#define DEFAFILE        "conf/maze.out"     // 配置文件

myLogin::myLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myLogin)
{
    ui->setupUi(this);
    _wg = new myWidget;


    //点击按钮 选取文件
     ui->lineEdit->setText(DEFAFILE);
     QString _path = DEFAFILE;
    connect(ui->pushButton_path, &QPushButton::clicked, [&](){
       _path = QFileDialog::getOpenFileName(this, "打开文件", "./");
       if(_path.isEmpty()){
            QMessageBox::warning(this, "警告", "打开失败");
       }
       else{
           //将路径放入到lineEdit
           ui->lineEdit->setText(_path);
       }
    });

    //迷宫图
    _wg->readMaze(QString("maze1"));
    void(QComboBox::*cbxsingal)(const QString &text)
            = &QComboBox::currentIndexChanged;
    connect(ui->comboBox, cbxsingal, [=] (const QString &text) mutable{
         _wg->readMaze(QString("maze%1").arg(text));
    });

    connect(_wg, &myWidget::enterMaze, [=]{
//        ui->comboBox->setEditText("1");
        ui->comboBox->setCurrentText("1");
        _wg->readMaze(QString("maze1"));
//        cout << "_wg, &myWidget::enterMaze";
        this->show();
    });

    connect(ui->pushButton_quit, &QPushButton::clicked,[=]{
        //程序结束
        //清理。。。
        close();
    });


    connect(ui->pushButton_ok, &QPushButton::clicked,[=]()mutable{
        //进入迷宫
        this->hide();
        _path = ui->lineEdit->text();
        cout << _path;
        _wg->showWindow(_path);
    });
}



myLogin::~myLogin()
{
    if(_wg)
        delete _wg;
    delete ui;
}
