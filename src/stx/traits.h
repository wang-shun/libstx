/**
 * This file is part of the "libstx" project
 *   Copyright (c) 2014 Paul Asmuth, Google Inc.
 *
 * libstx is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License v3.0. You should have received a
 * copy of the GNU General Public License along with this program. If not, see
 * <http://www.gnu.org/licenses/>.
 */
#ifndef _STX_TRAITS_H
#define _STX_TRAITS_H

namespace stx {

/* TypeIsReflected<T> */
template <typename T>
using TypeIsReflected = stx::reflect::is_reflected<T>;

/* TypeIsVector<T> */
template <typename T, typename = void>
struct TypeIsVector {
  static const bool value = false;
};

template <typename T>
struct TypeIsVector<
    T,
    typename std::enable_if<
        std::is_same<
            T,
            std::vector<
                typename T::value_type,
                typename T::allocator_type>>::value>::type>  {
  static const bool value = true;
};

} // namespace stx
#endif
