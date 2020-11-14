
#include <QApplication>
#include <QCommandLineParser>
#include <QQmlApplicationEngine>

#include <wrappers/LoginWrapper.hpp>

#include <ClientConnection.hpp>

#include <deliveryVersion.h>

int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setOrganizationName("gSystem Labs");
    QCoreApplication::setApplicationName("Desk Orders");
    QCoreApplication::setApplicationVersion(VERSION_STR);
    
    QGuiApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::applicationName());
    parser.addHelpOption();
    parser.addVersionOption();
    parser.process(app);

    bool invalid = false;
    ClientConnection *cConnection = ClientConnection::instance();
    std::string sSignature("sig12xss92383");
    if (cConnection->signatureValid(sSignature)) {
        VersionResponse_Status vStatus = cConnection->versionValid(VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
        if (vStatus == VersionResponse_Status_RPC_FAILED || vStatus == VersionResponse_Status_VERSION_INCOMPATIBLE) {
            invalid = true;
        }
    } else {
        invalid = true;
    }

    QQmlApplicationEngine engine;
    LoginWrapper loginWrapper(&engine);
    engine.load(QUrl(QStringLiteral("qrc:/deskOrdersMain.qml")));

    return (!engine.rootObjects().isEmpty() && !invalid) ? app.exec() : -1;
}
