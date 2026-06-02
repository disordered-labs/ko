/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <vector>

namespace KO_NS {

class Input {

  public:

    Input(int, char **);

  public:

    auto file() -> void;

  private:

    const std::string comments = "!#$";
    const std::string whitespace = " \t\f\v\n\r";

    std::string input_file;

    std::string command;
    std::vector<std::string> args;

    int echo_console;
    int echo_logfile;

    auto trim_comments(std::string &) -> void;
    auto trim_whitespace(std::string &) -> void;

    auto parse(std::string &) -> void;
    auto execute_command() -> void;

  private:

    auto echo() -> void;
    auto boundary() -> void;
    auto material() -> void;
    auto mesh() -> void;
    auto variable() -> void;

}; // class Input
} // namespace KO_NS

#endif

// -------------------------------------------------------------------------- //
