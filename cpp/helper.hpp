#pragma once

#include <array>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <complex>


namespace sapper
{

const int X_SIZE = 20;
const int Y_SIZE = 23;
const int FIELD_SIZE = Y_SIZE * X_SIZE;
const int BOMBS_NUM = 80;
enum class ELEMENT {hidden = 'h', bomb  = 'b', flag  = 'f',
                    empty  = '0', one   = '1', two   = '2',
                    three  = '3', four  = '4', five  = '5',
                    six    = '6', seven = '7', eight = '8' };
using board_t = std::array<ELEMENT, FIELD_SIZE>;

inline bool valid_ELEMENT(const size_t el)
{
  switch(static_cast<ELEMENT>(el))
  {
    case ELEMENT::hidden:
    case ELEMENT::empty :
    case ELEMENT::three :
    case ELEMENT::six   :
    case ELEMENT::bomb  :
    case ELEMENT::one   :
    case ELEMENT::four  :
    case ELEMENT::seven :
    case ELEMENT::flag  :
    case ELEMENT::two   :
    case ELEMENT::five  :
    case ELEMENT::eight : return true;
    default: return false;
  }
}

struct coord_t
{
  int x;
  int y;
};

inline bool valid(const coord_t& c) noexcept
{
  return 0 <= c.x && c.x < X_SIZE &&
         0 <= c.y && c.y < Y_SIZE;
}

inline coord_t to_coord(const int pos) noexcept
{
  return coord_t{pos % X_SIZE, pos / X_SIZE};
}

inline size_t get_pos(const coord_t& c) noexcept
{
  return c.x + c.y * X_SIZE;
}


template <typename os_t>
os_t& operator<<(os_t& os, const coord_t& c)
{
   return os<<"x: "<<c.x<<"; y: "<<c.y;
}


}// namespace sapper
