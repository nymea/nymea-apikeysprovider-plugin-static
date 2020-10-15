# API keys provider plugin for nymea

## Building

Install the nymea SDK

    sudo apt-get install nymea-sdk


Create a file named `apikeys.json` in the data directory of this repository with the following format:

    {
        "service": {
            "appid": "myAppId",
            "key": "some-key"
        }
    }

nymea plugins having requested a matching service in their plugin JSON file will be
granted access to the given service credentials. The service map may contain any
key-value pair required to communicate to the service.

Example:

    {
        "openweathermap": {
            "appid": "abcdef1234567890"
        },
        "someotherservice": {
            "apiKey": "some-key",
            "someOtherOption": "some-other-value"
        }
    }

Then build this project in a normal (qmake) way:

    qmake
    make


## Usage

The resulting plugin file can be installed systemwide into $LIBDIR/nymea/apikeyproviders
or by pointing nymea to it using the NYMEA_APIKEYS_PLUGINS_PATH environment variable.

## Disclaimer

We are aware that security of this is mediocre at best and thus this plugin should only
be used for non mission critical api keys like for example openweathermap where an
exploitation of the key only causes the service to cease working because of the API rate
limit but not allow extracting any user information or similar.

For more sensitive API keys, other api key provider plugins should be used which can use
more secure means of providing api keys, such as fetching temporary keys from an online
service or using an encrypted storage of some sort.

The main purpose of this plugin is to fulfill the requirements of some online services
which require to not host api keys in open source code repositories or distribute them
in plaintext to users by their license agreement.
