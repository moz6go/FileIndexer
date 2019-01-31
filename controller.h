#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include "searchfiles.h"

class Controller : public QObject {
    Q_OBJECT
    SearchFiles* s_ptr_;
public:
    Controller (SearchFiles* s_ptr);
public slots:
    void onStartButtonClick();
    void onStopButtonClick();
    void onPauseButtonClick();
    void onSearchButtonClick();
signals:
    void paused (QString);
    void finished();
};

#endif // CONTROLLER_H
