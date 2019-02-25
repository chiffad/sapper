#pragma once

#include "helper.hpp"

#include <memory>


namespace sapper
{

class board_logic_t
{
public:
  board_logic_t();
  ~board_logic_t();

  board_t get_board() const;
  //return false if field already open
  bool open_field(const size_t pos);
  void mark_field(const size_t pos, bool bomb);

private:
  struct impl_t;
  std::unique_ptr<impl_t> impl;
};

}// namespace sapper
