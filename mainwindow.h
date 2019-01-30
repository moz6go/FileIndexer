#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"
#include "searchfiles.h"

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QTableView>
#include <QTreeView>
#include <QHBoxLayout>


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
    SearchFiles* s_ptr_;
    Ui::MainWindow* ui;
    QLabel* sb_info;
    QTableView* table_view;
    QTreeView* tree_view;
    QHBoxLayout* h_main_loyout;

    //threads
    StartThread* start_thread;
    StopThread* stop_thread;

    void SwitchButtons(Process proc);
public:
    MainWindow(SearchFiles* s_ptr, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionStart_triggered();
    void on_actionPause_triggered();
    void on_actionStop_triggered();
    void on_actionSearch_triggered();
    void ActionsAfterIndexing();

};

#endif // MAINWINDOW_H
