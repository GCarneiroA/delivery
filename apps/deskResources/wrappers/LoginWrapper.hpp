
#ifndef LOGINWRAPPER_HPP
#define LOGINWRAPPER_HPP

#include <QObject>
#include <QQmlApplicationEngine>

class QString;

class LoginWrapper : public QObject
{
    Q_OBJECT
public:
    explicit LoginWrapper(QQmlApplicationEngine *engine, QObject *parent = nullptr);
    Q_INVOKABLE void login(const QString &username, const QString &password);

signals:
    void authChanged(bool);

private:
    bool m_logged;
};

#endif
