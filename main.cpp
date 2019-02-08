#include "mainwindow.h"

int main(int argc, char *argv[])
{
#if defined(_WIN32)
    std::locale::global(std::locale(""));
#endif
    qRegisterMetaType<FileInfo>("FileInfo"); // for QObject::connect new syntax
    QApplication a(argc, argv);
    Indexer indx;
    IndexReader reader;
    MainWindow w(&indx, &reader);
    w.show();

    return a.exec();
}
