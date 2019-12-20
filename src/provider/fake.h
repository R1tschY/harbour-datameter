#ifndef FAKE_H
#define FAKE_H

#include "../provider.h"

class QNetworkReply;

namespace DataMeter {

class CyclicHttpRequest;

/**
 * @brief Fake provider
 */
class FakeProvider : public ProviderModel {
    Q_OBJECT
public:
    explicit FakeProvider(QObject* parent = nullptr);

signals:

public slots:

public:
    QString name() override;
    QString description() override;

    DataUsage lastState() override;

private:
    CyclicHttpRequest* m_request;
    DataUsage m_lastState;
};

} // namespace DataMeter

#endif // FAKE_H
