/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#include "ko.h"

#include "error.h"
#include "macros.h"

#include <memory>
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
  std::string arg;
  int iarg, shift;
  int help_flag, input_flag;

  //

  error = std::make_unique<Error>();

  // Process command-line arguments

  help_flag = 0;
  input_flag = 0;

  iarg = 1;
  while (iarg < argc) {
    arg = argv[iarg];
    if (std::regex_match(arg, std::regex("-{1,2}h(elp)?"))) {
      shift = 1;
      if (iarg + shift > argc) {
        error->fatal(FLERR, "Invalid command-line argument");
      }
      help_flag = iarg + 1;
      iarg += shift;
    } else if (std::regex_match(arg, std::regex("-{1,2}i(n(put)?)?"))) {
      shift = 2;
      if (iarg + shift > argc) {
        error->fatal(FLERR, "Invalid command-line argument");
      }
      input_flag = iarg + 1;
      iarg += shift;
    } else {
      error->fatal(FLERR, "Invalid command-line argument");
    }
  }

  //

  if (help_flag) {
    //help();
    //error->done();
  }

  //

  if (input_flag) {
    input = std::make_unique<Input>(argc, argv);
  } else {
    error->fatal(FLERR, "The --input command-line option was not found");
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

void KO::help(char *exename)
{
}

// -------------------------------------------------------------------------- //
