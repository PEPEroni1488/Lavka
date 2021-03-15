#include <QFile>
#include <QDataStream>
#include <QDebug>
#include <kabinet.h>
#include <ManageProduct.h>
#include <product.h>
#include <ManageUsers.h>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "config.h"

MainWindow::MainWindow(User &user, QWidget *parent) :
    QWidget(parent),
    mUi(new Ui::MainWindow),
    m_user(user)
{
    mUi->setupUi(this);
    m_infoDialog = new InfoUser(m_user, this);
    m_infoDialog->setWindowTitle(Config::nameApplication);

    if (m_user.status() == User::Manadger)
        mUi->controlusers->hide();
    if (m_user.status() == User::Seller)
    {
        mUi->controlproduct->hide();
        mUi->controlusers->hide();
    }

    loadProducts();
    mUi->Board_product->sortByColumn(3,Qt::AscendingOrder);
}

MainWindow::~MainWindow()
{
    delete mUi;
    delete m_infoDialog;
    delete &m_user;
}

void MainWindow::on_controlproduct_clicked()
{    
    const QList<Product> &listProduct = qobject_cast<MainWindow*>(this)->listProduct();
    ManageProduct dialog(listProduct, this);
    dialog.setWindowTitle(windowTitle());
        connect(&dialog, SIGNAL(addProduct(Product)),
                this, SLOT(addProduct(Product)));

        connect(&dialog, SIGNAL(editProduct(int, Product)),
                this, SLOT(editProduct(int, Product)));

        connect(&dialog, SIGNAL(deleteProduct(int)),
                this, SLOT(deleteProduct(int)));
    dialog.exec();
    mUi->Board_product->sortByColumn(3,Qt::AscendingOrder);
}

void MainWindow::on_controlusers_clicked()
{
    ManageUsers dialog(this);
    dialog.setWindowTitle(windowTitle());
    dialog.show();
    dialog.exec();
}

void MainWindow::on_infoUser_clicked()
{
    if (m_infoDialog->exec() == QDialog::Accepted)
         emit changeUser();
}

void MainWindow::addProduct(Product product)
{
    m_listProduct.append(product);
    QFile file(Config::Productbin);
    file.open(QIODevice::Append);
    QDataStream ost(&file);
    ost << product;
    QTableWidgetItem *it_numb = new QTableWidgetItem(product.get_number());
    QTableWidgetItem *it_quant = new QTableWidgetItem(product.quan());
    QTableWidgetItem *it_names = new QTableWidgetItem(product.name());
    QTableWidgetItem *it_provid= new QTableWidgetItem(product.provider());
    int row = mUi->Board_product->rowCount();
    mUi->Board_product->insertRow(row);
    mUi->Board_product->setItem(row, 0, it_numb);
    mUi->Board_product->setItem(row, 1, it_names);
    mUi->Board_product->setItem(row, 2, it_provid);
    mUi->Board_product->setItem(row, 3, it_quant );
}

void MainWindow::editProduct(int row, Product product)
{
    m_listProduct[row] = product;
    QFile file(Config::Productbin);
    if (file.open(QIODevice::ReadOnly))
    {
        QFile write_file("product_file");
        write_file.open(QIODevice::WriteOnly);
        QDataStream read_ist(&file);
        QDataStream write_ist(&write_file);

        int countSeats = 0;
        while (!read_ist.atEnd())
        {
            Product bProduct;
            read_ist >> bProduct;

            if (countSeats++ == row)
            {
                bProduct = product;
            }

            write_ist << bProduct;
        }
        file.close();
        file.remove();
        write_file.close();
        write_file.rename(Config::Productbin);
    }
    mUi->Board_product->item(row, 0)->setText(product.get_number());
    mUi->Board_product->item(row, 1)->setText(product.name());
    mUi->Board_product->item(row, 2)->setText(product.provider());
    mUi->Board_product->item(row, 3)->setText(product.quan());
}

void MainWindow::deleteProduct(int row)
{
    m_listProduct.removeAt(row);
    QFile file(Config::Productbin);
    if (file.open(QIODevice::ReadOnly))
    {
        QFile write_file("product_file");
        write_file.open(QIODevice::WriteOnly);
        QDataStream read_ist(&file);
        QDataStream write_ist(&write_file);

        int countReads = 0;
        while (!read_ist.atEnd())
        {
            Product bProduct;
            read_ist >> bProduct;
            if (countReads++ != row)
            {
                write_ist << bProduct;
            }
        }
        file.close();
        file.remove();
        write_file.close();
        write_file.rename(Config::Productbin);
    }
    mUi->Board_product->removeRow(row);
}

const QList<Product> &MainWindow::listProduct() const
{
    return m_listProduct;
}

void MainWindow::loadProducts()
{
    m_listProduct.clear();
    QFile file(Config::Productbin);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream ist(&file);
        while (!ist.atEnd()) {
            Product product;
            ist >> product;
            m_listProduct.append(product);
        }
    }

    int row = 0;
    foreach (const Product &product, m_listProduct) {

        QTableWidgetItem *it_num = new QTableWidgetItem(product.get_number());
        QTableWidgetItem *it_names  = new QTableWidgetItem(product.name());
        QTableWidgetItem *it_provid  = new QTableWidgetItem(product.provider());
        QTableWidgetItem *it_quant= new QTableWidgetItem(product.quan());

        mUi->Board_product->insertRow(row);
        mUi->Board_product->setItem(row, 0, it_num);
        mUi->Board_product->setItem(row, 1, it_names );
        mUi->Board_product->setItem(row, 2, it_provid );
        mUi->Board_product->setItem(row, 3, it_quant);
        row++;
    }
}
