/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*
* Copyright 2013 - 2024, nymea GmbH
* Contact: contact@nymea.io
*
* This file is part of nymea.
* This project including source code and documentation is protected by
* copyright law, and remains the property of nymea GmbH. All rights, including
* reproduction, publication, editing and translation, are reserved. The use of
* this project is subject to the terms of a license agreement to be concluded
* with nymea GmbH in accordance with the terms of use of nymea GmbH, available
* under https://nymea.io/license
*
* GNU Lesser General Public License Usage
* Alternatively, this project may be redistributed and/or modified under the
* terms of the GNU Lesser General Public License as published by the Free
* Software Foundation; version 3. This project is distributed in the hope that
* it will be useful, but WITHOUT ANY WARRANTY; without even the implied
* warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this project. If not, see <https://www.gnu.org/licenses/>.
*
* For any further details and any questions please contact us under
* contact@nymea.io or see our FAQ/Licensing Information on
* https://nymea.io/license/faq
*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "apikeysproviderstatic.h"

#include "loggingcategories.h"
NYMEA_LOGGING_CATEGORY(dcApiKeysProviderStatic, "ApiKeysProviderStatic")

#include "apikeys.h"

#include <QJsonDocument>

ApiKeysProviderStatic::ApiKeysProviderStatic()
{
    qCDebug(dcApiKeysProviderStatic()) << "Loaded static provider";
}

QHash<QString, ApiKey> ApiKeysProviderStatic::apiKeys() const
{
    QHash<QString, ApiKey> ret;

    QJsonParseError error;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(QByteArray::fromBase64(data), &error);
    if (error.error != QJsonParseError::NoError) {
        qCWarning(dcApiKeysProviderStatic()) << "Error parsing API input file";
        return ret;
    }

    QVariantMap keysMap = jsonDoc.toVariant().toMap();
    foreach (const QString &keyName, keysMap.keys()) {
        QVariantMap keyContent = keysMap.value(keyName).toMap();
        ApiKey key;
        foreach (const QString &entryName, keyContent.keys()) {
            key.insert(entryName, keyContent.value(entryName).toByteArray());
        }
        ret.insert(keyName, key);
    }
    return ret;
}
