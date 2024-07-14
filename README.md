# ESPSystem

This is the System implementation for ESP32 and ESP8266 with Arduino.

It contains the basic classes which inherit from the [Interfaces](https://github.com/xit303/Interfaces.git) repository.

`SettingsBase` is the implementation of the `ISettingsBase` interface. It uses the ESP32 `Preferences` class to store system settings. `SettingsBase` only overrides the `Init`, `SetDefault`, `Reload` and `Save` methods, so that we don't need to take care of calling `Preferences.begin()` and `Preferences.end()`.

`OnInit`, `OnSetDefault`, `OnReload`, `OnSave` and `HasChanged` have to be overwritten by all classes which inherit form `SettingsBase`.

Here is a short implementation example. Please note that this is not the full implementation of the WiFiSettings class, which can be found in the future in a different repository.

WiFiSettings.h

```
#include "SettingsBase.h"

class WiFiSettings : public SettingsBase
{
private:
    bool enabled;
    bool loadedEnabled;
    bool defaultEnabled;

protected:
    virtual void OnInit() override;
    virtual void OnSetDefault() override;
    virtual void OnReload() override;
    virtual void OnSave() override;

    virtual void Print() override;

    WiFiSettings(const char *name, bool defaultEnabled = false);

    virtual bool HasChanged() override;
};
```

WiFiSettings.cpp

```
//******************************************************
// Includes
//******************************************************

#include "WiFiSettings.h"

//******************************************************
// Public Methods
//******************************************************

WiFiSettings::WiFiSettings(const char *name, bool defaultEnabled)
    : SettingsBase(name)
{
    this->defaultEnabled = defaultEnabled;
}

bool WiFiSettings::HasChanged()
{
    return enabled != loadedEnabled;
}

//******************************************************
// Protected Methods
//******************************************************

void WiFiSettings::OnInit()
{
    loadedEnabled = enabled = preferences.getBool("enabled", defaultEnabled);

    Print();
}

void WiFiSettings::OnSetDefault()
{
    loadedEnabled = enabled = defaultEnabled;

    preferences.remove("enabled");
}

void WiFiSettings::OnReload()
{
    enabled = loadedEnabled;
}

void WiFiSettings::OnSave()
{
    if (enabled != loadedEnabled)
    {
        loadedEnabled = enabled;
        preferences.putBool("enabled", enabled);
    }

    Print();
}

void WiFiSettings::Print()
{
    Serial.print("Enabled: ");
    Serial.println(enabled);
}

```
