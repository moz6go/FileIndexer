#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QtWidgets>

MainWindow::MainWindow(SearchFiles* s_ptr, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    s_ptr_ = s_ptr;
    ui->setupUi(this);
    sb_info = new QLabel(this);
    table_view = new QTableView(this);
    tree_view = new QTreeView(this);
    h_main_loyout = new QHBoxLayout(this);
    h_main_loyout->addWidget (table_view);
    h_main_loyout->addWidget (tree_view);
    sb_info->setFrameStyle (QFrame::StyledPanel & QFrame::Plain);
    ui->statusBar->addWidget (sb_info);
    SwitchButtons (DEFAULT);

    start_thread = new StartThread(s_ptr_);
    stop_thread = new StopThread(s_ptr_);

    QWidget* wgt = new QWidget(this);
    wgt->setLayout (h_main_loyout);
    setCentralWidget (wgt);

    QObject::connect (start_thread, SIGNAL(finished()), this, SLOT(ActionsAfterIndexing()));
}

void MainWindow::SwitchButtons(Process proc){
    switch(proc){
    case DEFAULT:
        ui->actionStart->setEnabled (true);
        ui->actionStop->setDisabled (true);
        ui->actionPause->setDisabled (true);
        ui->actionSearch->setEnabled (true);
        break;
    case START:
        ui->actionStart->setDisabled (true);
        ui->actionStop->setEnabled (true);
        ui->actionPause->setEnabled (true);
        ui->actionSearch->setDisabled (true);
        break;
    case STOP:
        ui->actionStart->setEnabled (true);
        ui->actionStop->setDisabled (true);
        ui->actionPause->setEnabled (true);
        ui->actionSearch->setEnabled (true);
        break;
    case PAUSE:
        ui->actionStart->setEnabled (true);
        ui->actionStop->setEnabled (true);
        ui->actionPause->setDisabled (true);
        ui->actionSearch->setDisabled (true);
        break;
    case SEARCH:
        ui->actionStart->setDisabled (true);
        ui->actionStop->setDisabled (true);
        ui->actionPause->setDisabled (true);
        ui->actionSearch->setDisabled (true);
    }
}

MainWindow::~MainWindow() {
    delete ui;
    delete start_thread;
}

void MainWindow::on_actionStart_triggered()
{
    SwitchButtons(START);
    sb_info->setText("Indexing... Please wait...");
    start_thread->start ();
}

void MainWindow::on_actionPause_triggered() {

}

void MainWindow::on_actionStop_triggered() {
    SwitchButtons(STOP);
    sb_info->setText("Indexing was stopped!");
    stop_thread->start ();
}

void MainWindow::on_actionSearch_triggered() {

}

void MainWindow::ActionsAfterIndexing(){
    SwitchButtons(DEFAULT);
    sb_info->setText ("Count of dirs: " + QString::number(s_ptr_->GetDirCount ()) +
                      "\tCount of objects: " + QString::number (s_ptr_->GetObjectCount ()));
}
