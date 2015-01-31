/* ----------------------------------------------------------------------------

   Squeezer
   ========
   Flexible general-purpose audio compressor with a touch of lemon.

   Copyright (c) 2013-2015 Martin Zuther (http://www.mzuther.de/)

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

#ifndef __FILTER_CHEBYSHEV_STAGE_H__
#define __FILTER_CHEBYSHEV_STAGE_H__

#include "../JuceLibraryCode/JuceHeader.h"
#include <float.h>


static const float  fAntiDenormal = FLT_MIN;
static const double dAntiDenormal = DBL_MIN;

//============================================================================
class FilterChebyshevStage
{
public:
    //==========================================================================

    FilterChebyshevStage(double dRelativeCutoffFrequency, bool isHighPass, double dPercentRipple, int nNumberOfPoles, int nPolePair);
    ~FilterChebyshevStage();

    void changeParameters(double dRelativeCutoffFrequency, bool isHighPass, double dPercentRipple, int nNumberOfPoles, int nPolePair);
    double filterSample(double dInputCurrent);
    void reset();

    juce_UseDebuggingNewOperator
private:
    JUCE_LEAK_DETECTOR(FilterChebyshevStage);

    double coeff_A0;
    double coeff_A1;
    double coeff_A2;
    double coeff_B1;
    double coeff_B2;

    double dInputPrevious_1;
    double dInputPrevious_2;

    double dOutputPrevious_1;
    double dOutputPrevious_2;
};

#endif  // __FILTER_CHEBYSHEV_STAGE_H__


// Local Variables:
// ispell-local-dictionary: "british"
// End:
