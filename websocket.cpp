#include "websocket.h"

WebSocket::WebSocket(quint16 port, QObject *parent) : QObject(parent), mWebSocketServer(new QWebSocketServer(QStringLiteral("Server"), QWebSocketServer::NonSecureMode, this))
{
    if (!mWebSocketServer->listen(QHostAddress::LocalHost, port)) {
            qDebug() << "Creating QWebSocketServer failed:" << mWebSocketServer->errorString();
            exit(1);
    }
    qDebug() << "QWebSocketServer created successfully on port:" << port;

    connect(mWebSocketServer, &QWebSocketServer::newConnection, this, &WebSocket::newConnection);
    connect(mWebSocketServer, &QWebSocketServer::closed, this, &WebSocket::closed);
}

WebSocket::~WebSocket()
{
    mWebSocketServer->close();
    qDeleteAll(mClients.begin(), mClients.end());
}

void WebSocket::newConnection()
{
    QWebSocket *mSocket = mWebSocketServer->nextPendingConnection();
    connect(mSocket, &QWebSocket::textMessageReceived, this, &WebSocket::onReciveMessage);

    mClients << mSocket;
    messageSocket = mSocket;
}

void WebSocket::onReciveMessage(const QString message)
{
    reciveMessageBuffor = message;
}

QString WebSocket::reciveMessage()
{
    return reciveMessageBuffor;
}

void WebSocket::sendMessage(const QString message)
{
    if (messageSocket) {
        messageSocket->sendTextMessage(message);
    }
}
