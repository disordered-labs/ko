/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#ifndef INPUT_H
#define INPUT_H

#include <fstream>
#include <memory>
#include <string>

namespace KO_NS {

class Input {

  public:

  Input(int, char **);

  public:

  void file();

  private:

  int echo_console;
  int echo_logfile;

  std::ifstream stream;
  std::string input_file;
  std::string line;

  int narg;
  std::string args;

  void execute_command();
  void parse();
  void trim_comments();
  void trim_whitespace();
  void echo();
  void boundary();

}; // class Input
} // namespace KO_NS

#endif

// -------------------------------------------------------------------------- //
