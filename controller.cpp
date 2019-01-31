#include "controller.h"

Controller::Controller (SearchFiles* ptr) : s_ptr_(ptr) {}

void Controller::onStartButtonClick(){
    s_ptr_->SetCount(0, 0);
    s_ptr_->SetState (DEFAULT);
#if defined(_WIN32)
    std::wofstream fout;
    fout.open("files.txt");
    DWORD dr = GetLogicalDrives();
    for (int x = 0; x <= 'Z'-'A'; x++)
    {
        int n = ((dr >> x) & 1);
        if (n)
        {
            std::wstring disc;
            disc.push_back(static_cast<wchar_t>('A' + x));
            disc += L":\\";
            s_ptr_->Index(fout, disc);
        }
    }
    fout.close();

#else
    std::ofstream fout;
    fout.open ("files.txt");
    s_ptr_->Index (fout, "");
    fout.close ();
#endif
    emit finished ();
}

void Controller::onStopButtonClick() {
    s_ptr_->SetState (STOP);
    emit finished ();
}

void Controller::onPauseButtonClick() {
    s_ptr_->SetState (PAUSE);
    emit paused ("Paused...");
}

void Controller::onSearchButtonClick() {

}
