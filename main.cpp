#include "mainwindow.h"

#include <QApplication>
#include <iostream>
#include <locale>

using namespace std;

int main(int argc, char *argv[])
{
#if defined(_WIN32)
    std::locale::global(std::locale(""));
#endif
    QApplication a(argc, argv);
    SearchFiles s;
    MainWindow w(&s);
    w.show();

    return a.exec();
}
