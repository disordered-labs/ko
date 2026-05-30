/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#include "ko.h"

#include "error.h"
#include "macros.h"
#include "universe.h"
#include "version.h"

#include <format>
#include <memory>
#include <print>
#include <regex>
#include <string>

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
  int console_flag, echo_flag, help_flag, input_flag, logfile_flag, nobuffer_flag;

  // Initialize fundamental classes

  error = std::make_unique<Error>();
  universe = std::make_unique<Universe>();

  // Process command-line arguments

  console_flag = 0;
  echo_flag = 0;
  help_flag = 0;
  input_flag = 0;
  logfile_flag = 0;
  nobuffer_flag = 0;

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
    } else if (std::regex_match(arg, std::regex("-{1,2}i(n(put)?)?"))) {
      shift = 2;
      if (iarg + shift > argc) {
        error->fatal(FLERR, "Invalid command-line argument");
      }
      input_flag = iarg + 1;
      iarg += shift;
    } else if (std::regex_match(arg, std::regex("-{1,2}l(og(file)?)?"))) {
      shift = 2;
      if (iarg + shift > argc) {
        error->fatal(FLERR, "Invalid command-line argument");
      }
      logfile_flag = iarg + 1;
      iarg += shift;
    } else if (std::regex_match(arg, std::regex("--no-buffer"))) {
      shift = 1;
      if (iarg + shift > argc) {
        error->fatal(FLERR, "Invalid command-line argument");
      }
      nobuffer_flag = 1;
      iarg += shift;
    } else {
      error->fatal(FLERR, "Invalid command-line argument");
    }
  }

  // Configure the console and logfile

  if (!console_flag) {
    universe->console = stdout;
  } else {
    arg = argv[console_flag];
    if (std::regex_match(arg, std::regex("none"))) {
      universe->console = nullptr;
    } else {
      universe->console = fopen(arg.c_str(), "w");
      if (universe->console == nullptr) {
        error->fatal(FLERR, std::format("Could not open the console file {}", arg));
      }
    }
  }

  if (!logfile_flag) {
    arg = "ko.log";
    universe->logfile = fopen(arg.c_str(), "w");
    if (universe->logfile == nullptr) {
      error->fatal(FLERR, std::format("Could not open the log file {}", arg));
    }
  } else {
    arg = argv[logfile_flag];
    if (std::regex_match(arg, std::regex("none"))) {
      universe->logfile = nullptr;
    } else {
      universe->logfile = fopen(arg.c_str(), "w");
      if (universe->logfile == nullptr) {
        error->fatal(FLERR, std::format("Could not open the log file {}", arg));
      }
    }
  }

  // Configure the console and logfile for unbuffered output

  if (nobuffer_flag) {
    if (universe->console) {
      setbuf(universe->console, nullptr);
    }
    if (universe->logfile) {
      setbuf(universe->logfile, nullptr);
    }
  }

  // Startup messages

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

  // Initialize the input class

  if (!input_flag) {
    error->fatal(FLERR, "The --input command-line option was not found");
  }
  input = std::make_unique<Input>(argc, argv);
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

void KO::help(char *exename)
{
}

// -------------------------------------------------------------------------- //
