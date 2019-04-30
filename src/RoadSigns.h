/* created by Van Borm Joren & Bontenakel Lenny
 */

#include "Road.h"

#ifndef LNJPSE_PROJECT_ROADSIGNS_H
#define LNJPSE_PROJECT_ROADSIGNS_H

class RoadSign
{
public:

    RoadSign(const string& type, unsigned int position, Road* road);
    /** ---------------------------------------------------------------------
     * RoadSign
     *
     *  Postcondition:
     *      RoadSign is properly initialised.
     --------------------------------------------------------------------- */


    bool properlyInitialised() const;
    /** ---------------------------------------------------------------------
     * properlyInitialised
     *
     --------------------------------------------------------------------- */

    const string& getType() const;
    /** ---------------------------------------------------------------------
     * getType
     *
     *  Precondition:
     *      RoadSign properly initialised.
     --------------------------------------------------------------------- */


    const unsigned int getPosition() const;
    /** ---------------------------------------------------------------------
     * getPosition
     *
     *  Precondition:
     *      RoadSign properly initialised.
     --------------------------------------------------------------------- */


    Road* const getRoad() const;
    /** ---------------------------------------------------------------------
     * getRoad
     *
     *  Precondition:
     *      RoadSign properly initialised.
     --------------------------------------------------------------------- */
private:

    string type;
    unsigned int position;
    Road* road;
};

#endif //LNJPSE_PROJECT_ROADSIGNS_H
