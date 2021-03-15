#include "registration.h"
#include "ui_registration.h"
#include "users.h"
#include "config.h"
#include <QFile>
#include <QDataStream>

void SignUp::on_accept_clicked()
{
    mUi->label_error->clear();
    const int minimal_Password_Length = 6;
    const int maximum_Password_Length = 20;
    const QString login = mUi->log->text();
    const QString password = mUi->pass->text();
    const QString repeatPassword = mUi->reppass->text();
    if (login.isEmpty() || password.isEmpty() || repeatPassword.isEmpty())
    {
        mUi->label_error->setText("Заполните все поля");
    }
    else if (isLoginExists(login))
    {
        if (mUi->label_error->text().isEmpty())
            mUi->label_error->setText("Данное имя пользователя занято!");
    }
    else if (login.size() < minimal_Password_Length || login.size() > maximum_Password_Length)
    {
        mUi->label_error->setText("Имя пользователя должено содержать от 6 до 20 символов!");
    }
    else if (password.size() < minimal_Password_Length || password.size() > maximum_Password_Length)
    {
        mUi->label_error->setText("Пароль должен содержать от 6 до 20 символов!");
    }
    else if (password != repeatPassword)
    {
        mUi->label_error->setText("Пароли не совпадают!");
    }
    else
    {
        User user(login,
                  password,
                  m_typeReg == Admin ? User::Admin : User::Seller);

        QFile file(Config::Usersbin);
        file.open(QIODevice::Append);
        QDataStream ost(&file);
        ost << user;
        emit openAuthorization();
    }
}

SignUp::SignUp(TypeRegistration typeReg, QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::SignUp)
{
    mUi->setupUi(this);
    if (typeReg == Admin)
    {
      mUi->label->setText("Регистрация администратора");
      mUi->auth->hide();
    }
    m_typeReg = typeReg;
    connect(mUi->auth, SIGNAL(clicked()),
           this, SIGNAL(openAuthorization()));
}

SignUp::~SignUp()
{
    delete mUi;
}

bool SignUp::isLoginExists(const QString &login)
{
    QFile file(Config::Usersbin);
    if (file.exists())
    {
        QDataStream ist(&file);
        while (!ist.atEnd())
        {
            User users_buf;
            ist >> users_buf;
            if (users_buf.login() == login)
                return true;
        }

        return false;
    }
    else
        return false;
}






