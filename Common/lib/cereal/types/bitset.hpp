/*! \file bitset.hpp
    \brief Support for types found in \<bitset\>
    \ingroup STLSupport */
/*
  Copyright (c) 2014, Randolph Voorhies, Shane Grant
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
      * Redistributions of source code must retain the above copyright
        notice, this list of conditions and the following disclaimer.
      * Redistributions in binary form must reproduce the above copyright
        notice, this list of conditions and the following disclaimer in the
        documentation and/or other materials provided with the distribution.
      * Neither the name of cereal nor the
        names of its contributors may be used to endorse or promote products
        derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL RANDOLPH VOORHIES OR SHANE GRANT BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef CEREAL_TYPES_BITSET_HPP_
#define CEREAL_TYPES_BITSET_HPP_

#include "cereal/cereal.hpp"
#include <bitset>

namespace cereal
{
  //! Serializing (save) for std::bitset when BinaryData optimization supported
  template <class Archive, size_t N,
            traits::EnableIf<traits::is_output_serializable<BinaryData<std::uint32_t>, Archive>::value>
            = traits::sfinae> inline
  void CEREAL_SAVE_FUNCTION_NAME( Archive & ar, std::bitset<N> const & bits )
  {
    // Serialize 8 bit chunks
    std::uint8_t chunk = 0;
    std::uint8_t mask = 0x80;

    // Set each chunk using a rotating mask for the current bit
    for( std::size_t i = 0; i < N; ++i )
    {
      if( bits[i] )
        chunk |= mask;

      mask = static_cast<std::uint8_t>(mask >> 1);

      // output current chunk when mask is empty (8 bits)
      if( mask == 0 )
      {
        ar( chunk );
        chunk = 0;
        mask = 0x80;
      }
    }

    // serialize remainder, if it exists
    if( mask != 0x80 )
      ar( chunk );
  }

  //! Serializing (load) for std::bitset
  template <class Archive, size_t N> inline
  void CEREAL_LOAD_FUNCTION_NAME( Archive & ar, std::bitset<N> & bits )
  {
    // Normally we would use BinaryData to route this at compile time,
    // but doing this at runtime doesn't break any old serialization
    std::uint8_t chunk = 0;
    std::uint8_t mask  = 0;

    bits.reset();

    // Load one chunk at a time, rotating through the chunk
    // to set bits in the bitset
    for( std::size_t i = 0; i < N; ++i )
    {
      if( mask == 0 )
      {
        ar( chunk );
        mask = 0x80;
      }

      if( chunk & mask )
        bits[i] = 1;

      mask = static_cast<std::uint8_t>(mask >> 1);
    }
  }
} // namespace cereal

#endif // CEREAL_TYPES_BITSET_HPP_
