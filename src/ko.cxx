/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#include "ko.h"

#include "error.h"
#include "macros.h"
#include "memory.h"
#include "universe.h"
#include "version.h"

#include <cstdlib>
#include <format>
#include <memory>
#include <print>
#include <regex>
#include <string>
#include <string_view>

// -------------------------------------------------------------------------- //

using namespace KO_NS;

// -------------------------------------------------------------------------- //


/* --------------------------------------------------------------------------
   Special member functions
   -------------------------------------------------------------------------- */


// -------------------------------------------------------------------------- //

KO::KO(int argc, char **argv)
{
  std::string arg, mesg;
  int iarg, shift;
  int console_flag, echo_flag, help_flag, input_flag, logfile_flag;

  // Initialize fundamental classes

  memory = std::make_unique<Memory>();
  error = std::make_unique<Error>();
  universe = std::make_unique<Universe>();

  // Process command-line arguments with error checking

  console_flag = 0;
  echo_flag = 0;
  help_flag = 0;
  input_flag = 0;
  logfile_flag = 0;

  iarg = 1;
  while (iarg < argc) {
    arg = argv[iarg];
    if (std::regex_match(arg, std::regex("-{1,2}c(onsole)?"))) {
      shift = 2;
      if (iarg + shift > argc) {
        error->fatal(FLERR, "Invalid command-line argument");
      }
      console_flag = iarg + 1;
      iarg += shift;
    } else if (std::regex_match(arg, std::regex("-{1,2}e(cho)?"))) {
      shift = 2;
      if (iarg + shift > argc) {
        error->fatal(FLERR, "Invalid command-line argument");
      }
      echo_flag = iarg + 1;
      iarg += shift;
    } else if (std::regex_match(arg, std::regex("-{1,2}h(elp)?"))) {
      shift = 1;
      if (iarg + shift > argc) {
        error->fatal(FLERR, "Invalid command-line argument");
      }
      help_flag = 1;
      iarg += shift;
    } else if (std::regex_match(arg, std::regex("-{1,2}i(nput)?"))) {
      shift = 2;
      if (iarg + shift > argc) {
        error->fatal(FLERR, "Invalid command-line argument");
      }
      input_flag = iarg + 1;
      iarg += shift;
    } else if (std::regex_match(arg, std::regex("-{1,2}l(ogfile)?"))) {
      shift = 2;
      if (iarg + shift > argc) {
        error->fatal(FLERR, "Invalid command-line argument");
      }
      logfile_flag = iarg + 1;
      iarg += shift;
    } else {
      error->fatal(FLERR, "Invalid command-line argument");
    }
  }

  // Post-processing configuration

  if (console_flag) {
    universe->set_console(argv[console_flag]);
  } else {
    universe->set_console(universe->console_default);
  }

  if (logfile_flag) {
    universe->set_logfile(argv[logfile_flag]);
  } else {
    universe->set_logfile(universe->logfile_default);
  }

  if ((!input_flag) && (!help_flag)) {
    error->fatal(FLERR, "The --input command-line option was not found");
  } else {
    input = std::make_unique<Input>(argc, argv);
  }

  // Startup information to console and logfile

  mesg = std::format("KO ({})\n", KO_VERSION);

  if (universe->console) {
    std::print(universe->console, "{}", mesg);
  }

  if (universe->logfile) {
    std::print(universe->logfile, "{}", mesg);
  }

  // If help_flag is set, print help message and exit with success status

  if (help_flag) {
    help(argv[0]);
    error->done(EXIT_SUCCESS);
  }
}

// -------------------------------------------------------------------------- //


/* --------------------------------------------------------------------------
   Public functions
   -------------------------------------------------------------------------- */


// -------------------------------------------------------------------------- //


/* --------------------------------------------------------------------------
   Private functions
   -------------------------------------------------------------------------- */


// -------------------------------------------------------------------------- //

void KO::help(std::string_view exename)
{
  std::string mesg = std::format(
  "\nKO - Computer Simulation of Dynamic Phenomena\n\n"
  "General usage:\n\n"
  "  {} --input <filename> [options]\n\n"
  "Usage example:\n\n"
  "  {} --input ko.inp\n\n"
  "List of command-line options:\n\n"
  "  -c, --console <none/filename>           : where to send console output (default: stdout)\n"
  "  -e, --echo <both/console/logfile/none>  : echoing of input script (default: logfile)\n"
  "  -h, --help                              : print this help message\n"
  "  -i, --input <filename>                  : read input from filename (no default)\n"
  "  -l, --logfile <none/filename>           : where to send logfile output (default: ko.log)\n"
  "\n", exename, exename);

  std::print(universe->console, "{}", mesg);
}

// -------------------------------------------------------------------------- //
