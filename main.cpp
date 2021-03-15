#include "mainwidjet.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget g;
    g.resize(400, 400);
    g.show();
    return a.exec();
}
