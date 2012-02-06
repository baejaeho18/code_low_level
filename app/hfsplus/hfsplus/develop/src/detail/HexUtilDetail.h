#pragma once

#include <stdint.h>

namespace utility { namespace detail {
////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
template<typename IntType>
IntType to_intbe(uint8_t const* buf, size_t size)
{
    uint8_t res[8] = { 0 };

    if (buf == NULL)
        return IntType(0);

    for (size_t i=0; i<size; i++)
        res[i] = *(buf + size - 1 - i);

    return *(IntType *)res;
}

////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////
} // end of detail
} // end of utility
