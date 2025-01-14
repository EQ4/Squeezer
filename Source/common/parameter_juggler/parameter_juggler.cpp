/* ----------------------------------------------------------------------------

   MZ common JUCE
   ==============
   Common classes for use with the JUCE library

   Copyright (c) 2010-2015 Martin Zuther (http://www.mzuther.de/)

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

   Thank you for using free software!

---------------------------------------------------------------------------- */

#include "parameter_juggler.h"


// The methods of this class may be called on the audio thread, so
// they are absolutely time-critical!

/// Constructor.
///
/// @param settingsID parameter file ID (unique for every plug-in)
///
/// @param completeParameters number of parameters (hidden and revealed)
///
/// @param revealedParameters number of revealed parameters
///
ParameterJuggler::ParameterJuggler(const String &settingsID, int completeParameters, int revealedParameters)
{
    // store parameter file ID
    jugglerID = settingsID;

    // store number of parameters
    numberOfParameters = completeParameters;
    numberOfRevealedParameters = revealedParameters;
}


/// Destructor.
///
ParameterJuggler::~ParameterJuggler()
{
    // loop over plug-in parameters
    while (arrParameters.size())
    {
        // pop first parameter
        PluginParameter *parameter = arrParameters.remove(0);

        // do not delete elements of combined parameters!
        if (!parameter->saveFromDeletion())
        {
            delete parameter;
            parameter = nullptr;
        }
    }

    // clear arrays
    arrParameters.clear();
    arrMayModify.clear();
}


/// Check parameter index and whether the parameter may be modified.
/// Throws an assertion should an assumption not be fulfilled.
/// Calling this method in RELASE mode is a waste of time as it will
/// do absolutely NOTHING.
///
/// @param index parameter index
///
/// @param wantModification check whether the parameter may be modified
///
void ParameterJuggler::assertParameter(int index, bool wantModification)
{
    // check parameter index
    jassert(index >= 0);
    jassert(index < arrParameters.size());

    // check whether the parameter may be modified
    if (wantModification)
    {
        jassert(arrMayModify[index]);
    }
}


/// Get pointer to plug-in parameter.  **Do not delete this pointer!**
///
/// @param index parameter index
///
/// @return pointer to requested PluginParameter instance
///
PluginParameter *ParameterJuggler::getPluginParameter(int index)
{
#ifdef DEBUG
    assertParameter(index, false);
#endif

    return arrParameters[index];
}


/// Format all plug-in parameters.
///
/// @return String containing all plug-in parameters and their values
///
String ParameterJuggler::toString()
{
    String strParameters;

    // loop over plug-in parameters
    for (int n = 0; n < arrParameters.size(); n++)
    {
        // add parameter name
        strParameters += arrParameters[n]->getName() + ":  ";

        // add parameter value
        strParameters += arrParameters[n]->getText() + "\n";
    }

    return strParameters;
}


/// Get number of plug-in parameters.
///
/// @param includeHiddenParameters count hidden parameters that cannot
///        be automated
///
/// @return number of plug-in parameters
///
int ParameterJuggler::getNumParameters(bool includeHiddenParameters)
{
    // check that all intended parameters have been added
    jassert(numberOfParameters == arrParameters.size());

    if (includeHiddenParameters)
    {
        return numberOfParameters;
    }
    else
    {
        return numberOfRevealedParameters;
    }
}


/// Add plug-in parameter to container.
///
/// @param parameter pointer to plug-in parameter instance
///
/// @param index parameter index (must point to the end of the array
///        and is used for sanity checking only)
///
void ParameterJuggler::add(PluginParameter *parameter, int index)
{
    // add parameter to container
    arrParameters.add(parameter);

    // parameter is writeable
    arrMayModify.add(true);

    // check whether index of parameter is correct
    jassert(arrParameters.size() == index + 1);
}


/// Add **read-only** plug-in parameter to container.
///
/// @param parameter pointer to plug-in parameter instance
///
/// @param index parameter index (must point to the end of the array
///        and is used for sanity checking only)
///
void ParameterJuggler::addProtected(PluginParameter *parameter, int index)
{
    // add parameter to container
    add(parameter, index);

    // parameter is read-only
    arrMayModify.set(index, false);
}


/// Add **combined** plug-in parameter to container.
///
/// @param parameter pointer to plug-in parameter instance
///
/// @param switchIndex index of parameter switch (must point to the
///        end of the array and is used for sanity checking only)
///
/// @param parameterIndex index of parameter (must be **switchIndex** + 1
///        and is used for sanity checking only)
///
void ParameterJuggler::addCombined(PluginParameterCombined *parameter, int switchIndex, int parameterIndex)
{
    jassert(parameterIndex == (switchIndex + 1));

    // add parameter switch to container
    addProtected(parameter->getModeSwitch(), switchIndex);

    // add parameter to container
    add(parameter, parameterIndex);
}


/// Get parameter's name.
///
/// @param index parameter index
///
/// @return parameter name
///
String ParameterJuggler::getName(int index)
{
#ifdef DEBUG
    assertParameter(index, false);
#endif

    return arrParameters[index]->getName();
}


/// Set parameter's name.
///
/// @param index parameter index
///
/// @param newParameterName new parameter name
///
void ParameterJuggler::setName(int index, const String &newParameterName)
{
#ifdef DEBUG
    assertParameter(index, true);
#endif

    arrParameters[index]->setName(newParameterName);
}


/// Get **internal** default value as float.  Values range from 0.0 to
/// 1.0.
///
/// @param index parameter index
///
/// @return internal default value (between 0.0 and 1.0)
///
float ParameterJuggler::getDefaultFloat(int index)
{
#ifdef DEBUG
    assertParameter(index, false);
#endif

    return arrParameters[index]->getDefaultFloat();
}


/// Get **real** default value as float.  Values range from the
/// parameter's minimum value to its maximum value.
///
/// @param index parameter index
///
/// @return default value
///
float ParameterJuggler::getDefaultRealFloat(int index)
{
#ifdef DEBUG
    assertParameter(index, false);
#endif

    return arrParameters[index]->getDefaultRealFloat();
}


/// Get default value as Boolean.
///
/// @param index parameter index
///
/// @return **false** if the default value is set to the parameter's
///         minimum, **true** otherwise
///
bool ParameterJuggler::getDefaultBoolean(int index)
{
#ifdef DEBUG
    assertParameter(index, false);
#endif

    return arrParameters[index]->getDefaultBoolean();
}


/// Get **real** default value as integer.  Values range from the
/// parameter's (rounded) minimum value to its (rounded) maximum
/// value.
///
/// @param index parameter index
///
/// @return default value
///
int ParameterJuggler::getDefaultRealInteger(int index)
{
#ifdef DEBUG
    assertParameter(index, false);
#endif

    return arrParameters[index]->getDefaultRealInteger();
}


/// Set **real** default value from float.  The new value must be in
/// the defined range of the parameter's values.
///
/// @param index parameter index
///
/// @param newRealValue new default value
///
/// @param updateParameter if this is true, the parameter's value will
///        be set to the new default value
///
void ParameterJuggler::setDefaultRealFloat(int index, float newRealValue, bool updateParameter)
{
#ifdef DEBUG
    assertParameter(index, true);
#endif

    arrParameters[index]->setDefaultRealFloat(newRealValue, updateParameter);
}


/// Get **internal** parameter value as float.  Values range from 0.0
/// to 1.0.
///
/// @param index parameter index
///
/// @return current value (between 0.0 and 1.0)
///
float ParameterJuggler::getFloat(int index)
{
#ifdef DEBUG
    assertParameter(index, false);
#endif

    return arrParameters[index]->getFloat();
}


/// Set **internal** parameter value from float.  The new value must
/// be in the range from 0.0 to 1.0.
///
/// @param index parameter index
///
/// @param newValue new value (between 0.0 and 1.0)
///
void ParameterJuggler::setFloat(int index, float newValue)
{
#ifdef DEBUG
    assertParameter(index, true);
#endif

    arrParameters[index]->setFloat(newValue);
}


/// Get **real** parameter value as float.  Values range from the
/// parameter's minimum value to its maximum value.
///
/// @param index parameter index
///
/// @return current value
///
float ParameterJuggler::getRealFloat(int index)
{
#ifdef DEBUG
    assertParameter(index, false);
#endif

    return arrParameters[index]->getRealFloat();
}


/// Set **real** parameter value from float.  The new value must be in
/// the defined range of the parameter's values.
///
/// @param index parameter index
///
/// @param newRealValue new value
///
void ParameterJuggler::setRealFloat(int index, float newRealValue)
{
#ifdef DEBUG
    assertParameter(index, true);
#endif

    arrParameters[index]->setRealFloat(newRealValue);
}


/// Get **real** parameter value as integer.  Values range from the
/// (rounded) parameter's minimum value to its (rounded) maximum
/// value.
///
/// @param index parameter index
///
/// @return current value
///
int ParameterJuggler::getRealInteger(int index)
{
#ifdef DEBUG
    assertParameter(index, false);
#endif

    return arrParameters[index]->getRealInteger();
}


/// Set **real** parameter value from integer.  The new value must be
/// in the defined range of the parameter's values.
///
/// @param index parameter index
///
/// @param newRealValue new value
///
void ParameterJuggler::setRealInteger(int index, int newRealValue)
{
#ifdef DEBUG
    assertParameter(index, true);
#endif

    arrParameters[index]->setRealInteger(newRealValue);
}


/// Get parameter value as Boolean.
///
/// @param index parameter index
///
/// @return **false** if current value is at its minimum, **true**
///         otherwise
///
bool ParameterJuggler::getBoolean(int index)
{
#ifdef DEBUG
    assertParameter(index, false);
#endif

    return arrParameters[index]->getBoolean();
}


/// Get parameter value as formatted string.
///
/// @param index parameter index
///
/// @return current value
///
String ParameterJuggler::getText(int index)
{
#ifdef DEBUG
    assertParameter(index, false);
#endif

    return arrParameters[index]->getText();
}


/// Set parameter value from (correctly) formatted string.
///
/// @param index parameter index
///
/// @param newValue new value as formatted string
///
void ParameterJuggler::setText(int index, const String &newValue)
{
#ifdef DEBUG
    assertParameter(index, true);
#endif

    arrParameters[index]->setText(newValue);
}


/// Get parameter's change flag.  Determines whether the parameter has
/// changed since the last time the change flag was reset.
///
/// @param index parameter index
///
/// @return change flag
///
bool ParameterJuggler::hasChanged(int index)
{
#ifdef DEBUG
    assertParameter(index, false);
#endif

    return arrParameters[index]->hasChanged();
}


/// Mark parameter as unchanged.
///
/// @param index parameter index
///
void ParameterJuggler::clearChangeFlag(int index)
{
#ifdef DEBUG
    assertParameter(index, false);
#endif

    return arrParameters[index]->clearChangeFlag();
}


/// Load all parameter values from XML.
///
/// @param xmlDocument XML document to load from
///
void ParameterJuggler::loadFromXml(XmlElement *xmlDocument)
{
    // check ID of XML document
    if (xmlDocument && xmlDocument->hasTagName(jugglerID))
    {
        // loop over plug-in parameters
        for (int n = 0; n < arrParameters.size(); n++)
        {
            // only load values of writeable parameters
            if (arrMayModify[n])
            {
                // load parameter value
                arrParameters[n]->loadFromXml(xmlDocument);
            }
        }
    }
}


/// Store all parameter values as XML.
///
/// @param xmlDocument XML document to store in
///
XmlElement ParameterJuggler::storeAsXml()
{
    // create XML document
    XmlElement xmlDocument(jugglerID);

    // set plug-in version
    xmlDocument.setAttribute("version", JucePlugin_VersionString);

    // loop over plug-in parameters
    for (int n = 0; n < arrParameters.size(); n++)
    {
        // only store writeable parameters
        if (arrMayModify[n])
        {
            // store parameter value
            arrParameters[n]->storeAsXml(&xmlDocument);
        }
    }

    // return XML document (will be deleted by the caller)
    return xmlDocument;
}


// Local Variables:
// ispell-local-dictionary: "british"
// End:
