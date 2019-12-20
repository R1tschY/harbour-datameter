#include "cyclichttprequest.h"

#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QTimer>

namespace DataMeter {

CyclicHttpRequest::CyclicHttpRequest(QObject* parent)
    : QObject(parent)
    , m_timer(new QTimer(this))
{
}

QNetworkRequest CyclicHttpRequest::request() const
{
    return m_request;
}

void CyclicHttpRequest::setRequest(const QNetworkRequest& request)
{
    m_request = request;
    emit requestChanged();
}

bool CyclicHttpRequest::active() const
{
    return m_active;
}

void CyclicHttpRequest::start()
{
    connect(m_timer, &QTimer::timeout,
        this, &CyclicHttpRequest::doStart);
    m_timer->start(60000);
    m_timer->setSingleShot(false);
    doStart();
}

void CyclicHttpRequest::doStart()
{
    if (m_active)
        return;

    m_active = true;
    m_reply = m_nam.get(m_request);
    connect(
        m_reply, &QNetworkReply::finished,
        this, &CyclicHttpRequest::onFinished);

    emit activeChanged();
}

void CyclicHttpRequest::onFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    Q_ASSERT(reply == m_reply);

    m_active = false;
    m_reply = nullptr;
    emit result(reply);
    emit activeChanged();
}

} // namespace DataMeter
