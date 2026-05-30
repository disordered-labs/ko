/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#ifndef INPUT_H
#define INPUT_H

#include <memory>
#include <string>

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
    std::string args;

    int narg;
    int echo_console;
    int echo_logfile;

    void trim_comments(std::string &);
    void trim_whitespace(std::string &);

    void parse();
    void execute_command();

  private:

    void boundary();
    void echo();

}; // class Input
} // namespace KO_NS

#endif

// -------------------------------------------------------------------------- //
