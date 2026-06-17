/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#ifndef POINTERS_H
#define POINTERS_H

#include "ko.h"
#include "macros.h"

namespace KO_NS {

class Pointers {

  public:

    Pointers(KO *ptr) :
      ko(ptr),
      memory(ptr->memory),
      error(ptr->error),
      universe(ptr->universe),
      input(ptr->input) {}

  protected:

    KO *ko;
    Memory *&memory;
    Error *&error;
    Universe *&universe;
    Input *&input;

}; // class POINTERS
} // namespace KO_NS

#endif

// -------------------------------------------------------------------------- //
