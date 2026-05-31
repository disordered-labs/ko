/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#ifndef KO_H
#define KO_H

#include "input.h"

#include <memory>
#include <string_view>

namespace KO_NS {

class KO {

  public:

    std::unique_ptr<Input> input;

  public:

    KO(int, char **);

  private:

    void help(std::string_view);

}; // class KO
} // namespace KO_NS

#endif

// -------------------------------------------------------------------------- //
