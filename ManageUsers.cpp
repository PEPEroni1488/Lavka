#include "ManageUsers.h"
#include "ui_ManageUsers.h"
#include "config.h"
#include "addusers.h"
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QDebug>

ManageUsers::ManageUsers(QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::ManageUsers)
{
    mUi->setupUi(this);
    QFile file(Config::Usersbin);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream ist(&file);
        int row = 0;
        while (!ist.atEnd()) {
            User user;
            ist >> user;
            m_listUsers.append(user);
            QTableWidgetItem *item_login = new QTableWidgetItem(user.login());
            QTableWidgetItem *item_status = new QTableWidgetItem(user.statusString());

            mUi->TableUsers->insertRow(row);
            mUi->TableUsers->setItem(row, 0, item_login);
            mUi->TableUsers->setItem(row, 1, item_status);
            row++;
        }
    }
}

ManageUsers::~ManageUsers()
{
    delete mUi;
}

void ManageUsers::slotUpDownStatus()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());

    int currentRow = mUi->TableUsers->currentRow();
    if (currentRow != -1)
    {
        const QString login = mUi->TableUsers->item(currentRow, 0)->text();
        const QString status = mUi->TableUsers->item(currentRow, 1)->text();

        if (status == "Администратор" && countAdmins() <= 1)
        {
            QMessageBox::warning(this, windowTitle(), "Не удалось изменить статус пользователя!");
            return;
        }

        QFile file(Config::Usersbin);
        if (file.open(QIODevice::ReadOnly)) {
            QFile write_file("buf_file_users");
            write_file.open(QIODevice::WriteOnly);
            QDataStream read_ist(&file);
            QDataStream write_ist(&write_file);

            while (!read_ist.atEnd())
            {
                User user;
                read_ist >> user;

                if (user.login() == login)
                {
                    if (btn->objectName() == "up")
                    {

                        if (!user.upStatus())
                        {
                            QMessageBox::warning(this, windowTitle(),
                                                 "Данный статус является максимальным.");
                        }
                    }
                    else
                    {
                        if (!user.downStatus())
                        {
                            QMessageBox::warning(this, windowTitle(),
                                                 "Данный статус является минимальным.");
                        }
                    }

                    mUi->TableUsers->item(currentRow, 1)->setText(user.statusString());
                }
                write_ist << user;
            }
            file.close();
            file.remove();
            write_file.close();
            write_file.rename(Config::Usersbin);
        }
    }
    else
    {
        QMessageBox::warning(this, windowTitle(),
                             "Ошибка: не удалось повысить/понизить пользователя!");
    }
}		

void ManageUsers::on_delete_2_clicked()
{
    int currentRow = mUi->TableUsers->currentRow();
    if (currentRow != -1)
    {
        const QString login = mUi->TableUsers->item(currentRow, 0)->text();
        const QString status = mUi->TableUsers->item(currentRow, 1)->text();

        if (status == "Администратор" && countAdmins() <= 1)
        {
            QMessageBox::warning(this, windowTitle(),
                                 "Не удалось изменить статус пользователя!");
            return;
        }
        mUi->TableUsers->removeRow(currentRow);
        QFile file(Config::Usersbin);
        if (file.open(QIODevice::ReadOnly))
        {
            QFile write_file("buf_file_users");
            write_file.open(QIODevice::WriteOnly);
            QDataStream read_ist(&file);
            QDataStream write_ist(&write_file);

            while (!read_ist.atEnd())
            {
                User user;
                read_ist >> user;

                if (user.login() != login)
                {
                    write_ist << user;
                }
            }

            file.close();
            file.remove();
            write_file.close();
            write_file.rename(Config::Usersbin);
        }
    }
}

void ManageUsers::on_add_clicked()
{
    AddUsers dialog(this);
    dialog.setWindowTitle(windowTitle());
    if (dialog.exec() == QDialog::Accepted)
    {
        const User &user = dialog.getUser();
        QFile file(Config::Usersbin);
        file.open(QIODevice::Append);
        QDataStream ost(&file);
        ost << user;
        QTableWidgetItem *item_login = new QTableWidgetItem(user.login());
        QTableWidgetItem *item_status = new QTableWidgetItem(user.statusString());

        int row = mUi->TableUsers->rowCount();

        mUi->TableUsers->insertRow(row);
        mUi->TableUsers->setItem(row, 0, item_login);
        mUi->TableUsers->setItem(row, 1, item_status);
    }
}

int ManageUsers::countAdmins() const
{
    QFile file(Config::Usersbin);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream ist(&file);

        int count = 0;
        while (!ist.atEnd()) {
            User user;
            ist >> user;
            if (user.status() == User::Admin) count++;
        }
        return count;
    }
    else return 0;
}



