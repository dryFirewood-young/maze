#ifndef MYLOGIN_H
#define MYLOGIN_H

#include <QDialog>
#include "mywidget.h"

namespace Ui {
class myLogin;
}

class myLogin : public QDialog
{
    Q_OBJECT

public:
    explicit myLogin(QWidget *parent = nullptr);
    ~myLogin();

signals:

private:
    Ui::myLogin *ui;
    myWidget* _wg;
};

#endif // MYLOGIN_H
