#pragma once

#include "helper.hpp"

#include <memory>


namespace sapper
{

class board_logic_t
{
public:
  enum GAME_STATUS{in_progress, win, lose};

public:
  board_logic_t();
  ~board_logic_t();

  board_t get_board() const;
  GAME_STATUS status() const;
  void start_new_game();
  int bombs_left() const;
  //return false if field already open
  bool open_field(const size_t pos);
  bool mark_field(const size_t pos);
  void save_game() const;


private:
  struct impl_t;
  std::unique_ptr<impl_t> impl;
};

}// namespace sapper
