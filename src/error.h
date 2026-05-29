/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#ifndef ERROR_H
#define ERROR_H

#include <memory>
#include <string>

namespace KO_NS {

class Error {

  public:

  Error();

  public:

  [[noreturn]] void done(int);
  [[noreturn]] void fatal(const std::string &, int, const std::string &);

  private:

  std::string basename(const std::string &);

}; // class Error
inline std::unique_ptr<Error> error;
} // namespace KO_NS

#endif

// -------------------------------------------------------------------------- //
