/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#ifndef INPUT_H
#define INPUT_H

#include <memory>
#include <string>
#include <vector>

namespace KO_NS {

class Input {

  public:

    Input(int, char **);

  public:

    void file();

  private:

    const std::string comments = "!#$";
    const std::string whitespace = " \t\f\v\n\r";

    std::string input_file;
    std::string command;
    std::vector<std::string> args;

    int echo_console;
    int echo_logfile;

    void trim_comments(std::string &);
    void trim_whitespace(std::string &);

    void parse(std::string &);
    void execute_command();

  private:

    void echo();
    void boundary();
    void material();
    void mesh();
    void variable();

}; // class Input
} // namespace KO_NS

#endif

// -------------------------------------------------------------------------- //
