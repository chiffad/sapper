#pragma once

#include <array>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <complex>


namespace sapper
{

const int X_SIZE = 15;
const int Y_SIZE = 20;
const int FIELD_SIZE = Y_SIZE * X_SIZE;
const int BOMBS_NUM = 45;
enum class ELEMENT {hidden = 'h', bomb = 'b', empty = 0, one = 1, two = 2, three = 3, four = 4, five = 5, six = 6, seven = 7, eight = 8};
using board_t = std::array<ELEMENT, FIELD_SIZE>;

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
