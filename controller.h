#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "indexer.h"
#include "indexreader.h"

class Controller : public QObject {
    Q_OBJECT
    Indexer* indx_ptr_;
    IndexReader* reader_ptr_;
public:
    Controller (Indexer* indx_ptr);
    Controller (IndexReader* reader_ptr);
public slots:
    void onStartButtonClick();
    void onStopButtonClick();
    void onPauseButtonClick();
    void onSearchButtonClick(SearchType key, string_t value);
    void ReadIndex ();
signals:
    void finished();
};

#endif // CONTROLLER_H
