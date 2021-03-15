#ifndef MANAGEPRODUCT_H
#define MANAGEPRODUCT_H

#include <QDialog>
#include "product.h"

namespace Ui {
class ManageProduct;
}
class ManageProduct : public QDialog
{
    Q_OBJECT

public:
    explicit ManageProduct(const QList<Product> &listProduct, QWidget *parent = nullptr);
    ~ManageProduct();

private slots:
    void on_lineFind_textChanged(const QString &arg1);
    void on_add_clicked();
    void on_del_clicked();
    void on_edit_clicked();

private:
    Ui::ManageProduct *mUi;

    const QList<Product> &m_listProduct;

signals:    
    void addProduct(Product);
    void editProduct(int, Product);
    void deleteProduct(int);

};



#endif // MANAGEPRODUCT_H


