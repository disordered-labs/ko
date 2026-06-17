/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "pointers.h"

#include <cstdio>
#include <string>

namespace KO_NS {

class Universe : protected Pointers {

  public:

    Universe(class KO *);

  public:

    std::string console_default;
    std::string logfile_default;

    FILE *console;
    FILE *logfile;

    auto set_console(std::string) -> void;
    auto set_logfile(std::string) -> void;

  private:

    int omp_num_threads;

}; // class Universe
} // namespace KO_NS

#endif

// -------------------------------------------------------------------------- //
