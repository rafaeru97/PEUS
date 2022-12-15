//GUI
#include <QApplication>
#include <QtWebKitWidgets/QWebView>

//WebSocket
#include <QWebSocket>
#include <QWebSocketServer>
#include "websocket.h"

//Debug
#include <QDebug>

//Timer
#include "timer.h"

int main(int argc, char *argv[])
{
    bool debug = true; // true - enabled debug mode, false - disabled debug mode

    QApplication app(argc, argv);

    //CREATING TIMER
    qDebug() << "An attempt to create Timer.";
    Timer *clock = new Timer(1000);
    if(clock->timerStatus())
        qDebug() << "Timer created successfully with delay:" << clock->timerGetDelay() << "ms.";
    else
        qDebug() << "Timer has not been created.";

    //CREATING WEBSOCKET SERVER
    qDebug() << "*****";
    qDebug() << "An attempt to create WebSocket Server.";
    quint16 port = 43434;
    WebSocket *server = new WebSocket(port);
    QObject::connect(server, &WebSocket::closed, &app, &QCoreApplication::quit);

    //LINKING SERVER WITH TIMER TO HANDLE MESSAGES
    qDebug() << "*****";
    qDebug() << "An attempt to link Timer with WebSocket Server.";
    clock->timerSetServer(server);
    qDebug() << "Linking successfully.";

    //CREATING WEBVIEW
    qDebug() << "*****";
    qDebug() << "An attempt to create WebView.";
    QWebView *view = new QWebView();
    view->resize(1920,1080);
    view->load(QUrl("file:///home/pi/Desktop/Project/GUI/index.html"));
    if(debug) {
        QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);
    } else {
        view->showFullScreen();
        view->setContextMenuPolicy(Qt::NoContextMenu);
    }
    qDebug() <<"WebView created successfully with" << view->size();
    view->show();
    qDebug() << "*****";
    qDebug() << "Successful initialization.";

    return app.exec();
}
