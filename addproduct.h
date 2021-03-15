#ifndef ADDPRODUCT_H
#define ADDPRODUCT_H

#include <QDialog>

class Product;

namespace Ui {
class AddProduct;
}

class AddProduct : public QDialog
{
    Q_OBJECT

public:

    enum Type { Create, Edit };
    explicit AddProduct(Product *product, const QList<Product> &listProduct, Type type, QWidget *parent = nullptr);
    ~AddProduct();

private:
    Ui::AddProduct *mUi;
    QString m_startNumberProduct;
    Product *my_pro;
    const QList<Product> &m_listproduct;

public slots:
    void accept();
private slots:

};

#endif // ADDPRODUCT_H

