#include "controller.h"

StartThread::StartThread(SearchFiles* ptr): QThread(), s_ptr_(ptr) {}

void StartThread::run() {
#if defined(_WIN32)
    std::wofstream fout;
    fout.open("files.txt");
    DWORD dr = GetLogicalDrives();
    /*for (int x = 0; x <= 'Z'-'A'; x++)
    {
        int n = ((dr >> x) & 1);
        if (n)
        {
            std::wstring disc;
            disc.push_back((wchar_t)('A' + x));
            disc += L":\\";*/
            s_ptr_->Index(fout, L"D:\\"/*disc*/);
        */}
    }*/
    fout.close();

#else
    std::ofstream fout;
    fout.open ("files.txt");
    s_ptr_->Index (fout, "");
    fout.close ();
#endif
}

StopThread::StopThread(SearchFiles* ptr): QThread(), s_ptr_(ptr) {}

void StopThread::run() {

}
