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
  void open_field(const coord_t& pos);

private:
  struct impl_t;
  std::unique_ptr<impl_t> impl;
};

}// namespace sapper
