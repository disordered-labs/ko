/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#include "input.h"

#include "error.h"
#include "macros.h"
#include "universe.h"

#include <format>
#include <fstream>
#include <print>
#include <sstream>
#include <string>

// -------------------------------------------------------------------------- //

using namespace KO_NS;

// -------------------------------------------------------------------------- //


/* --------------------------------------------------------------------------
   Special member functions
   -------------------------------------------------------------------------- */


// -------------------------------------------------------------------------- //

Input::Input(KO *ko, int argc, char **argv) : Pointers(ko)
{
  std::string option;
  int iarg, shift;

  // Default parameter values

  echo_console = 0;
  echo_logfile = 1;

  // Process command-line arguments

  iarg = 1;
  while (iarg < argc) {
    option = argv[iarg];
    if (option == "-e" || option == "--echo") {
      shift = 2;
      args.clear();
      args.push_back(argv[iarg+1]);
      echo();
      args.clear();
      iarg += shift;
    } else if (option == "-i" || option == "--input") {
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

auto Input::file() -> void
{
  std::ifstream stream;
  std::string line, next_line;

  // Open the input file

  stream.open(input_file);
  if (!stream.is_open()) {
    error->fatal(FLERR, std::format(R"(Could not open the input file "{}")", input_file));
  }

  // Process input file contents

  while (std::getline(stream, line)) {

    // Trim comments and whitespace, skip to the next line if empty

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

    if (echo_console && universe->console()) {
      std::print(universe->console(), "{}\n", line);
    }

    if (echo_logfile && universe->logfile()) {
      std::print(universe->logfile(), "{}\n", line);
    }

    // Parse the line, skip to the next line if empty

    parse(line);
    if (command.empty()) continue;

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

auto Input::trim_comments(std::string &line) -> void
{
  size_t pos = line.find_first_of(comments);

  if (pos != std::string::npos) {
    line.erase(pos);
  }
}

// -------------------------------------------------------------------------- //

auto Input::trim_whitespace(std::string &line) -> void
{
  size_t beg = line.find_first_not_of(whitespace);
  size_t end = line.find_last_not_of(whitespace);

  if (beg != std::string::npos && end != std::string::npos) {
    line.erase(0,beg);
    line.erase(end-beg+1);
  } else {
    line.clear();
  }
}

// -------------------------------------------------------------------------- //

auto Input::parse(std::string &line) -> void
{
  std::string token;
  std::stringstream stream(line);

  command.clear();
  args.clear();

  if (stream >> command) {
    while (stream >> token) {
      args.push_back(token);
    }
  } else {
    error->fatal(FLERR, std::format(R"(Could not parse the line "{}")", line));
  }
}

// -------------------------------------------------------------------------- //

auto Input::execute_command() -> void
{
  if (command == "boundary") boundary();
  else if (command == "echo") echo();
  else if (command == "error") echo();
  else if (command == "material") material();
  else if (command == "mesh") mesh();
  else if (command == "variable") variable();
  else error->fatal(FLERR, std::format(R"(Unknown command "{}")", command));
}

// -------------------------------------------------------------------------- //


// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //
// -------------------------------------------------------------------------- //


// -------------------------------------------------------------------------- //

auto Input::boundary() -> void
{
}

// -------------------------------------------------------------------------- //

auto Input::echo() -> void
{
  if (args.size() != 1) {
    error->fatal(FLERR, "Echo command expects exactly one argument");
  }

  if (args[0] == "both") {
    echo_console = 1;
    echo_logfile = 1;
  } else if (args[0] == "console") {
    echo_console = 1;
    echo_logfile = 0;
  } else if (args[0] == "logfile") {
    echo_console = 0;
    echo_logfile = 1;
  } else if (args[0] == "none") {
    echo_console = 0;
    echo_logfile = 0;
  } else {
    error->fatal(FLERR, std::format(R"(Unknown echo keyword "{}")", args[0]));
  }
}

// -------------------------------------------------------------------------- //

auto Input::mesh() -> void
{
}

// -------------------------------------------------------------------------- //

auto Input::material() -> void
{
}

// -------------------------------------------------------------------------- //

auto Input::variable() -> void
{
}

// -------------------------------------------------------------------------- //