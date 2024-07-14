#pragma once

//******************************************************
// Includes
//******************************************************

#include <Arduino.h>
#include <Preferences.h>
#include "ISettingsBase.h"

//******************************************************
// Classes
//******************************************************

class SettingsBase : public ISettingsBase
{
protected:
    Preferences preferences;

    virtual void OnInit() = 0;
    virtual void OnSetDefault() = 0;
    virtual void OnReload() = 0;
    virtual void OnSave() = 0;
    virtual void Print() {};

public:
    SettingsBase(const char *name) : ISettingsBase(name) {}

    virtual bool HasChanged() = 0;

    virtual bool Init() override
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

    virtual bool SetDefault() override
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

    virtual bool Reload() override
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

    virtual bool Save(bool forceSave = false) override
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

    virtual void Update() override {}
};