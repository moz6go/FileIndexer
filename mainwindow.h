#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"

#include <QMainWindow>
#include <QtWidgets>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QTableView>
#include <QTreeView>
#include <QHBoxLayout>

#define S_TYPE QStringList() << "Name" << "Extension" << "Size" << "Date"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    Indexer* indx_ptr_;
    Ui::MainWindow* ui;

    QToolBar* ptb;
    QAction* start_action;
    QAction* pause_action;
    QAction* stop_action;
    QAction* search_action;
    QLineEdit* s_line;
    QComboBox* s_combo;

    QFileSystemModel* f_model;
    QTableWidget* table_wgt;
    QTreeView* tree_view;
    QHBoxLayout* h_main_loyout;

    void SwitchButtons(Process proc);
public:
    MainWindow(Indexer* indx_ref, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onActionStop();
    void onActionPause();
    void onActionStart();
    void onActionSearch();
    void ActionsAfterIndexing();
    void DisplayFileInfo(Indexer::FileInfo info);
};

#endif // MAINWINDOW_H
