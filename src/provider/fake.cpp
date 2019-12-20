#include "fake.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMimeType>
#include <QNetworkRequest>
#include <QRegularExpression>
#include <QDateTime>

#include "../cyclichttprequest.h"
#include "../networkresponse.h"

namespace DataMeter {

FakeProvider::FakeProvider(QObject* parent)
    : ProviderModel(parent)
    , m_request(new CyclicHttpRequest(this))
{
    m_lastState.lastUpdate = QDateTime::currentMSecsSinceEpoch();
    m_lastState.nextUpdate = QDateTime::currentMSecsSinceEpoch() + 1000LL * 3600LL;
    m_lastState.passName = QString("Fake");
    m_lastState.passStage = QString();
    m_lastState.dataVolume = 1024LL * 1024LL * 1024LL * 10LL;
    m_lastState.usedDataVolume = 1024LL * 1024LL * 999LL; // * 1024LL * 4LL;
    m_lastState.remainingTime = 1000LL * 3600LL * 300LL;
    m_lastState.valid = true;
}

QString FakeProvider::name()
{
    return tr("Deutsche Telekom (Congstar, ...)");
}

QString FakeProvider::description()
{
    return tr("Network of the Deutsche Telekom");
}

DataUsage FakeProvider::lastState()
{
    return m_lastState;
}

} // namespace DataMeter
