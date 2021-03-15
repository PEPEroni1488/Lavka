#include "product.h"

Product::Product(QString number, const QString quantity,
    const QString names, const QString provid)
{
    setData(number, quantity, names, provid);
}

void Product::setData(QString number, const QString quan,
    const QString name, const QString provider)
{
    my_num = number;
    my_qua = quan;
    my_nam = name;
    my_prov = provider;
}

Product::Product()
{
     my_num = "";
     my_nam = "";
}

void Product::setNumber(const QString &number)
{
    my_num = number;
}


QString Product::quan() const
{
    return my_qua;
}

void Product::setName(const QString &name)
{
    my_nam = name;
}

QString Product::get_number() const
{
    return my_num;
}

void Product::setQuantity(const QString &quan)
{
    my_qua = quan;
}

QString Product::provider() const
{
    return my_prov;
}

void Product::setDProvider(const QString &provider)
{
    my_prov = provider;
}

QString Product::name() const
{
    return my_nam;
}
