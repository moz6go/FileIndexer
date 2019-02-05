#include "xmlreader.h"
#include "mainwindow.h"
#include <QtDebug>
#include <QApplication>
#include <iostream>
#include <locale>

using namespace std;

int main(int argc, char *argv[])
{
#if defined(_WIN32)
    std::locale::global(std::locale(""));
#endif
    qRegisterMetaType<FileInfo>("FileInfo"); // for QObject::connect new syntax
    QApplication a(argc, argv);
    Indexer indx;
    indx.ReadIndex ();
    MainWindow w(&indx);
    w.show();

    return a.exec();
}
