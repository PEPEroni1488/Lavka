#ifndef PRODUCT_H
#define PRODUCT_H

#include <QString>
#include <QDate>
#include <QTime>
#include "users.h"
#include <QDataStream>
#include <QTextStream>

class Product
{
public:
    Product();
    Product(QString get_number, const QString quan,
           const QString name, const QString provider);
    void setData(QString get_number, const QString quan,
                 const QString name, const QString provider);

    QString get_number() const;
    QString quan() const;
    QString name() const;
    QString provider() const;

    void setNumber(const QString &get_number);
    void setQuantity(const QString &quan);
    void setName(const QString &name);
    void setDProvider(const QString &provider);


private:
    QString my_num;
    QString my_qua;
    QString my_nam;
    QString my_prov;
};

inline QDataStream &operator<< (QDataStream &ost, const Product &product)
{
    ost << product.get_number() << product.quan()  << product.name() << product.provider();
    return ost;
}
inline QDataStream &operator>> (QDataStream &ist, Product &product)
{
    QString number;
    QString quantity;
    QString name;
    QString provider;

    ist >> number >> quantity  >> name >> provider ;
    product.setData(number, quantity, name, provider);
    return ist;
}


#endif // PRODUCT_H
