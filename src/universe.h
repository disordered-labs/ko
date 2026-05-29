/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <cstdio>
#include <memory>

namespace KO_NS {

class Universe {

  public:

  Universe();

  public:

  FILE *console;
  FILE *logfile;

  private:

  int omp_num_threads;

}; // class Universe
inline std::unique_ptr<Universe> universe;
} // namespace KO_NS

#endif

// -------------------------------------------------------------------------- //
