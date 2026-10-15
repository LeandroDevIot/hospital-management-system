#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>         // <-- Adicionado para permitir injetar no QML
#include "totemcontroller.h"   // <-- Adicionado para conhecer a nossa classe

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // --- INÍCIO DA INJEÇÃO DO CONTROLADOR ---
    TotemController totemController;
    engine.rootContext()->setContextProperty("totemController", &totemController);
    // --- FIM DA INJEÇÃO ---

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.loadFromModule("TotemHospitalar", "Main");

    return QGuiApplication::exec();
}