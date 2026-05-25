/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#include "ko.h"

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <memory>

// -------------------------------------------------------------------------- //

using namespace KO_NS;

// -------------------------------------------------------------------------- //

int main(int argc, char **argv)
{
  try {
    auto ko = std::make_unique<KO>(argc, argv);
    //
  } catch (std::exception &mesg) {
    fprintf(stdout, "\nERROR: The following exception has occured\n%s\n",
            mesg.what());
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

// -------------------------------------------------------------------------- //
