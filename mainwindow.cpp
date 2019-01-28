#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "searchfiles.h"
#include <iostream>
#include <ctime>
#include <QThread>

class StartThread: public QThread {
    void run() {

    }
};


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    search_line = new QLineEdit(this);
    c_dir_label = new QLabel(this);
    c_obj_label = new QLabel(this);

    ui->toolBar->addWidget (search_line);
    ui->actionStop->setDisabled (true);
    ui->actionPause->setDisabled (true);
    ui->statusBar->addWidget (c_dir_label);
    ui->statusBar->addWidget (c_obj_label);
    //QWidget* wgt = new QWidget(this);
    //wgt->setLayout (ui->h_main_loyout);
    setCentralWidget (ui->t_edit);

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_actionStart_triggered()
{
    //ui->t_edit->setText("Search in progress... Please wait...");
    char path[260] = "/home";
    std::ofstream fout;
    fout.open ("files.txt");
    SearchFiles s(path);
    s.GetFilesListMapWrite (fout, path);
    fout.close ();

    ui->t_edit->setText("");

    c_dir_label->setText ("Count of dirs: " + QString::number(s.GetDirCount ()));
    c_obj_label->setText ("Count of objects: " + QString::number (s.GetObjectCount ()));

}
