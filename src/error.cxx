/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#include "error.h"

#include "macros.h"
#include "universe.h"

#include <cstdio>
#include <format>
#include <print>
#include <string>

// -------------------------------------------------------------------------- //

using namespace KO_NS;

// -------------------------------------------------------------------------- //


/* --------------------------------------------------------------------------
   Special member functions
   -------------------------------------------------------------------------- */


// -------------------------------------------------------------------------- //

Error::Error()
{
}

// -------------------------------------------------------------------------- //


/* --------------------------------------------------------------------------
   Public functions
   -------------------------------------------------------------------------- */


// -------------------------------------------------------------------------- //

void Error::done(int status)
{
  if (universe->console != stdout) {
    fclose(universe->console);
  }

  if (universe->logfile) {
    fclose(universe->logfile);
  }

  exit(status);
}

// -------------------------------------------------------------------------- //

void Error::fatal(const std::string &file, int line, const std::string &string)
{
  std::string mesg = std::format("\nERROR: {} ({}:{})\n", string, basename(file), line);

  if (universe->console) {
    std::print(universe->console, "{}", mesg);
    if (universe->console != stdout) {
      fclose(universe->console);
    }
  }

  if (universe->logfile) {
    std::print(universe->logfile, "{}", mesg);
    fclose(universe->logfile);
  }

  exit(EXIT_FAILURE);
}

// -------------------------------------------------------------------------- //


/* --------------------------------------------------------------------------
   Private functions
   -------------------------------------------------------------------------- */


// -------------------------------------------------------------------------- //

std::string Error::basename(const std::string &path)
{
  std::size_t found;

  found = path.find("src/");
  if (found != std::string::npos) {
    return path.substr(found);
  } else {
    return path;
  }
}

// -------------------------------------------------------------------------- //
