#include "controller.h"

void StartThread::run() {
#if defined(_WIN32)
    std::wofstream fout;
    fout.open("files.txt");
//    DWORD dr = GetLogicalDrives();
//    for (int x = 0; x <= 'Z'-'A'; x++)
//    {
//        int n = ((dr >> x) & 1);
//        if (n)
//        {
//            std::wstring disc;
//            disc.push_back((wchar_t)('A' + x));
//            disc += L":\\";
            SearchFiles s;
            s.Index(fout, L"D:\\"/*disc*/);
//        }
//    }
    fout.close();
#else
    char path[260] = "";
    std::ofstream fout;
    fout.open ("files.txt");
    SearchFiles s;
    s.Index (fout, path);
    fout.close ();
#endif
    emit indx_ends("Count of dirs: " + QString::number(s.GetDirCount ()) +
                   "\tCount of objects: " + QString::number (s.GetObjectCount ()));

}

void StopThread::run() {

}
