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

    auto set_console() -> void;
    auto set_console(std::string) -> void;

    auto set_logfile() -> void;
    auto set_logfile(std::string) -> void;

    auto console() const -> FILE * { return _console; }
    auto logfile() const -> FILE * { return _logfile; }

    auto omp_num_threads() const -> int { return _omp_num_threads; }

  private:

    FILE *_console;
    FILE *_logfile;

    int _omp_num_threads;

}; // class Universe
} // namespace KO_NS

#endif

// -------------------------------------------------------------------------- //
