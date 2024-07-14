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
    SettingsBase(const char* name) : ISettingsBase(name) {}

    virtual bool HasChanged() = 0;

    virtual bool Init() override
    {
        if (preferences.begin(name))
        {
            Serial.printf("Loading settings for %s\n", name);
            OnInit();
            preferences.end();
            return true;    
        }
        else
        {
            Serial.printf("Could not load settings for %s. Preferences.begin() was FALSE\n", name);
        }
        
        return false;
    }

    void SetDefault()
    {
        if (preferences.begin(name))
        {
            OnSetDefault();
            preferences.end();
        }
    }

    void Reload()
    {
        if (preferences.begin(name))
        {
            OnReload();
            preferences.end();
        }
    }

    void Save()
    {
        if (HasChanged())
        {
            if (preferences.begin(name))
            {
                Serial.print(name);
                Serial.println(" saving...");
                OnSave();
                Serial.print(name);
                Serial.println(" saved");
            }
            else
            {
                Serial.print(name);
                Serial.println(" Preferences.begin() returned false");
            }
        }
    }

    virtual void Update() override {}
};