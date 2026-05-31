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
#include <regex>
#include <sstream>
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
      args.clear();
      args.push_back(argv[iarg+1]);
      echo();
      args.clear();
      iarg += shift;
    } else if (std::regex_match(arg, std::regex("-{1,2}i(nput)?"))) {
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

    if (echo_console && universe->console) {
      std::print(universe->console, "{}\n", line);
    }

    if (echo_logfile && universe->logfile) {
      std::print(universe->logfile, "{}\n", line);
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

void Input::trim_comments(std::string &line)
{
  size_t pos = line.find_first_of(comments);

  if (pos != std::string::npos) {
    line.erase(pos);
  }
}

// -------------------------------------------------------------------------- //

void Input::trim_whitespace(std::string &line)
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

void Input::parse(std::string &line)
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

void Input::execute_command()
{
  if (command == "boundary") boundary();
  else if (command == "echo") echo();
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

void Input::boundary()
{
}

// -------------------------------------------------------------------------- //

void Input::echo()
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

void Input::mesh()
{
}

// -------------------------------------------------------------------------- //

void Input::material()
{
}

// -------------------------------------------------------------------------- //

void Input::variable()
{
}

// -------------------------------------------------------------------------- //