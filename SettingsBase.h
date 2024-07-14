#pragma once

//******************************************************
// Includes
//******************************************************

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

    virtual bool Init() override;
    virtual bool SetDefault() override;
    virtual bool Reload() override;
    virtual bool Save(bool forceSave = false) override;
    virtual void Update() override {}
};