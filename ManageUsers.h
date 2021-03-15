#ifndef MANAGEUSERS_H
#define MANAGEUSERS_H

#include <QDialog>
#include "users.h"

namespace Ui {
class ManageUsers;
}
class ManageUsers : public QDialog
{
    Q_OBJECT

public:

    explicit ManageUsers(QWidget *parent = nullptr);
    ~ManageUsers();

private slots:
    void on_delete_2_clicked();

    void on_add_clicked();
    void slotUpDownStatus();

private:
    Ui::ManageUsers *mUi;
    QList<User> m_listUsers;
    int countAdmins() const;
};
#endif // MANAGEUSERS_H
