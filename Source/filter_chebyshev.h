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

#ifndef __FILTER_CHEBYSHEV_H__
#define __FILTER_CHEBYSHEV_H__

#include "filter_chebyshev_stage.h"
#include "../JuceLibraryCode/JuceHeader.h"

//============================================================================
class FilterChebyshev
{
public:
    //==========================================================================

    FilterChebyshev(float fRelativeCutoffFrequency, bool isHighPass, float fPercentRipple, int nNumberOfPoles);
    ~FilterChebyshev();

    double filterSample(double dInputCurrent);
    void changeParameters(float fRelativeCutoffFrequency, bool isHighPass);
    void reset();

    juce_UseDebuggingNewOperator
private:
    JUCE_LEAK_DETECTOR(FilterChebyshev);

    FilterChebyshevStage** pFilterStages;
    int nNumberOfStages;
    float fRipple;
    double dGainNormalise;
};

#endif  // __FILTER_CHEBYSHEV_H__


// Local Variables:
// ispell-local-dictionary: "british"
// End: