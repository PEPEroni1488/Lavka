#include "config.h"
#include "product.h"
#include "addproduct.h"
#include "ui_addproduct.h"
#include <QComboBox>

AddProduct::AddProduct(Product *product, const QList<Product> &listProduct, Type type, QWidget *parent) :
    QDialog(parent),
    mUi(new Ui::AddProduct),
    my_pro(product),
    m_listproduct(listProduct)
{
    mUi->setupUi(this);
    m_startNumberProduct = product->get_number();
    if (type == Edit)
    {
        mUi->label_7->setText("Редактирование");
        mUi->Number->setText(my_pro->get_number());
        mUi->kolvo->setText(my_pro->quan());
        mUi->nazv->setText(my_pro->name());
        mUi->post->setText(my_pro->provider());
    }

    else
    {
        mUi->label_7->setText("Добавление");
    }

}


AddProduct::~AddProduct()
{
    delete mUi;
}

void AddProduct::accept()
{
    mUi->error->clear();

    QString number = mUi->Number->text();
    QString quan = mUi->kolvo->text();
    QString name = mUi->nazv->text();
    QString provide = mUi->post->text();

    if (number.isEmpty() ||
        provide.isEmpty()||
        name.isEmpty())
    {
        mUi->error->setText("Заполните все поля!");
    }
    else
    {
        my_pro->setData(number, quan, name, provide);
        QDialog::accept();
    }
}


