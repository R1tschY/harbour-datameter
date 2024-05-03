#include "fake.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMimeType>
#include <QNetworkRequest>
#include <QRegularExpression>
#include <QDateTime>

namespace DataMeter {

FakeProvider::FakeProvider(QObject* parent)
    : ProviderModel(parent)
{
    m_lastState.lastUpdate = QDateTime::currentDateTimeUtc();
    m_lastState.nextUpdate = QDateTime::currentDateTimeUtc().addSecs(600);
    m_lastState.until = QDateTime::currentDateTimeUtc().addDays(3).addSecs(600);
    m_lastState.passName = QString("Fake");
    m_lastState.passStage = QString();
    m_lastState.dataVolume = 1024LL * 1024LL * 1024LL * 10LL;
    m_lastState.usedDataVolume = 1024LL * 1024LL * 999LL; // * 1024LL * 4LL;
    m_lastState.valid = true;
}

QString FakeProvider::name()
{
    return tr("Fake");
}

QString FakeProvider::description()
{
    return tr("Fake for testing");
}

DataUsage FakeProvider::lastState()
{
    return m_lastState;
}

void FakeProvider::refresh()
{

}

} // namespace DataMeter
