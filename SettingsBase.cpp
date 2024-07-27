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
    Serial.print(Name());
    Serial.print(".Init()");

    if (!preferences.begin(Name()))
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
    Serial.print(Name());
    Serial.print(".SetDefault()");

    if (!preferences.begin(Name()))
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
    Serial.print(Name());
    Serial.print(".Reload()");

    if (!preferences.begin(Name()))
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
    Serial.print(Name());
    Serial.print(".Save()");

    if (forceSave || HasChanged())
    {
        if (!preferences.begin(Name()))
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