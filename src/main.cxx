/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#include "ko.h"

#include <cstdlib>
#include <exception>
#include <memory>
#include <print>

// -------------------------------------------------------------------------- //

using namespace KO_NS;

// -------------------------------------------------------------------------- //

int main(int argc, char **argv)
{
  try {
    auto ko = std::make_unique<KO>(argc, argv);
    ko->input->file();
  } catch (std::exception &mesg) {
    std::print(stdout, "\nERROR: The following exception has occured\n{}\n", mesg.what());
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

// -------------------------------------------------------------------------- //
