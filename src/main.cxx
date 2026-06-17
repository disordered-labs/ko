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

auto main(int argc, char **argv) -> int
{
  try {
    auto ko = std::make_unique<KO>(argc, argv);
    ko->run();
    return EXIT_SUCCESS;
  } catch (const std::exception &mesg) {
    std::print(stderr, "\nERROR: {}\n", mesg.what());
    return EXIT_FAILURE;
  } catch (...) {
    std::print(stderr, "\nERROR: An unknown exception has occurred.\n");
    return EXIT_FAILURE;
  }
}

// -------------------------------------------------------------------------- //
