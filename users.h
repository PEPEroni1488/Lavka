#ifndef USERS_H
#define USERS_H

#include <QString>
#include <QDataStream>
#include <QMap>


class User
{
public:
    enum Status { Seller, Manadger ,Admin };

    User();
    User(const QString &login, const QString &password, const Status &status);
    const QString &login() const;
    const QString &password() const;
    const Status &status() const;
    const QString statusString() const;

    void setData(const QString &login, const QString &password, const Status &status);
    void setLogin(const QString &login);
    void setPassword(const QString &password);
    void setStatus(const Status &status);
    bool upStatus();
    bool downStatus();
    static QMap<Status, QString> getListStatus();

private:
    QString m_login;
    QString m_password;
    Status m_status;
};

inline QDataStream &operator<< (QDataStream &ost, const User &user)
{
    ost << user.login() << user.password() << user.status();
    return ost;
}

inline QDataStream &operator>> (QDataStream &ist, User &user)
{
    QString login;
    QString password;
    int status;
    ist >> login >> password >> status;
    user.setData(login, password, User::Status(status));

    return ist;
}


#endif // USERS_H


