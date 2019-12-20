/*
 * Copyright 2019 Richard Liebscher <richard.liebscher@gmail.com>.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "networklistener.h"

#include <QNetworkConfiguration>
#include <QDebug>

namespace DataMeter {

static QList<QNetworkConfiguration::BearerType> MOBILE_DATA_FAMILY {
    QNetworkConfiguration::Bearer2G,
    QNetworkConfiguration::Bearer3G,
    QNetworkConfiguration::Bearer4G
};


NetworkListener::NetworkListener(QObject *parent) : QObject(parent)
{
    // Detect when a network interface changes status, so we announce ourselves
    // in the new network
    connect(
        &m_networkManager, &QNetworkConfigurationManager::configurationChanged,
        this, &NetworkListener::onNetworkConfigurationChanged);
    connect(
        &m_networkManager, &QNetworkConfigurationManager::configurationAdded,
        this, &NetworkListener::onNetworkConfigurationChanged);
    connect(
        &m_networkManager, &QNetworkConfigurationManager::configurationRemoved,
        this, &NetworkListener::onNetworkConfigurationRemoved);

    qDebug() << "Discovered network configurations:";
    const auto allConfigs = m_networkManager.allConfigurations(
                QNetworkConfiguration::Active);
    for (const auto& config : allConfigs) {
        m_activeConfigurations.insert(config.identifier());
        printConfig(config);
    }
    refresh();
}

void NetworkListener::onNetworkConfigurationChanged(
        const QNetworkConfiguration &config)
{
    int activeConfigs = m_activeConfigurations.size();
    QString id = config.identifier();

    if (config.state().testFlag(QNetworkConfiguration::Active)) {
        m_activeConfigurations.insert(id);
#ifndef QT_NO_DEBUG_OUTPUT
        if (!m_activeConfigurations.contains(id)) {
            qDebug() << "New active network configuration:";
            printConfig(config);
        }
#endif
    } else {
        m_activeConfigurations.remove(id);
#ifndef QT_NO_DEBUG_OUTPUT
        if (m_activeConfigurations.contains(id)) {
            qDebug() << "Inactivated network configuration:";
            printConfig(config);
        }
#endif
    }

    int newActiveConfigs = m_activeConfigurations.size();
    if (newActiveConfigs > activeConfigs) {
        refresh();
        Q_EMIT networkChanged();
    }
}

void NetworkListener::onNetworkConfigurationRemoved(
        const QNetworkConfiguration &config)
{
    if (m_activeConfigurations.remove(config.identifier())) {
        refresh();
        Q_EMIT networkChanged();
    }
}

void NetworkListener::printConfig(const QNetworkConfiguration &config)
{
    qDebug() << " " << config.name();
    qDebug() << "    id:" << config.identifier();
    qDebug() << "    bearer type:" << config.bearerTypeName();
    qDebug() << "    purpose:" << config.purpose();
    qDebug() << "    state:" << config.state();
}

void NetworkListener::refresh()
{
    const auto configs = m_networkManager.allConfigurations(
        QNetworkConfiguration::Active);

    m_hasMobileData = false;
    for (auto& config : configs) {
        if (MOBILE_DATA_FAMILY.contains(config.bearerTypeFamily())) {
            m_hasMobileData = true;
        }
    }
}

} // namespace SailfishConnect
