#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QTableView>
#include <QTreeView>
#include <QHBoxLayout>
#include "controller.h"

enum Process {
    DEFAULT = 1,
    START,
    STOP,
    PAUSE,
    SEARCH
};

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow {
    Q_OBJECT
    Ui::MainWindow* ui;
    QLabel* sb_info;
    QTableView* table_view;
    QTreeView* tree_view;
    QHBoxLayout* h_main_loyout;

    //threads
    StartThread s_indx;
public:
    explicit MainWindow(QWidget *parent = 0);
    void SwitchButtons(Process proc);
    ~MainWindow();

private slots:
    void on_actionStart_triggered();
    void on_actionPause_triggered();
    void ActionsAfterIndexing();

    void on_actionStop_triggered();
    void on_actionSearch_triggered();
};

#endif // MAINWINDOW_H
