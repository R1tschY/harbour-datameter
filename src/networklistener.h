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

#pragma once

#include <QNetworkConfigurationManager>
#include <QObject>
#include <QSet>
#include <QString>

class QNetworkConfiguration;

namespace DataMeter {

class NetworkListener : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool hasMobileData READ hasMobileData NOTIFY networkChanged)

public:
    explicit NetworkListener(QObject *parent = nullptr);

    QNetworkConfigurationManager& networkManager() { return m_networkManager; }

    bool hasMobileData() const { return m_hasMobileData; }

signals:
    void networkChanged();

private:
    void onNetworkConfigurationChanged(const QNetworkConfiguration& config);
    void onNetworkConfigurationRemoved(const QNetworkConfiguration& config);
    void printConfig(const QNetworkConfiguration& config);

    QNetworkConfigurationManager m_networkManager;

    QSet<QString> m_activeConfigurations;
    bool m_hasMobileData = false;

    void refresh();
};

} // namespace SailfishConnect
