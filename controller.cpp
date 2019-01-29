#include "controller.h"

void StartThread::run() {
    char path[260] = "";
    std::ofstream fout;
    fout.open ("files.txt");
    SearchFiles s;
    s.Index (fout, path);
    fout.close ();

    emit indx_ends("Count of dirs: " + QString::number(s.GetDirCount ()) +
                   "\tCount of objects: " + QString::number (s.GetObjectCount ()));
}

void StopThread::run() {

}
