#include "controller.h"

Controller::Controller (Indexer* indx_ptr) : indx_ptr_(indx_ptr) {}

void Controller::onStartButtonClick(){
    indx_ptr_->SetCount(0, 0);
    indx_ptr_->SetState (DEFAULT);
    indx_ptr_->WriteIndex ();
    emit finished ();
}

void Controller::onStopButtonClick() {
    indx_ptr_->SetState (STOP);
    emit finished ();
}

void Controller::onPauseButtonClick() {
    indx_ptr_->SetState (PAUSE);
    emit finished ();
}

void Controller::ReadIndex (){
    indx_ptr_->ReadIndex ();
    emit finished ();
}

void Controller::onSearchButtonClick(SearchType key, string_t value) {
    indx_ptr_->Search (key, value);
}
