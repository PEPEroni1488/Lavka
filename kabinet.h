#ifndef LK_H
#define LK_H
#include <QDialog>

class User;

namespace Ui {
class InfoUser;
}
class InfoUser : public QDialog
{
    Q_OBJECT

public:
     explicit InfoUser(const User &user, QWidget *parent = nullptr);
    ~InfoUser();

private slots:

private:
    Ui::InfoUser *mUi;
};
#endif // LK_H
