#ifndef PROVIDER_H
#define PROVIDER_H

#include <QObject>
#include <QString>
#include <QDateTime>

namespace DataMeter {

class ProviderModel;

class Provider : public QObject {
    Q_OBJECT

    Q_PROPERTY(QString name READ name NOTIFY modelChanged)
    Q_PROPERTY(QString description READ description NOTIFY modelChanged)
    Q_PROPERTY(ProviderModel* model READ model WRITE setModel NOTIFY modelChanged)

    Q_PROPERTY(QString passName READ passName NOTIFY update)
    Q_PROPERTY(bool hasError READ hasError NOTIFY update)
    Q_PROPERTY(QString errorString READ errorString NOTIFY update)
    Q_PROPERTY(qreal dataVolume READ dataVolume NOTIFY update)
    Q_PROPERTY(qreal usedDataVolume READ usedDataVolume NOTIFY update)
    Q_PROPERTY(QDateTime lastUpdate READ lastUpdate NOTIFY update)
    Q_PROPERTY(QDateTime nextUpdate READ nextUpdate NOTIFY update)

public:
    QString name();
    QString description();

    ProviderModel* model() const { return m_model; }
    void setModel(ProviderModel* model);

    bool hasError() const;
    QString passName() const;
    QString errorString() const;

    qreal dataVolume() const;
    qreal usedDataVolume() const;

    QDateTime lastUpdate() const;
    QDateTime nextUpdate() const;

    Q_INVOKABLE void refresh();

signals:
    void update();
    void modelChanged();

private:
    ProviderModel* m_model = nullptr;

    void onUpdate();
};

struct DataUsage {
    bool valid = false;
    QString error;

    qlonglong lastUpdate;
    qlonglong nextUpdate;

    QString passName;
    QString passStage;

    qlonglong remainingTime;
    qlonglong dataVolume;
    qlonglong usedDataVolume;
};

class ProviderModel : public QObject {
    Q_OBJECT
public:
    using QObject::QObject;

    virtual QString name() = 0;
    virtual QString description() = 0;

    virtual void refresh() = 0;

    virtual DataUsage lastState() = 0;

signals:
    void update();
};

} // namespace DataMeter

#endif // PROVIDER_H
