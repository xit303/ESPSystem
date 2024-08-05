#pragma once

//******************************************************
// Includes
//******************************************************

#include <Preferences.h>
#include "ISettingsGroup.h"
#include "Setting.h"

//******************************************************
// Classes
//******************************************************

class SettingsGroup : public ISettingsGroup
{
protected:
    Preferences preferences;

    virtual void OnInit() = 0;
    virtual void OnSetDefault() = 0;
    virtual void OnSave() = 0;
    virtual void Print() {};

public:
    SettingsGroup(const char *name) : ISettingsGroup(name) {}

    virtual bool Init() override;
    virtual bool SetDefault() override;
    virtual bool Save(bool forceSave = false) override;
    virtual void Update() override {}
};