#ifndef SQL_H
#define SQL_H
#include <QSqlDatabase>
#include <QSqlQuery>

class Sql
{
    public:
        Sql();
        bool configureConnection(const QString host, const QString database, const QString username, const QString password);
        bool getConnection();
        void insertMeasurements(int set_temperature, int set_humidity, int temperature, int humidity, int window);

    private:
        QSqlDatabase db;
        bool ok = false;
};

#endif // SQL_H
