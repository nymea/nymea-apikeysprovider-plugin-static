#ifndef APIKEYSPROVIDERSTATIC_H
#define APIKEYSPROVIDERSTATIC_H

#include <network/apikeys/apikeysprovider.h>

class ApiKeysProviderStatic : public ApiKeysProvider
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "io.nymea.ApiKeysProviderStatic")
    Q_INTERFACES(ApiKeysProvider)
public:
    explicit ApiKeysProviderStatic();
    ~ApiKeysProviderStatic() = default;

    QHash<QString, ApiKey> apiKeys() const;

};

#endif // APIKEYSPROVIDERSTATIC_H
