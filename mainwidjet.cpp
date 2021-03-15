#include <registration.h>
#include <authorization.h>
#include <QFile>
#include <QVBoxLayout>
#include <QDebug>
#include "users.h"
#include "mainwidjet.h"
#include "config.h"
#include "mainwindow.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
      m_currentWidget(nullptr)
{
    setWindowTitle(Config::nameApplication);

    if (!QFile(Config::Usersbin).exists())
    {
        m_currentWidget = new SignUp(SignUp::Admin, this);
        connect(m_currentWidget, SIGNAL(openAuthorization()),
                this, SLOT(Authorization()));
    }
    else
    {
        m_currentWidget = new SignIn(this);
        connect(m_currentWidget, SIGNAL(openRegistration()),
                this, SLOT(Registration()));
        connect(m_currentWidget, SIGNAL(succesfulEntry(User*)),
                this, SLOT(slotMainWindow(User*)));
    }

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setMargin(0);
    layout->addWidget(m_currentWidget);
    setLayout(layout);
}


MainWidget::~MainWidget()
{
    delete m_currentWidget;
}

void MainWidget::Authorization()
{
    delete m_currentWidget;
    m_currentWidget = new SignIn(this);
    connect(m_currentWidget, SIGNAL(openRegistration()),
            this, SLOT(Registration()));
    connect(m_currentWidget, SIGNAL(succesfulEntry(User*)),
            this, SLOT(slotMainWindow(User*)));

    layout()->addWidget(m_currentWidget);
}

void MainWidget::Registration()
{
    delete m_currentWidget;
    m_currentWidget = new SignUp(SignUp::Passenger, this);
    connect(m_currentWidget, SIGNAL(openAuthorization()),
            this, SLOT(Authorization()));
    layout()->addWidget(m_currentWidget);
}

void MainWidget::slotMainWindow(User *user)
{
    delete m_currentWidget;
    m_currentWidget = new MainWindow(*user, this);
    this->resize(400, 400);
    connect(m_currentWidget, SIGNAL(changeUser()),
            this, SLOT(Authorization()));
    layout()->addWidget(m_currentWidget);
}
