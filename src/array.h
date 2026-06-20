/* -----------------------------------------------------------------------------
   KO - Computer Simulation of Dynamic Phenomena

   See the README file in the top-level directory.
----------------------------------------------------------------------------- */

#ifndef ARRAY_H
#define ARRAY_H

#include <cassert>
#include <cstddef>
#include <vector>

namespace KO_NS {

// --------------------------------------------------------------------------
//  Array<T> — dynamic-rank N-dimensional array
//
//  Rank is determined at allocation time from the number of arguments:
//
//    Array<double> x;
//    x.allocate(100);          // 1D
//    x.allocate(100, 50);      // 2D
//    x.allocate(10, 20, 30);   // 3D
//    x.allocate(10, 20, 30, 40); // 4D
//
//  Access via C++23 multi-parameter operator[]:
//
//    x[42] = 1.0;
//    y[3, 17] = 2.71;
//    z[3, 15, 22] = 1.0;
//Array<double> *x = new Array<double>();
//x->allocate(100);
// ... use it ...
//delete x;
//Or with a smart pointer:
//auto x = std::make_unique<Array<double>>();
//x->allocate(100);
// --------------------------------------------------------------------------

template <typename T>
class Array {

  public:

    // Constructors

    Array() = default;

    template <typename... Dims>
    explicit Array(Dims... d) { allocate(d...); }

    // Allocate storage with the given dimensions

    template <typename... Dims>
    auto allocate(Dims... d) -> void {
      static_assert(sizeof...(Dims) >= 1, "Array::allocate requires at least one dimension");
      _dims = {static_cast<int>(d)...};
      _data.resize(product(_dims));
    }

    // Grow or shrink the array

    template <typename... Dims>
    auto grow(Dims... d) -> void {
      constexpr auto R = sizeof...(Dims);
      static_assert(R >= 1, "Array::grow requires at least one dimension");
      int nd[R] = {static_cast<int>(d)...};

      if constexpr (R == 1) {
        _data.resize(nd[0]);
        _dims[0] = nd[0];
      } else {
        bool trailing_unchanged = true;
        for (std::size_t i = 1; i < R; ++i) {
          if (nd[i] != _dims[i]) { trailing_unchanged = false; break; }
        }

        if (trailing_unchanged) {
          _data.resize(product(nd, R));
          _dims[0] = nd[0];
          return;
        }

        std::vector<T> ndata(product(nd, R));

        if constexpr (R == 2) {
          int cn1 = _dims[0] < nd[0] ? _dims[0] : nd[0];
          int cn2 = _dims[1] < nd[1] ? _dims[1] : nd[1];
          for (int i = 0; i < cn1; ++i)
            for (int j = 0; j < cn2; ++j)
              ndata[i * nd[1] + j] = _data[i * _dims[1] + j];
        } else if constexpr (R == 3) {
          int cn1 = _dims[0] < nd[0] ? _dims[0] : nd[0];
          int cn2 = _dims[1] < nd[1] ? _dims[1] : nd[1];
          int cn3 = _dims[2] < nd[2] ? _dims[2] : nd[2];
          for (int i = 0; i < cn1; ++i)
            for (int j = 0; j < cn2; ++j)
              for (int k = 0; k < cn3; ++k)
                ndata[(i * nd[1] + j) * nd[2] + k]
                  = _data[(i * _dims[1] + j) * _dims[2] + k];
        } else if constexpr (R == 4) {
          int cn1 = _dims[0] < nd[0] ? _dims[0] : nd[0];
          int cn2 = _dims[1] < nd[1] ? _dims[1] : nd[1];
          int cn3 = _dims[2] < nd[2] ? _dims[2] : nd[2];
          int cn4 = _dims[3] < nd[3] ? _dims[3] : nd[3];
          for (int i = 0; i < cn1; ++i)
            for (int j = 0; j < cn2; ++j)
              for (int k = 0; k < cn3; ++k)
                for (int l = 0; l < cn4; ++l)
                  ndata[((i * nd[1] + j) * nd[2] + k) * nd[3] + l]
                    = _data[((i * _dims[1] + j) * _dims[2] + k) * _dims[3] + l];
        }

        _data = std::move(ndata);
        _dims.assign(nd, nd + R);
      }
    }

    // Release all storage and reset to empty

    auto deallocate() -> void {
      _data.clear();
      _data.shrink_to_fit();
      _dims.clear();
    }

    // Return the total number of elements

    auto size() const noexcept -> std::size_t { return _data.size(); }

    // Return the extent of a single dimension

    auto size(int dim) const -> int {
      assert(dim >= 1 && dim <= static_cast<int>(_dims.size()));
      return _dims[dim - 1];
    }

    // Return the number of dimensions

    auto rank() const noexcept -> std::size_t { return _dims.size(); }

    // --- Element access ------------------------------------------------------

    template <typename... Idx>
    auto operator[](Idx... idx) -> T & {
      assert(_dims.size() == sizeof...(Idx));
      std::size_t off = 0;
      std::size_t d = 0;
      ((off = off * static_cast<std::size_t>(_dims[d++]) + static_cast<std::size_t>(idx)), ...);
      return _data[off];
    }

    template <typename... Idx>
    auto operator[](Idx... idx) const -> T const & {
      assert(_dims.size() == sizeof...(Idx));
      std::size_t off = 0;
      std::size_t d = 0;
      ((off = off * static_cast<std::size_t>(_dims[d++]) + static_cast<std::size_t>(idx)), ...);
      return _data[off];
    }

    // --- Raw pointer access --------------------------------------------------

    auto data() noexcept -> T * { return _data.data(); }
    auto data() const noexcept -> T const * { return _data.data(); }

  private:

    std::vector<T> _data;
    std::vector<int> _dims;

    static auto product(const std::vector<int> &d) -> std::size_t {
      std::size_t p = 1;
      for (auto x : d) p *= x;
      return p;
    }

    static auto product(const int *d, std::size_t n) -> std::size_t {
      std::size_t p = 1;
      for (std::size_t i = 0; i < n; ++i) p *= d[i];
      return p;
    }

}; // class Array
} // namespace KO_NS

#endif

// -------------------------------------------------------------------------- //
