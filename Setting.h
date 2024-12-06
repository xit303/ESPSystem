#pragma once

//******************************************************
// Includes
//******************************************************

#include "ISetting.h"

//******************************************************
// Classes
//******************************************************

template <class T>
class Setting : public ISetting
{
private:
    T defaultValue;
    T value;
    T loadedValue;

    bool isLoadedValueSet;

    const T defaultT = T();

    bool IsValueDifferentTo(T valueToCheck)
    {
        if (valueToCheck == defaultT)
        {
            return value != defaultT;
        }
        else if (&valueToCheck == &value)
        {
            return false;
        }
        else if (valueToCheck == value)
        {
            return false;
        }

        return true;
    }

public:
    Setting(const char *name) : ISetting(name) {}

    /// <summary>
    ///
    /// </summary>
    T DefaultValue() { return defaultValue; }
    void DefaultValue(T value)
    {
        T lastDefaultValue = defaultValue;

        defaultValue = value;

        // initially set the value to the same as the defaultValue
        // if we did not load any value, we have to set Value
        // this ensures that Value will always be either the defaultValue or the loadedValue

        if (loadedValue == defaultT) // || loadedValue->Equals(default(T)))
        {
            // for the case that Value has been set somewhere else we do not write the new value

            if (this->value != defaultT)
            {
                if (lastDefaultValue == defaultT || this->value == lastDefaultValue)
                {
                    // setting Value instead of value triggers ValueChanged
                    Value(value);
                }
            }
            else
            {
                if (lastDefaultValue == defaultT)
                {
                    // setting Value instead of value triggers ValueChanged
                    Value(value);
                }
            }
        }
    }

    T Value() const { return value; };
    void Value(T value)
    {
        // TODO I really don't like this ... But in some cases (Brushes) value.Equals is not working
        if (this->value == defaultT || IsValueDifferentTo(value))
        {
            // Do not try to set defaultValue here if it is nullptr
            // Saving will no longer work in that case (initial empty strings which have changed etc)

            this->value = value;

            // EventArgs e;
            // ValueChanged(*this, e);
        }
    }

    T LoadedValue() { return loadedValue; }
    void LoadedValue(T value)
    {
        // loading the value has to set the working value
        loadedValue = value;
        isLoadedValueSet = true;
        this->Value(value);
    }

    bool HasChanged()
    {
        return !isLoadedValueSet
                   ? IsValueDifferentTo(defaultValue)
                   : IsValueDifferentTo(loadedValue);
    }

    virtual bool SetDefault() override
    {
        loadedValue = value = defaultValue;
        return true;
    }

    virtual bool Reload() override
    {
        value = loadedValue;
        return true;
    }

    virtual bool Save(bool forceSave = false) override
    {
        loadedValue = value;
        return true;
    }

    bool ShouldSerialize()
    {
        return IsValueDifferentTo(defaultValue);
    }

    operator T() const
    {
        return value;
    }

    void operator=(T other)
    {
        value = other;
    }
};