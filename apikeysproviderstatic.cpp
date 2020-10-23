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
