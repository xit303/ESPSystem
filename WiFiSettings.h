#pragma once

//******************************************************
// Includes
//******************************************************

#include "SettingsBase.h"

//******************************************************
// Classes
//******************************************************

class WiFiSettings : public SettingsBase
{
private:
    bool enabled;
    bool loadedEnabled;
    bool defaultEnabled;

    String hostname;
    String loadedHostname;
    String defaultHostname;

    String ssid;
    String loadedSsid;
    String defaultSsid;

    String password;
    String loadedPassword;
    String defaultPassword;

protected:
    virtual void OnInit() override;
    virtual void OnSetDefault() override;
    virtual void OnReload() override;
    virtual void OnSave() override;

    virtual void Print() override;

public:
    WiFiSettings(const char *name, bool defaultEnabled = false, String defaultHostname = String(), String defaultSsid = String(), String defaultPassword = String());

    virtual bool HasChanged() override;

    void Enabled(bool value) { enabled = value; }
    bool Enabled() { return enabled; }

    bool Valid();

    void Hostname(String &value) { hostname = value; }
    String Hostname() { return hostname; }

    void Ssid(String &value) { ssid = value; }
    String Ssid() { return ssid; }

    void Password(String &value) { password = value; }
    String Password() { return password; }
};
