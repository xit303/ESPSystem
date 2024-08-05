//******************************************************
// Includes
//******************************************************

#include <Arduino.h>

#include "SettingsGroup.h"

//******************************************************
// Public Methods
//******************************************************

bool SettingsGroup::Init()
{
    Serial.print(Name());
    Serial.println(".Init()");

    if (!preferences.begin(Name()))
    {
        Serial.println(" Preferences.begin() returned false");
        return false;
    }

    OnInit();
    preferences.end();
    Serial.println("Done");
    return true;
}

bool SettingsGroup::SetDefault()
{
    Serial.print(Name());
    Serial.println(".SetDefault()");

    if (!preferences.begin(Name()))
    {
        Serial.println(" Preferences.begin() returned false");
        return false;
    }

    OnSetDefault();
    preferences.end();
    Serial.println("Done");
    return true;
}

bool SettingsGroup::Save(bool forceSave)
{
    Serial.print(Name());
    Serial.println(".Save()");

    if (forceSave || HasChanged())
    {
        if (!preferences.begin(Name()))
        {
            Serial.println(" Preferences.begin() returned false");
            return false;
        }

        OnSave();
        ISettingsGroup::Save();
        preferences.end();
        Serial.println("Done");
    }
    else
        Serial.println("nothing to save");

    return true;
}