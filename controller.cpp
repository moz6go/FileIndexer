#include "controller.h"

Controller::Controller (Indexer* indx_ptr) : indx_ptr_(indx_ptr) {}

Controller::Controller (IndexReader* reader_ptr) : reader_ptr_(reader_ptr) {}

void Controller::onStartButtonClick(){
    indx_ptr_->SetCount(0, 0);
    indx_ptr_->SetState (DEFAULT);
    indx_ptr_->Index ();
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
    reader_ptr_->ReadIndexToString ();
    emit finished ();
}

void Controller::onSearchButtonClick(SearchType key, string_t value) {
    reader_ptr_->SearchInIndex (key, value);
}
