#include "deutsche-telekom.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QMimeType>
#include <QNetworkRequest>
#include <QRegularExpression>

#include "../networkresponse.h"

namespace DataMeter {

DeutscheTelekom::DeutscheTelekom(QObject* parent)
    : ProviderModel(parent)
{
    m_request = QNetworkRequest(
        QUrl("https://pass.telekom.de/api/service/generic/v1/status"));
    m_request.setRawHeader("Accept", "application/json");
    m_request.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/4.0");
    connect(&m_timer, &QTimer::timeout,
        this, &DeutscheTelekom::doStart);
    m_timer.start(60000);
    m_timer.setSingleShot(true);
    doStart();
}

QString DeutscheTelekom::name()
{
    return tr("Germany D1 (Deutsche Telekom)");
}

QString DeutscheTelekom::description()
{
    return tr("Network of the Deutsche Telekom");
}

DataUsage DeutscheTelekom::lastState()
{
    return m_lastState;
}

void DeutscheTelekom::refresh()
{

}

void DeutscheTelekom::doStart()
{
    if (m_reply) {
        m_reply->abort();
    }

    m_reply = m_nam.get(m_request);
    connect(
        m_reply, &QNetworkReply::finished,
        this, &DeutscheTelekom::onFinished);
}

void DeutscheTelekom::onFinished()
{
    if (m_reply == nullptr) {
        return;
    }

    auto now = QDateTime::currentDateTimeUtc();
    auto response = HttpResponse(m_reply);
    m_reply = nullptr;

    if (response.hasNetworkError()) {
        return sendErrorUpdate(response.errorString());
    }

    int code = response.statusCode();
    if (code != 200) {
        return sendErrorUpdate(tr("Got HTTP status code %1: %2").arg(code).arg(response.errorString()));
    }

    //    if (!response.errorString().isEmpty()) {
    //        return sendErrorUpdate(response.errorString());
    //    }

    QRegularExpression re("\\Aapplication/json(?:\\s*;\\s*charset\\s*=\\s*(?:UTF|utf)-8)?\\z");
    if (!re.match(response.header("Content-Type")).hasMatch()) {
        return sendErrorUpdate(tr("Got non-JSON response: %1").arg(response.header("Content-Type")));
    }

    QByteArray content = response.content();
    qDebug() << "got content" << content;

    QJsonParseError error;
    QJsonDocument json = QJsonDocument::fromJson(content, &error);
    if (error.error != QJsonParseError::NoError) {
        return sendErrorUpdate(tr("JSON parse error"));
    }

    if (!json.isObject()) {
        return sendErrorUpdate(tr("Unexpected JSON format"));
    }

    QJsonObject jsonObj = json.object();
    DataUsage lastState;
    lastState.lastUpdate = QDateTime::fromMSecsSinceEpoch(jsonObj.value(QStringLiteral("usedAt")).toVariant().toLongLong());
    lastState.passName = jsonObj.value(QStringLiteral("passName")).toString();
    lastState.passStage = jsonObj.value(QStringLiteral("passStage")).toString();
    lastState.dataVolume = jsonObj.value(QStringLiteral("initialVolume")).toVariant().toLongLong();
    lastState.usedDataVolume = jsonObj.value(QStringLiteral("usedVolume")).toVariant().toLongLong();
    lastState.until = now.addSecs(jsonObj.value(QStringLiteral("remainingSeconds")).toInt());
    sendUpdate(std::move(lastState));
}

void DeutscheTelekom::sendUpdate(DataUsage dataUsage)
{
    m_lastState = dataUsage;
    m_timer.start(600000);
    m_lastState.valid = true;
    emit update();
}

void DeutscheTelekom::sendErrorUpdate(const QString& message)
{
    DataUsage lastState;
    lastState.error = message;
    m_timer.start(60000);
    qDebug() << "got error" << message;
    sendUpdate(std::move(lastState));
}

} // namespace DataMeter
