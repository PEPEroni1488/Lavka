#include "ManageProduct.h"
#include "ui_ManageProduct.h"
#include "config.h"
#include <addproduct.h>
#include <QMessageBox>
#include <QFile>
#include <QDataStream>
#include <mainwindow.h>

ManageProduct::ManageProduct(const QList<Product> &listProduct, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::ManageProduct),
    m_listProduct(listProduct)
{
    mUi->setupUi(this);

    int row = 0;
    foreach (const Product &product, m_listProduct)
    {
        QTableWidgetItem *item_number = new QTableWidgetItem(product.get_number());
        QTableWidgetItem *item_names = new QTableWidgetItem(product.name());
        QTableWidgetItem *item_provid= new QTableWidgetItem(product.provider());
        QTableWidgetItem *item_quant = new QTableWidgetItem(product.quan());

        mUi->TableProduct->insertRow(row);
        mUi->TableProduct->setItem(row, 0, item_number);
        mUi->TableProduct->setItem(row, 1, item_names );
        mUi->TableProduct->setItem(row, 2, item_provid );
        mUi->TableProduct->setItem(row, 3,  item_quant);
        row++;
    }
}

ManageProduct::~ManageProduct()
{
    delete mUi;
}

void ManageProduct::on_lineFind_textChanged(const QString &text)
{
    QStringList listStr = text.split(" ");
    listStr.removeAll(QString());
    for (int i = 0; i < m_listProduct.size(); i++)
    {
        mUi->TableProduct->showRow(i);
    }
    int row = 0;
    foreach (const Product &product, m_listProduct)
    {
        int count = 0;
        foreach (const QString &str, listStr)
        {
            if (product.get_number().contains(str) ||
                product.name().contains(str))
            {
                count++;
            }
        }
        if (count != listStr.size())
        {
            mUi->TableProduct->hideRow(row);
        }
        row++;
    }
}

void ManageProduct::on_add_clicked()
{
    Product product;
    AddProduct dialog(&product, m_listProduct, AddProduct::Create, this);
    dialog.setWindowTitle(windowTitle());
    if (dialog.exec() == QDialog::Accepted)
    {
        emit addProduct(product);
        QTableWidgetItem *item_number = new QTableWidgetItem(product.get_number());
        QTableWidgetItem *item_names = new QTableWidgetItem(product.name());
        QTableWidgetItem *item_provid= new QTableWidgetItem(product.provider());
        QTableWidgetItem *item_quant = new QTableWidgetItem(product.quan());
        int row = mUi->TableProduct->rowCount();

        mUi->TableProduct->insertRow(row);
        mUi->TableProduct->setItem(row, 0, item_number);
        mUi->TableProduct->setItem(row, 1, item_names );
        mUi->TableProduct->setItem(row, 2, item_provid );
        mUi->TableProduct->setItem(row, 3, item_quant);
    }
}

void ManageProduct::on_del_clicked()
{
    int currentRow = mUi->TableProduct->currentRow();
    if (currentRow != -1)
    {
        emit deleteProduct(currentRow);
        mUi->TableProduct->removeRow(currentRow);
    }
    else
    {
        QMessageBox::warning(this, windowTitle(), "Не выбран ни один товар!");
    }
}

void ManageProduct::on_edit_clicked()
{
    int currentRow = mUi->TableProduct->currentRow();
    if (currentRow != -1)
    {
        Product product = m_listProduct[currentRow];
        AddProduct dialog(&product, m_listProduct, AddProduct::Edit, this);
        dialog.setWindowTitle(windowTitle());
        if (dialog.exec() == QDialog::Accepted)
        {
            emit editProduct(currentRow, product);
            mUi->TableProduct->item(currentRow, 0)->setText(product.get_number());
            mUi->TableProduct->item(currentRow, 1)->setText(product.name());
            mUi->TableProduct->item(currentRow, 2)->setText(product.provider());
            mUi->TableProduct->item(currentRow, 3)->setText(product.quan());

        }
    }
}
