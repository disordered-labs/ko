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

    std::ifstream stream;
    std::string input_file;
    std::string line;

}; // class Input
} // namespace KO_NS

#endif

// -------------------------------------------------------------------------- //
