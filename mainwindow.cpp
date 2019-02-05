#include "ui_mainwindow.h"
#include "mainwindow.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>

#include <QtWidgets>

#if defined(_WIN32)
#define SIZE_WID 24
#else
#define SIZE_WID 32
#endif

MainWindow::MainWindow(Indexer* indx_ref, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    indx_ptr_ = indx_ref;
    ui->setupUi(this);

    QWidget* wgt = new QWidget(this);
    setCentralWidget (wgt);

    ptb = new QToolBar(this);
    s_line = new QLineEdit(this);
    s_line->setMaximumSize (200, SIZE_WID);
    s_line->setPlaceholderText ("Search...");

    s_combo = new QComboBox(this);
    s_combo->setMaximumSize (200, SIZE_WID);
    s_combo->addItems (S_TYPE);

    start_action = ptb->addAction(QPixmap(":/buttons/resources/start.png"), "Start indexing", this, SLOT(onActionStart()));
    pause_action = ptb->addAction(QPixmap(":/buttons/resources/pause.png"), "Pause indexing", this, SLOT(onActionPause()));
    stop_action = ptb->addAction(QPixmap(":/buttons/resources/stop.png"), "Stop indexing", this, SLOT(onActionStop()));
    ptb->addSeparator ();
    ptb->addWidget (s_line);
    ptb->addWidget (new QLabel(" by ", this));
    ptb->addWidget (s_combo);
    search_action = ptb->addAction(QPixmap(":/buttons/resources/search.png"), "Search in index", this, SLOT(onActionSearch()));
    ptb->setMovable (false);
    ptb->setIconSize (QSize(SIZE_WID, SIZE_WID));
    addToolBar(Qt::TopToolBarArea, ptb);

    tree_view = new QTreeView(this);
    f_model = new QFileSystemModel(this);
    f_model->setRootPath(QDir::rootPath());
    tree_view->setModel(f_model);

    table_wgt = new QTableWidget(this);
    table_wgt->setColumnCount(5);
    table_wgt->setHorizontalHeaderLabels (S_TYPE << "Path");
    table_wgt->verticalHeader()->setVisible(false);
    table_wgt->setShowGrid(false);
    table_wgt->setWordWrap(false);
    QHeaderView* header = table_wgt->horizontalHeader();
    header->setSectionResizeMode(0, QHeaderView::Stretch);

    h_main_loyout = new QHBoxLayout(this);
    h_main_loyout->addWidget (table_wgt);
    h_main_loyout->addWidget(tree_view);

    SwitchButtons (DEFAULT);

    wgt->setLayout (h_main_loyout);
    setMinimumSize(600, 300);
}

void MainWindow::SwitchButtons(Process proc){
    switch(proc){
    case DEFAULT:
        start_action->setEnabled (true);
        stop_action->setDisabled (true);
        pause_action->setDisabled (true);
        search_action->setEnabled (true);
        break;
    case START:
        start_action->setDisabled (true);
        stop_action->setEnabled (true);
        pause_action->setEnabled (true);
        search_action->setDisabled (true);
        break;
    case STOP:
        start_action->setEnabled (true);
        stop_action->setDisabled (true);
        pause_action->setEnabled (true);
        search_action->setEnabled (true);
        break;
    case PAUSE:
        start_action->setEnabled (true);
        stop_action->setEnabled (true);
        pause_action->setDisabled (true);
        search_action->setDisabled (true);
        break;
    case SEARCH:
        start_action->setDisabled (true);
        stop_action->setDisabled (true);
        pause_action->setDisabled (true);
        search_action->setDisabled (true);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onActionStart(){
    SwitchButtons(START);
    ui->s_bar->showMessage ("Indexing... Please wait...");

    if (indx_ptr_->Check () == PAUSE){
        indx_ptr_->SetState (START);
    }
    else{
        QThread* start_thread = new QThread;
        Controller* contr = new Controller(indx_ptr_);
        contr->moveToThread (start_thread);

        QObject::connect (start_thread, &QThread::started, contr, &Controller::onStartButtonClick);
        QObject::connect (contr, &Controller::finished, this, &MainWindow::ActionsAfterIndexing);
        start_thread->start ();
    }
}

void MainWindow::onActionStop() {
    SwitchButtons(STOP);

    QThread* stop_thread = new QThread;
    Controller* contr = new Controller(indx_ptr_);
    contr->moveToThread (stop_thread);

    QObject::connect(stop_thread, &QThread::started, contr, &Controller::onStopButtonClick);
    QObject::connect(contr, &Controller::finished, this, &MainWindow::ActionsAfterIndexing);

    stop_thread->start ();
}

void MainWindow::onActionPause() {
    SwitchButtons(PAUSE);
    ui->s_bar->showMessage ("Paused...");

    QThread* pause_thread = new QThread;
    Controller* contr = new Controller(indx_ptr_);
    contr->moveToThread (pause_thread);

    QObject::connect(pause_thread, &QThread::started, contr, &Controller::onPauseButtonClick);

    pause_thread->start ();
}

void MainWindow::onActionSearch(){
}

void MainWindow::ActionsAfterIndexing(){
    SwitchButtons(DEFAULT);
    ui->s_bar->showMessage ("Count of dirs: " + QString::number(indx_ptr_->GetDirCount ()) +
                            ",    Count of objects: " + QString::number (indx_ptr_->GetObjectCount ()));
}

void MainWindow::DisplayFileInfo(FileInfo info){

    table_wgt->insertRow(table_wgt->rowCount());
//    table_wgt->setItem(table_wgt->rowCount() - 1, 0, new QTableWidgetItem(QString::fromStdString(info.name)));
//    table_wgt->setItem(table_wgt->rowCount() - 1, 1, new QTableWidgetItem(QString::fromStdString(info.extension)));
//    table_wgt->setItem(table_wgt->rowCount() - 1, 2, new QTableWidgetItem(QString::number(info.size)));
//    table_wgt->setItem(table_wgt->rowCount() - 1, 3, new QTableWidgetItem(QString::number(info.date)));
//    table_wgt->setItem(table_wgt->rowCount() - 1, 4, new QTableWidgetItem(QString::fromStdString(info.path)));
}

