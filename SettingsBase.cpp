//******************************************************
// Includes
//******************************************************

#include <Arduino.h>

#include "SettingsBase.h"

//******************************************************
// Public Methods
//******************************************************

bool SettingsBase::Init()
{
    Serial.print(name);
    Serial.print(".Init()");

    if (!preferences.begin(name))
    {
        Serial.println(" Preferences.begin() returned false");
        return false;
    }

    OnInit();
    preferences.end();
    Serial.println(" Done");
    return true;
}

bool SettingsBase::SetDefault()
{
    Serial.print(name);
    Serial.print(".SetDefault()");

    if (!preferences.begin(name))
    {

        Serial.println(" Preferences.begin() returned false");
        return false;
    }

    OnSetDefault();
    preferences.end();
    Serial.println(" Done");
    return true;
}

bool SettingsBase::Reload()
{
    Serial.print(name);
    Serial.print(".Reload()");

    if (!preferences.begin(name))
    {

        Serial.println(" Preferences.begin() returned false");
        return false;
    }

    OnReload();
    preferences.end();
    Serial.println(" Done");
    return true;
}

bool SettingsBase::Save(bool forceSave)
{
    Serial.print(name);
    Serial.print(".Save()");

    if (forceSave || HasChanged())
    {
        if (!preferences.begin(name))
        {
            Serial.println(" Preferences.begin() returned false");
            return false;
        }

        OnSave();
        preferences.end();
        Serial.println(" Done");
    }
    else
        Serial.println(" nothing to save");

    return true;
}