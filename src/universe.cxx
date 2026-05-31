/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#include "universe.h"

#include "error.h"
#include "macros.h"

#include <cstdio>
#include <format>
#include <regex>
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
  // Initialize output file handles

  console_default = "stdout";
  logfile_default = "ko.log";

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

void Universe::set_console(std::string arg)
{
  if (std::regex_match(arg, std::regex(console_default))) {
    console = stdout;
  } else {
    if (std::regex_match(arg, std::regex("none"))) {
      console = nullptr;
    } else {
      console = fopen(arg.c_str(), "w");
      if (console == nullptr) {
        error->fatal(FLERR, std::format("Could not open the console {}", arg));
      }
    }
  }
}

// -------------------------------------------------------------------------- //

void Universe::set_logfile(std::string arg)
{
  if (std::regex_match(arg, std::regex(logfile_default))) {
    logfile = fopen(arg.c_str(), "w");
    if (logfile == nullptr) {
      error->fatal(FLERR, std::format("Could not open the log file {}", arg));
    }
  } else {
    if (std::regex_match(arg, std::regex("none"))) {
      logfile = nullptr;
    } else {
      logfile = fopen(arg.c_str(), "w");
      if (logfile == nullptr) {
        error->fatal(FLERR, std::format("Could not open the log file {}", arg));
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
