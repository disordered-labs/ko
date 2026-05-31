/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#include "universe.h"

#include "error.h"
#include "macros.h"

#include <cstdlib>
#include <cstdio>
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

Universe::Universe()
{
  // Default output file handles

  console_default = "stdout";
  logfile_default = "ko.log";

  // Initialize output file handles

  console = stdout;
  logfile = nullptr;

  // Initialize the use of OMP THREADS

#if defined(_OPENMP)
  if (getenv("OMP_NUM_THREADS") == nullptr) {
    omp_num_threads = 1;
  } else {
    omp_num_threads = omp_get_max_threads();
  }
  omp_set_num_threads(omp_num_threads);
#else
  omp_num_threads = 0;
#endif
}

// -------------------------------------------------------------------------- //


/* --------------------------------------------------------------------------
   Public functions
   -------------------------------------------------------------------------- */


// -------------------------------------------------------------------------- //

auto Universe::set_console(std::string value) -> void
{
  if (value == console_default) {
    console = stdout;
  } else {
    if (value == "none") {
      console = nullptr;
    } else {
      console = fopen(value.c_str(), "w");
      if (console == nullptr) {
        error->fatal(FLERR, std::format("Could not open the console {}", value));
      }
    }
  }
}

// -------------------------------------------------------------------------- //

auto Universe::set_logfile(std::string value) -> void
{
  if (value == logfile_default) {
    logfile = fopen(value.c_str(), "w");
    if (logfile == nullptr) {
      error->fatal(FLERR, std::format("Could not open the log file {}", value));
    }
  } else {
    if (value == "none") {
      logfile = nullptr;
    } else {
      logfile = fopen(value.c_str(), "w");
      if (logfile == nullptr) {
        error->fatal(FLERR, std::format("Could not open the log file {}", value));
      }
    }
  }
}

// -------------------------------------------------------------------------- //


/* --------------------------------------------------------------------------
   Private functions
   -------------------------------------------------------------------------- */


// -------------------------------------------------------------------------- //


// -------------------------------------------------------------------------- //
