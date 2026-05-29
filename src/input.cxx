/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#include "input.h"

#include "error.h"
#include "macros.h"
#include "universe.h"

#include <format>
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

Input::Input(int argc, char **argv)
{
  std::string arg;
  int iarg, shift;
  int echo_flag;

  // Default parameter values

  echo_console = 0;
  echo_logfile = 1;

  // Process command-line arguments

  iarg = 1;
  while (iarg < argc) {
    arg = argv[iarg];
    if (std::regex_match(arg, std::regex("-{1,2}e(cho)?"))) {
      shift = 2;
      narg = 1;
      args = argv[iarg+1];
      echo();
      iarg += shift;
    } else if (std::regex_match(arg, std::regex("-{1,2}i(n(put)?)?"))) {
      shift = 2;
      input_file = argv[iarg+1];
      iarg += shift;
    } else {
      iarg += 1;
    }
  }
}

// -------------------------------------------------------------------------- //


/* --------------------------------------------------------------------------
   Public functions
   -------------------------------------------------------------------------- */


// -------------------------------------------------------------------------- //

void Input::file()
{
  // Open the input file

  stream.open(input_file);
  if (!stream.is_open()) {
    error->fatal(FLERR, std::format(R"(Could not open the file "{}")", input_file));
  }

  // Process input file contents

  while (std::getline(stream, line)) {

    // If line ends in '&', append next line

    // ...

    // Echo the line

    if (echo_console && universe->console) {
      std::print(universe->console, "{}\n", line);
    }

    if (echo_logfile && universe->logfile) {
      std::print(universe->logfile, "{}\n", line);
    }

    // Parse the line

    parse();

    // Execute the command

    execute_command();
  }

  // Close the input file

  stream.close();
}

// -------------------------------------------------------------------------- //


/* --------------------------------------------------------------------------
   Private functions
   -------------------------------------------------------------------------- */


// -------------------------------------------------------------------------- //

void Input::echo()
{
  if (narg != 1) {
    error->fatal(FLERR, "Too many args");
  }

  if (args == "both") {
    echo_console = 1;
    echo_logfile = 1;
  } else if (args == "console") {
    echo_console = 1;
    echo_logfile = 0;
  } else if (args == "logfile") {
    echo_console = 0;
    echo_logfile = 1;
  } else if (args == "none") {
    echo_console = 0;
    echo_logfile = 0;
  } else {
    error->fatal(FLERR, std::format(R"(Unknown echo keyword "{}")", args));
  }
}

// -------------------------------------------------------------------------- //

void Input::execute_command()
{
}

// -------------------------------------------------------------------------- //

void Input::parse()
{
}

// -------------------------------------------------------------------------- //

void Input::trim_comments()
{
}

// -------------------------------------------------------------------------- //

void Input::trim_whitespace()
{
}

// -------------------------------------------------------------------------- //


// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //


// -------------------------------------------------------------------------- //

void Input::boundary()
{
}

// -------------------------------------------------------------------------- //