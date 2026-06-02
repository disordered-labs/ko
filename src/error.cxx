/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#include "error.h"

#include "macros.h"
#include "universe.h"

#include <cstdlib>
#include <cstdio>
#include <format>
#include <print>
#include <string>
#include <string_view>

// -------------------------------------------------------------------------- //

using namespace KO_NS;

// -------------------------------------------------------------------------- //


/* --------------------------------------------------------------------------
   Special member functions
   -------------------------------------------------------------------------- */


// -------------------------------------------------------------------------- //

Error::Error() : numwarn(0), maxwarn(100) {}

// -------------------------------------------------------------------------- //


/* --------------------------------------------------------------------------
   Public functions
   -------------------------------------------------------------------------- */


// -------------------------------------------------------------------------- //

auto Error::done(int status) -> void
{
  if ((universe->console) && (universe->console != stdout)) {
    fclose(universe->console);
  }
  if (universe->logfile) {
    fclose(universe->logfile);
  }
  std::exit(status);
}

// -------------------------------------------------------------------------- //

auto Error::fatal(std::string_view path, int line, std::string_view memo) -> void
{
  std::string message = std::format("\nERROR: {} ({}:{})\n",
                                    memo, basename(path), line);

  if (universe->console) {
    std::print(universe->console, "{}", message);
    if (universe->console != stdout) {
      fclose(universe->console);
    }
  }
  if (universe->logfile) {
    std::print(universe->logfile, "{}", message);
    fclose(universe->logfile);
  }
  std::exit(EXIT_FAILURE);
}

// -------------------------------------------------------------------------- //

auto Error::warn(std::string_view path, int line, std::string_view memo) -> void
{
  numwarn += 1;
  if ((maxwarn > 0) && (numwarn > maxwarn)) {
    return;
  }

  std::string message = std::format("WARNING: {} ({}:{})\n",
                                    memo, basename(path), line);

  if (universe->console) {
    std::print(universe->console, "{}", message);
  }
  if (universe->logfile) {
    std::print(universe->logfile, "{}", message);
  }

  if ((maxwarn > 0) && (numwarn == maxwarn)) {
    std::string note = "WARNING: Maximum warning count reached. "
                       "Further warnings will be suppressed.\n";
    if (universe->console) {
      std::print(universe->console, "{}", note);
    }
    if (universe->logfile) {
      std::print(universe->logfile, "{}", note);
    }
  }
}

// -------------------------------------------------------------------------- //


/* --------------------------------------------------------------------------
   Private functions
   -------------------------------------------------------------------------- */


// -------------------------------------------------------------------------- //

auto Error::basename(std::string_view path) -> std::string_view
{
  auto found = path.find("src/");

  if (found != std::string_view::npos) {
    return path.substr(found);
  } else {
    return path;
  }
}

// -------------------------------------------------------------------------- //
