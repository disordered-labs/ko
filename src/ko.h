/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#ifndef KO_H
#define KO_H

#include <memory>
#include <string_view>

namespace KO_NS {

class Memory;

class KO {

  public:

    class Memory *memory;
    class Error *error;
    class Universe *universe;
    class Input *input;

  public:

    KO(int, char **);
    ~KO();

    auto run() -> void;

  private:

    auto create() -> void;
    auto help(std::string_view) -> void;

}; // class KO
} // namespace KO_NS

#endif

// -------------------------------------------------------------------------- //
