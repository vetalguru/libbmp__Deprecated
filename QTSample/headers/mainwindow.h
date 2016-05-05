#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QTextEdit>
#include <QMenu>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void open();
    void about();
    void closeApp();

private:
    Ui::MainWindow *ui;

    QWidget *m_viewPort;

    QMenu   *m_fileMenu;
    QAction *m_openAction;
    QAction *m_exitAction;

    QMenu *m_helpMenu;
    QAction *m_aboutQtAction;
    QAction *m_aboutApp;

};

#endif // MAINWINDOW_H
