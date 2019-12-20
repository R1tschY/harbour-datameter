#include <QGuiApplication>
#include <QScopedPointer>
#include <QtQuick>

#include <sailfishapp.h>

#include "provider.h"
#include "provider/deutsche-telekom.h"
#include "provider/fake.h"
#include "networklistener.h"

using namespace DataMeter;

int main(int argc, char* argv[])
{
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));

    qmlRegisterType<Provider>("DataMeter", 0, 1, "Provider");
    qmlRegisterType<NetworkListener>("DataMeter", 0, 1, "NetworkListener");

    Provider provider;
    if (qEnvironmentVariableIsSet("HARBOUR_DATAMETER_TESTENV")) {
        provider.setModel(new FakeProvider(app.data()));
    } else {
        provider.setModel(new DeutscheTelekom(app.data()));
    }
    NetworkListener networkListener;

    QQuickView* view = SailfishApp::createView();

    QQmlContext* ctx = view->rootContext();
    ctx->setContextProperty("provider", &provider);
    ctx->setContextProperty("networkListener", &networkListener);

    view->setSource(SailfishApp::pathToMainQml());
    view->showFullScreen();

    return app->exec();
}
