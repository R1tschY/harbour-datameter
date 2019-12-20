#ifndef CYCLICHTTPREQUEST_H
#define CYCLICHTTPREQUEST_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QObject>
#include <QUrl>

class QNetworkAccessManager;
class QNetworkReply;
class QTimer;

namespace DataMeter {

class CyclicHttpRequest : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool active READ active NOTIFY activeChanged)
    Q_PROPERTY(QNetworkRequest request READ request WRITE setRequest NOTIFY requestChanged)

public:
    explicit CyclicHttpRequest(QObject* parent = nullptr);

    QNetworkRequest request() const;
    void setRequest(const QNetworkRequest& request);

    bool active() const;

    void start();
    void startAt(qlonglong date);

signals:
    void result(QNetworkReply* reply);

    void activeChanged();
    void requestChanged();

public slots:

private:
    bool m_active = false;
    QNetworkRequest m_request;
    QNetworkAccessManager m_nam;
    QNetworkReply* m_reply = nullptr;
    QTimer* m_timer;

    void doStart();
    void onFinished();
};

} // namespace DataMeter

#endif // CYCLICHTTPREQUEST_H
