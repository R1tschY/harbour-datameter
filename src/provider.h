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

    Q_PROPERTY(QString passName READ passName NOTIFY dataChanged)
    Q_PROPERTY(bool hasError READ hasError NOTIFY dataChanged)
    Q_PROPERTY(QString errorString READ errorString NOTIFY dataChanged)
    Q_PROPERTY(qreal dataVolume READ dataVolume NOTIFY dataChanged)
    Q_PROPERTY(qreal usedDataVolume READ usedDataVolume NOTIFY dataChanged)
    Q_PROPERTY(QDateTime lastUpdate READ lastUpdate NOTIFY dataChanged)
    Q_PROPERTY(QDateTime nextUpdate READ nextUpdate NOTIFY dataChanged)
    Q_PROPERTY(QDateTime until READ until NOTIFY dataChanged)

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
    QDateTime until() const;

    Q_INVOKABLE void refresh();

signals:
    void dataChanged();
    void modelChanged();

private:
    ProviderModel* m_model = nullptr;

    void onUpdate();
};

struct DataUsage {
    bool valid = false;
    QString error;

    QDateTime lastUpdate;
    QDateTime nextUpdate;
    QDateTime until;

    QString passName;
    QString passStage;

    qlonglong dataVolume = 0;
    qlonglong usedDataVolume = 0;
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
