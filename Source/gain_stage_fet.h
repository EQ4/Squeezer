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

#ifndef __GAIN_STAGE_FET_H__
#define __GAIN_STAGE_FET_H__

#include "JuceHeader.h"
#include "gain_stage.h"


//==============================================================================
/**
*/
class GainStageFET : virtual public GainStage
{
public:
    GainStageFET(int nSampleRate);
    ~GainStageFET();

    void reset(double dCurrentGainReduction);
    double processGainReduction(double dGainReductionNew, double dGainReductionIdeal);
private:
    JUCE_LEAK_DETECTOR(GainStageFET);

    double dGainReduction;
};


#endif  // __GAIN_STAGE_FET_H__


// Local Variables:
// ispell-local-dictionary: "british"
// End:
