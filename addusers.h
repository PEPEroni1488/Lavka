#ifndef ADDUSERS_H
#define ADDUSERS_H

#include <QDialog>
#include "users.h"

namespace Ui {
class AddUsers;
}

class AddUsers : public QDialog
{
    Q_OBJECT
public:
    explicit AddUsers(QWidget *parent = nullptr);
    ~AddUsers();
    const User &getUser() const;

private:
    Ui::AddUsers *mUi;
    User m_user;

public slots:
    void accept();
    bool isLoginExists(const QString &login);
};

#endif // ADDUSERS_H
