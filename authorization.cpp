#include "authorization.h"
#include "ui_authorization.h"
#include "users.h"
#include "config.h"
#include <QFile>
#include <QDataStream>

SignIn::SignIn(QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::SignIn)
{
    mUi->setupUi(this);
    connect(mUi->registr, SIGNAL(clicked()),
            this, SIGNAL(openRegistration()));
}

SignIn::~SignIn()
{
    delete mUi;
}

User *SignIn::checkUser(const QString &login, const QString &password)
{
    QFile file(Config::Usersbin);
    if (file.exists())
    {
        User *user = nullptr;
        if (!file.open(QIODevice::ReadOnly))
        {
            mUi->labelError->setText("Ошибка: открытие файла невозможно!");
            return nullptr;
        }
        QDataStream ist(&file);

        while (!ist.atEnd())
        {
            User users_buf;
            ist >> users_buf;
            if (users_buf.login() == login && users_buf.password() == password)
            {

                user = new User(users_buf);
                return user;
            }
        }

        return user;
    }
    else
        return nullptr;
}

void SignIn::on_sign_clicked()
{
    mUi->labelError->clear();
    const QString login = mUi->Llog->text();
    const QString password = mUi->Lpass->text();
    const int minimal_Password_Length = 6;
    const int maximum_Password_Length = 20;
    if (login.isEmpty() || password.isEmpty())
    {
        mUi->labelError->setText("Заполните все поля!");
    }
    else if (login.size() < minimal_Password_Length || login.size() > maximum_Password_Length)
    {
        mUi->labelError->setText("Имя пользователя должено содержать от 6 до 20 символов!");
    }
    else if (password.size() < minimal_Password_Length || password.size() > maximum_Password_Length)
    {
        mUi->labelError->setText("Пароль должен содержать от 6 до 20 символов!");
    }
    else
        {
        User *user = checkUser(login, password);

        if (user == nullptr)
        {
            mUi->labelError->setText("Неправильный логин или пароль!");
        }
        else
        {
            emit succesfulEntry(user);
        }
    }
}








