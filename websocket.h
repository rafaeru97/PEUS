#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <QObject>
#include <QList>
#include <QWebSocket>
#include <QWebSocketServer>
#include <string>

//JSON handling
#include "nlohmann/json.hpp"
using json = nlohmann::json;

class WebSocket : public QObject
{
    Q_OBJECT

public:
    explicit WebSocket(quint16 port, QObject *parent = nullptr);
    void sendMessage(const QString message);
    QString reciveMessage();
    ~WebSocket();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void newConnection();
    void onReciveMessage(const QString message);

private:
    QWebSocket *messageSocket;
    QString reciveMessageBuffor;
    QWebSocketServer *mWebSocketServer;
    QList<QWebSocket *> mClients;
};

#endif // WEBSOCKET_H
