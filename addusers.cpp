#include "addusers.h"
#include "users.h"
#include "ui_addusers.h"
#include "config.h"
#include <QFile>
#include <QDataStream>


AddUsers::~AddUsers()
{
    delete mUi;
}

const User &AddUsers::getUser() const
{
    return m_user;
}

bool AddUsers::isLoginExists(const QString &login)
{
    QFile file(Config::Usersbin);
    if (file.exists())
    {
        QDataStream ist(&file);
        while (!ist.atEnd())
        {
            User buf_user;
            ist >> buf_user;
            if (buf_user.login() == login)
                return true;
        }
        return false;
    }
    else
        return false;
}

AddUsers::AddUsers(QWidget* parent) :
    QDialog(parent),
    mUi(new Ui::AddUsers)
{
    mUi->setupUi(this);
}

void AddUsers::accept()
{
    const QString login = mUi->L_login->text();
    const QString password = mUi->L_password->text();
    User::Status status = User::getListStatus().key(mUi->L_status->currentText());
    if (login.isEmpty() || password.isEmpty())
    {
        mUi->Error->setText("Необходимо заполнить все поля!");
    }
    else if (isLoginExists(login))
    {
        if (mUi->Error->text().isEmpty())
            mUi->Error->setText("Данное имя пользователя уже существует!");
    }
    else if (login.size() < 6 || login.size() > 20)
    {
        mUi->Error->setText("Имя пользователя должено содержать от 5 до 20 символов!");
    }

    else if (password.size() < 6 || password.size() > 20)
    {
        mUi->Error->setText("Пароль должен содержать от 6 до 20 символов!");
    }

    else
    {
        m_user.setData(login, password, status);
        QDialog::accept();
    }
}
