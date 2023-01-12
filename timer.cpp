#include "timer.h"

//JSON handling
#include <iostream>
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

Timer::Timer(int delay, QObject *parent) : QObject(parent)
{
    _delay = delay;
    _timer = new QTimer();
    QObject::connect(_timer, SIGNAL(timeout()), this, SLOT(timerFunction()));
    _timer->start(delay);
    db.configureConnection("localhost", "db", "root", "haslo123");
}

Timer::~Timer()
{
    _timer->stop();
}

int Timer::timerGetDelay()
{
    return _delay;
}

void Timer::timerSetDelay(int delay)
{
    _delay = delay;
    _timer->setInterval(delay);
}

bool Timer::timerStatus()
{
    return _timer->isActive();
}

void Timer::timerSetServer(WebSocket *server)
{
    _server = server;
}

void Timer::timerFunction()
{
    qDebug() << "Database connection: " << db.getConnection();
    QDateTime dt = QDateTime::currentDateTime();
    qDebug() << "[" << dt.toString("hh:mm:ss.z") << "]";

    QString message = _server->reciveMessage();

    // SWITCH
    qDebug() << "*****";
    qDebug() << "Button status: " << button.getStatus();

    // BME280
    if(bme280.getDeviceId() < 0) {
      qDebug() << "Sensor not found.";
    }
    else {
        qDebug() << "Sensor found (" << bme280.getDeviceId() << ")";
    }

    if(message.length() > 1) {
        json j = json::parse(message.toStdString());
        std::cout << "Message recived: " << message.toStdString() << std::endl;
        std::cout << "JSON conversion: " << j.dump(4) << std::endl;
        std::cout << "Temperature: " << j["set_temp"] << std::endl;
        std::cout << "Humidity: " << j["set_humi"] << std::endl;
        //std::cout << "Window: " << j["set_wind"] << std::endl;

        double set_temp = std::stod(j["set_temp"].get<std::string>());
        double set_humi = std::stod(j["set_humi"].get<std::string>());
        //bool set_wind = j["set_wind"].get<bool>();
        bool set_wind = button.getStatus();

        double out_pid_temp = temp_pid.calculate(set_temp);
        double out_pid_humi = humi_pid.calculate(set_humi);

        double disr_temp = 0;
        double disr_humi = 0;

        if (set_wind) {
            disr_temp = -10;
            disr_humi = 20;
        }

        out_pid_temp = out_pid_temp + disr_temp;
        out_pid_humi = out_pid_humi + disr_humi;

        double obj_temp = temp_object.calculate(out_pid_temp);
        double obj_humi = humi_object.calculate(out_pid_humi);

        temp_pid.setValue(obj_temp);
        humi_pid.setValue(obj_humi);

        bme280.getData();
        double out_temp = bme280.getTemperature();
        double out_humi = bme280.getHumidity();

        json m;
        m["act_temp"] = out_temp;
        m["act_humi"] = out_humi;
        m["set_wind"] = set_wind;
        m["uchyb_temp"] = temp_pid.getError();
        m["uchyb_humi"] = humi_pid.getError();
        if(set_wind) {
            m["ster_temp"] = out_pid_temp - disr_temp;
            m["ster_humi"] = out_pid_humi - disr_humi;
            m["zakl_temp"] = 10;
            m["zakl_humi"] = 20;
        } else {
            m["ster_temp"] = out_pid_temp;
            m["ster_humi"] = out_pid_humi;
            m["zakl_temp"] = 0;
            m["zakl_humi"] = 0;
        }

        db.insertMeasurements(set_temp, set_humi, out_temp, out_humi, set_wind);
        QString json_message = QString::fromStdString(m.dump());
        std::cout << "Message sended: " << json_message.toStdString() << std::endl;
        _server->sendMessage(json_message);
    }
}
