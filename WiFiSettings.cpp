//******************************************************
// Includes
//******************************************************

#include "WiFiSettings.h"

//******************************************************
// Public Methods
//******************************************************

WiFiSettings::WiFiSettings(const char *name, bool defaultEnabled, String defaultHostname, String defaultSsid, String defaultPassword)
    : SettingsBase(name)
{
    this->defaultEnabled = defaultEnabled;
    this->defaultHostname = defaultHostname;
    this->defaultSsid = defaultSsid;
    this->defaultPassword = defaultPassword;
}

bool WiFiSettings::HasChanged()
{
    return enabled != loadedEnabled ||
           hostname != loadedHostname ||
           ssid != loadedSsid ||
           password != loadedPassword;
}

bool WiFiSettings::Valid()
{
    if (hostname.isEmpty() || ssid.isEmpty())
        return false;

    // we do not check the password because it can be empty on an open network
    return true;
}

//******************************************************
// Protected Methods
//******************************************************

void WiFiSettings::OnInit()
{
    loadedEnabled = enabled = preferences.getBool("enabled", defaultEnabled);
    loadedHostname = hostname = preferences.getString("hostname", defaultHostname);
    loadedSsid = ssid = preferences.getString("ssid", defaultSsid);
    loadedPassword = password = preferences.getString("password", defaultPassword);

    Print();
}

void WiFiSettings::OnSetDefault()
{
    loadedEnabled = enabled = defaultEnabled;
    loadedHostname = hostname = defaultHostname;
    loadedSsid = ssid = defaultSsid;
    loadedPassword = password = defaultPassword;

    preferences.remove("enabled");
    preferences.remove("hostname");
    preferences.remove("ssid");
    preferences.remove("password");
}

void WiFiSettings::OnReload()
{
    enabled = loadedEnabled;
    hostname = loadedHostname;
    ssid = loadedSsid;
    password = loadedPassword;
}

void WiFiSettings::OnSave()
{
    if (enabled != loadedEnabled)
    {
        loadedEnabled = enabled;
        preferences.putBool("enabled", enabled);
    }

    if (hostname != loadedHostname)
    {
        loadedHostname = hostname;
        preferences.putString("hostname", hostname);
    }

    if (ssid != loadedSsid)
    {
        loadedSsid = ssid;
        preferences.putString("ssid", ssid);
    }

    if (password != loadedPassword)
    {
        loadedPassword = password;
        preferences.putString("password", password);
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