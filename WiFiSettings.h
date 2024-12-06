#pragma once

//******************************************************
// Includes
//******************************************************

#include <SettingsGroup.h>
#include <string>

//******************************************************
// Classes
//******************************************************

class WiFiSettings : public SettingsGroup
{
private:
    Setting<bool> enabled = Setting<bool>("enabled");
    Setting<std::string> hostname = Setting<std::string>("hostname");
    Setting<std::string> ssid = Setting<std::string>("ssid");
    Setting<std::string> password = Setting<std::string>("password");

protected:
    virtual void OnInit() override;
    virtual void OnSetDefault() override;
    virtual void OnSave() override;

    virtual void Print() override;

public:
    WiFiSettings(const char *name, bool defaultEnabled = false, std::string defaultHostname = std::string(), std::string defaultSsid = std::string(), std::string defaultPassword = std::string());

    Setting<bool>& Enabled() { return enabled; }

    bool Valid();

    Setting<std::string>& Hostname() { return hostname; }
    Setting<std::string>& Ssid() { return ssid; }
    Setting<std::string>& Password() { return password; }
};
