/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#include "universe.h"

#include "error.h"
#include "macros.h"

#include <cstdio>
#include <cstdlib>
#include <format>
#include <string>

#if defined(_OPENMP)
#include <omp.h>
#endif

// -------------------------------------------------------------------------- //

using namespace KO_NS;

// -------------------------------------------------------------------------- //


/* --------------------------------------------------------------------------
   Special member functions
   -------------------------------------------------------------------------- */


// -------------------------------------------------------------------------- //

Universe::Universe(KO *ko) : Pointers(ko), _console(stdout), _logfile(nullptr)
{
  // Initialize the use of OMP THREADS

#if defined(_OPENMP)
  if (getenv("OMP_NUM_THREADS") == nullptr) {
    _omp_num_threads = 1;
  } else {
    _omp_num_threads = omp_get_max_threads();
  }
  omp_set_num_threads(_omp_num_threads);
#else
  _omp_num_threads = 0;
#endif
}

// -------------------------------------------------------------------------- //


/* --------------------------------------------------------------------------
   Public functions
   -------------------------------------------------------------------------- */


// -------------------------------------------------------------------------- //

auto Universe::set_console() -> void
{
  _console = stdout;
}

// -------------------------------------------------------------------------- //

auto Universe::set_console(std::string value) -> void
{
  if (value == "none") {
    _console = nullptr;
  } else {
    _console = fopen(value.c_str(), "w");
    if (_console == nullptr) {
      error->fatal(FLERR, std::format("Could not open the console {}", value));
    }
  }
}

// -------------------------------------------------------------------------- //

auto Universe::set_logfile() -> void
{
  _logfile = fopen("ko.log", "w");
  if (_logfile == nullptr) {
    error->fatal(FLERR, "Could not open the default logfile ko.log");
  }
}

// -------------------------------------------------------------------------- //

auto Universe::set_logfile(std::string value) -> void
{
  if (value == "none") {
    _logfile = nullptr;
  } else {
    _logfile = fopen(value.c_str(), "w");
    if (_logfile == nullptr) {
      error->fatal(FLERR, std::format("Could not open the log file {}", value));
    }
  }
}

// -------------------------------------------------------------------------- //


/* --------------------------------------------------------------------------
   Private functions
   -------------------------------------------------------------------------- */


// -------------------------------------------------------------------------- //


// -------------------------------------------------------------------------- //
