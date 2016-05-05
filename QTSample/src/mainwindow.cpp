#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>

#include "bitmapview.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_viewPort(NULL)
    , m_fileMenu(NULL)
    , m_helpMenu(NULL)
    , m_exitAction(NULL)
    , m_aboutQtAction(NULL)
    , m_aboutApp(NULL)

{
    ui->setupUi(this);

    m_openAction = new QAction(tr("&Open"), this);
    m_exitAction = new QAction(tr("E&xit"), this);
    m_aboutQtAction = new QAction(tr("&Aboout Qt"), this);
    m_aboutApp = new QAction(tr("&About..."), this);


    connect(m_openAction, SIGNAL(triggered()), this, SLOT(open()));
    connect(m_exitAction, SIGNAL(triggered()), this, SLOT(closeApp()));
    connect(m_aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(m_aboutApp, SIGNAL(triggered()), this, SLOT(about()));

    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_openAction);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAction);

    m_helpMenu = menuBar()->addMenu(tr("&Help"));
    m_helpMenu->addAction(m_aboutQtAction);
    m_helpMenu->addAction(m_aboutApp);

    m_viewPort = new BitmapView(this);
    setCentralWidget(m_viewPort);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// SLOTS
void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("OpenFile"), "", tr("Text Files (*.txt);;C++ Files (*.cpp *.h)"));

    if(fileName != "")
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("ERROR"), tr("Coulkd not open file"));
            return;
        }
        file.close();
    }
}

void MainWindow::closeApp()
{
    close();
}

void MainWindow::about()
{
    QMessageBox::about(this, "About " + qApp->applicationName() + " version " + qApp->applicationVersion(),
                       "The " + qApp->applicationName() + " is the simple sample to view bitmaps");
}


// METHODS
