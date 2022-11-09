#ifndef MAIN_H
#define MAIN_H

#include <QObject>
#include <QTimer>
#include <QDateTime>
#include <QDebug>

#include "websocket.h"
#include "object.h"
#include "pid.h"


class Timer : public QObject
{
    Q_OBJECT

public:
    explicit Timer(int delay = 1000, QObject* parent = nullptr);
    ~Timer();

public slots:
    int timerGetDelay();
    void timerSetDelay(int delay);
    bool timerStatus(); // return status of timer
    void timerFunction();
    void timerSetServer(WebSocket *server);

private:
    int _delay;
    QTimer *_timer;
    WebSocket *_server;

    bool init = true;
    int temp_start = 0;
    int humi_start = 30;

    PID temp_pid = PID(1, 100, -100, 0.1, 0.1, 0, temp_start);
    PID humi_pid = PID(1, 100, -100, 0.1, 0.1, 0, humi_start);

    Object temp_object = Object(1, 1, 10, temp_start);
    Object humi_object = Object (1, 1, 10, humi_start);
};

#endif // MAIN_H
