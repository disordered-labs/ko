/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#ifndef ERROR_H
#define ERROR_H

#include <memory>
#include <string>
#include <string_view>

namespace KO_NS {

class Error {

  public:

    Error();

  public:

    [[noreturn]] auto done(int) -> void;
    [[noreturn]] auto fatal(std::string_view, int, std::string_view) -> void;

    auto warn(std::string_view, int, std::string_view) -> void;

  private:

    int numwarn;
    int maxwarn;

    auto basename(std::string_view) -> std::string_view;

}; // class Error
inline std::unique_ptr<Error> error;
} // namespace KO_NS

#endif

// -------------------------------------------------------------------------- //
