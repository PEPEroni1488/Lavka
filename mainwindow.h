#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include "users.h"
#include <product.h>
#include <QTableWidgetItem>
class InfoUser;

namespace Ui {
class MainWindow;
}
class MainWindow : public QWidget
{
    Q_OBJECT

public:

    explicit MainWindow(User &user, QWidget *parent = nullptr);
    ~MainWindow();

    const QList<Product> &listProduct() const;

public slots:

    void addProduct(Product product);
    void editProduct(int row, Product product);
    void deleteProduct(int row);

private slots:

    void on_infoUser_clicked();
    void on_controlproduct_clicked();
    void on_controlusers_clicked();


signals:
    void changeUser();


private:
    Ui::MainWindow *mUi;
    User &m_user;
    InfoUser *m_infoDialog;
    QList<Product> m_listProduct;
    void loadProducts();

};
#endif // MAINWINDOW_H

