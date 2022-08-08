#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>

#include "documentcontroller.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    QGuiApplication::setApplicationName("Notepad Example");
    QGuiApplication::setOrganizationName("Tutorial");
    QGuiApplication::setOrganizationDomain("tutotrial");


    QQmlApplicationEngine engine;
    qmlRegisterType<DocumentController>("notepad.example.texteditor", 1, 0, "DocumentController");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);



    engine.load(url);

    return app.exec();
}
