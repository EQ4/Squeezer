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

#ifndef __GENERIC_CHANNEL_SLIDER_H__
#define __GENERIC_CHANNEL_SLIDER_H__

#include "JuceHeader.h"


//==============================================================================
/**
*/
class GenericChannelSlider : public Slider
{
public:
    GenericChannelSlider(const String &componentName = String::empty);
    ~GenericChannelSlider();

    int getNumberOfChannels();
    void setNumberOfChannels(int nNumChannels);

    float getFloat();
    double getValueFromText(const String &strText);
    String getTextFromValue(double fValue);

private:
    JUCE_LEAK_DETECTOR(GenericChannelSlider);

    int nNumberOfChannels;
};


#endif  // __GENERIC_CHANNEL_SLIDER_H__


// Local Variables:
// ispell-local-dictionary: "british"
// End:
