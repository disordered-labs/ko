/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#ifndef POINTERS_H
#define POINTERS_H

#include "ko.h"

namespace KO_NS {

class Pointers {

  public:

    Pointers(KO *ptr) :
      ko(ptr),
      memory(ptr->memory),
      error(ptr->error),
      universe(ptr->universe),
      input(ptr->input) {}

    Pointers() = delete;
    Pointers(const Pointers &) = default;
    Pointers(Pointers &&) = delete;
    Pointers &operator=(const Pointers &) = delete;
    Pointers &operator=(Pointers &&) = delete;

  protected:

    KO *ko;
    Memory *&memory;
    Error *&error;
    Universe *&universe;
    Input *&input;

}; // class Pointers
} // namespace KO_NS

#endif

// -------------------------------------------------------------------------- //
