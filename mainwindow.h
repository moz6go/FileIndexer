#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    Indexer* indx_ptr_;
    IndexReader* reader_ptr_;
    SearchType type_;
    Ui::MainWindow* ui;

    QToolBar* ptb_;
    QAction* start_action_;
    QAction* pause_action_;
    QAction* stop_action_;
    QAction* search_action_;
    QAction* s_line_action_;
    QAction* s_date_action_;
    QAction* stacked_wgt_action_;
    QStackedWidget* stacked_wgt_;
    QLineEdit* s_line_;
    QDateEdit* s_date_;
    QComboBox* s_combo_;
    QFileSystemModel* f_model_;
    QTableWidget* table_wgt_;
    QHeaderView* header_;
    QTreeView* tree_view_;
    QSplitter* spliter_;
    QHBoxLayout* h_main_loyout_;

    void BuildToolbar();
    void DefaultTableInit();
    void DefaultTreeInit();
    void InitReadIndex();
    void SwitchButtons(Condition proc);
    void SearchMode();
public:
    MainWindow(Indexer* indx_ref, IndexReader* reader_ptr, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onActionStop();
    void onActionPause();
    void onActionStart();
    void onActionSearch();
    void ActionsAfterIndexing();
    void ActionsAfterSearch(unsigned count);
    void ActionsAfterIndexRead(QString msg);
    void DisplayFileInfo(FileInfo info);
    void setSearchType(QString type);
    void ShowDir(QTableWidgetItem* item);
};

#endif // MAINWINDOW_H
