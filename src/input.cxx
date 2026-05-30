/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#include "input.h"

#include "error.h"
#include "macros.h"
#include "universe.h"

#include <algorithm>
#include <format>
#include <fstream>
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
  std::ifstream stream;
  std::string line, next_line;

  // Open the input file

  stream.open(input_file);
  if (!stream.is_open()) {
    error->fatal(FLERR, std::format(R"(Could not open the file "{}")", input_file));
  }

  // Process input file contents

  while (std::getline(stream, line)) {

    // Trim comments and whitespace

    trim_comments(line);
    trim_whitespace(line);

    if (line.empty()) continue;

    // Append the next line if the current line ends in '&'

    while (!line.empty() && line.back() == '&') {
      line.pop_back();
      if (!std::getline(stream, next_line)) {
        break;
      }
      trim_comments(next_line);
      trim_whitespace(next_line);
      line.append(" ").append(next_line);
    }

    // Echo the line

    if (echo_console && universe->console) {
      std::print(universe->console, "{}\n", line);
    }

    if (echo_logfile && universe->logfile) {
      std::print(universe->logfile, "{}\n", line);
    }

    // Sanity check line syntax before parsing

    if (std::ranges::count(line, '&') > 0) {
      error->fatal(FLERR, "Too many line continuations");
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

void Input::trim_comments(std::string &string)
{
  size_t pos = string.find_first_of(comments);

  if (pos != std::string::npos) {
    string.erase(pos);
  }
}

// -------------------------------------------------------------------------- //

void Input::trim_whitespace(std::string &string)
{
  size_t beg = string.find_first_not_of(whitespace);
  size_t end = string.find_last_not_of(whitespace);

  if (beg != std::string::npos && end != std::string::npos) {
    string.erase(0,beg);
    string.erase(end-beg+1);
  } else {
    string.clear();
  }
}

// -------------------------------------------------------------------------- //

void Input::parse()
{
}

// -------------------------------------------------------------------------- //

void Input::execute_command()
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