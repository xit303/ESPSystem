#pragma once

//******************************************************
// Includes
//******************************************************

#include <SettingsGroup.h>

//******************************************************
// Classes
//******************************************************

class WiFiSettings : public SettingsGroup
{
private:
    Setting<bool> enabled = Setting<bool>("enabled");
    Setting<String> hostname = Setting<String>("hostname");
    Setting<String> ssid = Setting<String>("ssid");
    Setting<String> password = Setting<String>("password");

protected:
    virtual void OnInit() override;
    virtual void OnSetDefault() override;
    virtual void OnSave() override;

    virtual void Print() override;

public:
    WiFiSettings(const char *name, bool defaultEnabled = false, String defaultHostname = String(), String defaultSsid = String(), String defaultPassword = String());

    Setting<bool>& Enabled() { return enabled; }

    bool Valid();

    Setting<String>& Hostname() { return hostname; }
    Setting<String>& Ssid() { return ssid; }
    Setting<String>& Password() { return password; }
};
