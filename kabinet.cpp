#include "kabinet.h"
#include "ui_kabinet.h"
#include "users.h"
#include "mainwindow.h"

InfoUser::InfoUser(const User &user, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::InfoUser)
{
    mUi->setupUi(this);
    mUi->Llogin->setText(user.login());
    QString pass = "";

    for (int i = 0; i < user.password().size(); i++)
    {
        pass += '*';
    }

    mUi->LPassword->setText(pass);
    mUi->Lstatus->setText(user.statusString());
}

InfoUser::~InfoUser()
{
    delete mUi;
}
