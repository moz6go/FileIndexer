#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "searchfiles.h"
#include <iostream>
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
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

    QWidget* wgt = new QWidget(this);
    wgt->setLayout (h_main_loyout);
    setCentralWidget (wgt);

    QObject::connect (&s_indx, SIGNAL(indx_ends(QString)), sb_info, SLOT(setText(QString)));
    QObject::connect (&s_indx, SIGNAL(finished()), this, SLOT(ActionsAfterIndexing()));

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
}

void MainWindow::on_actionStart_triggered()
{
    SwitchButtons(START);
    sb_info->setText("Indexing... Please wait...");
    s_indx.start ();
}

void MainWindow::on_actionPause_triggered() {

}

void MainWindow::on_actionStop_triggered() {

}

void MainWindow::on_actionSearch_triggered() {

}

void MainWindow::ActionsAfterIndexing(){
    SwitchButtons(DEFAULT);
}
