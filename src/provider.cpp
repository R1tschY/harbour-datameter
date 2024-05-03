#include "provider.h"

namespace DataMeter {

QString Provider::name()
{
    return m_model ? m_model->name() : QString();
}

QString Provider::description()
{
    return m_model ? m_model->description() : QString();
}

void Provider::setModel(ProviderModel* model)
{
    if (m_model) {
        m_model->disconnect(this);
    }

    m_model = model;

    if (m_model) {
        connect(m_model, &ProviderModel::update,
            this, &Provider::onUpdate);
    }

    emit modelChanged();
}

QString Provider::passName() const
{
    return m_model ? m_model->lastState().passName : QString();
}

bool Provider::hasError() const
{
    return !m_model || !m_model->lastState().error.isEmpty();
}

QString Provider::errorString() const
{
    return m_model ? m_model->lastState().error : QString();
}

qreal Provider::dataVolume() const
{
    return m_model ? m_model->lastState().dataVolume : -1;
}

qreal Provider::usedDataVolume() const
{
    return m_model ? m_model->lastState().usedDataVolume : -1;
}

QDateTime Provider::lastUpdate() const
{
    return m_model
            ? m_model->lastState().lastUpdate
            : QDateTime();
}

QDateTime Provider::nextUpdate() const
{
    return m_model
            ? m_model->lastState().nextUpdate
            : QDateTime();
}

QDateTime Provider::until() const
{
    return m_model
            ? m_model->lastState().until
            : QDateTime();
}

void Provider::refresh()
{
    if (m_model) {
        m_model->refresh();
    }
}

void Provider::onUpdate()
{
    emit dataChanged();
}

} // namespace DataMeter
