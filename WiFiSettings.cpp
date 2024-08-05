//******************************************************
// Includes
//******************************************************

#include "WiFiSettings.h"

//******************************************************
// Public Methods
//******************************************************

WiFiSettings::WiFiSettings(const char *name, bool defaultEnabled, String defaultHostname, String defaultSsid, String defaultPassword)
    : SettingsGroup(name)
{
    this->enabled.DefaultValue(defaultEnabled);
    settings.push_back(&this->enabled);

    this->hostname.DefaultValue(defaultHostname),
    settings.push_back(&this->hostname);

    this->ssid.DefaultValue(defaultSsid);
    settings.push_back(&this->ssid);

    this->password.DefaultValue(defaultPassword);
    settings.push_back(&this->password);
}


bool WiFiSettings::Valid()
{
    String host = hostname;
    String ssi = ssid;
    if (host.isEmpty() || !ssi.isEmpty())
        return false;

    // we do not check the password because it can be empty on an open network
    return true;
}

//******************************************************
// Protected Methods
//******************************************************

void WiFiSettings::OnInit()
{
    bool b = preferences.getBool(enabled.Name(), enabled.DefaultValue());
    enabled.LoadedValue(b);
    settings.push_back(&enabled);

    String s = preferences.getString(hostname.Name(), hostname.DefaultValue());
    hostname.LoadedValue(s);
    settings.push_back(&hostname);

    s = preferences.getString(ssid.Name(), ssid.DefaultValue());
    ssid.LoadedValue(s);
    settings.push_back(&ssid);

    s = preferences.getString(password.Name(), password.DefaultValue());
    password.LoadedValue(s);
    settings.push_back(&password);

    Print();
}

void WiFiSettings::OnSetDefault()
{
    preferences.remove(enabled.Name());
    preferences.remove(hostname.Name());
    preferences.remove(ssid.Name());
    preferences.remove(password.Name());
}

void WiFiSettings::OnSave()
{
    if (enabled.HasChanged())
    {
        preferences.putBool(enabled.Name(), enabled);
    }

    if (hostname.HasChanged())
    {
        preferences.putString(hostname.Name(), hostname);
    }

    if (ssid.HasChanged())
    {
        preferences.putString(ssid.Name(), ssid);
    }

    if (password.HasChanged())
    {
        preferences.putString(password.Name(), password);
    }

    Print();
}

void WiFiSettings::Print()
{
    Serial.print("Enabled: ");
    Serial.println(enabled);

    Serial.print("Hostname: ");
    Serial.println(hostname);

    Serial.print("Ssid: ");
    Serial.println(ssid);

    Serial.print("Password: ");
    Serial.println(password);
}