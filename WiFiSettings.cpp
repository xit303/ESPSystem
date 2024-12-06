//******************************************************
// Includes
//******************************************************

#include "WiFiSettings.h"

//******************************************************
// Public Methods
//******************************************************

WiFiSettings::WiFiSettings(const char *name, bool defaultEnabled, std::string defaultHostname, std::string defaultSsid, std::string defaultPassword)
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
    std::string host = hostname;
    std::string ssi = ssid;
    if (host.empty() || !ssi.empty())
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

    String s = preferences.getString(hostname.Name(), hostname.DefaultValue().c_str());
    hostname.LoadedValue(s.c_str());
    settings.push_back(&hostname);

    s = preferences.getString(ssid.Name(), ssid.DefaultValue().c_str());
    ssid.LoadedValue(s.c_str());
    settings.push_back(&ssid);

    s = preferences.getString(password.Name(), password.DefaultValue().c_str());
    password.LoadedValue(s.c_str());
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
        preferences.putString(hostname.Name(), hostname.Value().c_str());
    }

    if (ssid.HasChanged())
    {
        preferences.putString(ssid.Name(), ssid.Value().c_str());
    }

    if (password.HasChanged())
    {
        preferences.putString(password.Name(), password.Value().c_str());
    }

    Print();
}

void WiFiSettings::Print()
{
    Serial.print("Enabled: ");
    Serial.println(enabled.Value());

    Serial.print("Hostname: ");
    Serial.println(hostname.Value().c_str());

    Serial.print("Ssid: ");
    Serial.println(ssid.Value().c_str());

    Serial.print("Password: ");
    Serial.println(password.Value().c_str());
}