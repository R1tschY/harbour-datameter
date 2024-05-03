#ifndef GERMANYD1_H
#define GERMANYD1_H

#include "../provider.h"

#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>

class QNetworkReply;

namespace DataMeter {

/**
 * @brief Provider for network of Deutsche Telekom (D1)
 */
class DeutscheTelekom : public ProviderModel {
    Q_OBJECT
public:
    explicit DeutscheTelekom(QObject* parent = nullptr);

signals:

public slots:

public:
    QString name() override;
    QString description() override;

    DataUsage lastState() override;
    void refresh() override;

private:
    QNetworkRequest m_request;
    QNetworkAccessManager m_nam;
    QNetworkReply* m_reply = nullptr;
    QTimer m_timer;
    DataUsage m_lastState;

    void doStart();
    void onFinished();
    void sendUpdate(DataUsage dataUsage);
    void sendErrorUpdate(const QString& message);
};

} // namespace DataMeter

#endif // GERMANYD1_H
