/* ----------------------------------------------------------------------------

   Squeezer
   ========
   Flexible general-purpose audio compressor with a touch of lemon.

   Copyright (c) 2013 Martin Zuther (http://www.mzuther.de/)

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

#ifndef __OPTICAL_CELL_H__
#define __OPTICAL_CELL_H__

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class OpticalCell
{
public:
    OpticalCell(int nSampleRate);
    ~OpticalCell();

    void reset();
    float processGainReduction(float fGainReductionNew);

    static float level2decibel(float fLevel);
    static float decibel2level(float fDecibels);
private:
    JUCE_LEAK_DETECTOR(OpticalCell);

    float fSampleRate;
    float fGainReduction;

    float fAttackCoefficient;
    float fReleaseCoefficient;
};


#endif  // __OPTICAL_CELL_H__


// Local Variables:
// ispell-local-dictionary: "british"
// End:
