#include "controller.h"

Controller::Controller (Indexer* indx_ptr) : indx_ptr_(indx_ptr) {}

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
}

void Controller::onSearchButtonClick() {

}
