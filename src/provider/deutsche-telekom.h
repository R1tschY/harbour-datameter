#ifndef GERMANYD1_H
#define GERMANYD1_H

#include "../provider.h"

class QNetworkReply;

namespace DataMeter {

class CyclicHttpRequest;

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

private:
    CyclicHttpRequest* m_request;
    DataUsage m_lastState;

    void onSuccess(QNetworkReply* reply);
    void sendUpdate(DataUsage dataUsage);
    void sendErrorUpdate(const QString& message);
};

} // namespace DataMeter

#endif // GERMANYD1_H
