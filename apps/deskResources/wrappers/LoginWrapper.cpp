
#include "LoginWrapper.hpp"

#include <QQmlContext>
#include <ClientConnection.hpp>

LoginWrapper::LoginWrapper(QQmlApplicationEngine *engine, QObject *parent)
    : QObject(parent)
    , m_logged(false)
{
    engine->rootContext()->setContextProperty("LoginWrapper", this);
    Q_INIT_RESOURCE(resources);
}

void LoginWrapper::login(const QString &username, const QString &password) 
{
    bool logged = false;

    std::string token = ClientConnection::instance()->login(username.toStdString(), password.toStdString());
    if (!token.empty()) {
        logged = true;
    }

    if (logged != m_logged) {
        m_logged = logged;
        emit authChanged(m_logged);
    }
}
