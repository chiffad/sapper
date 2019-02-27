#include "board_logic.hpp"
#include "logger.hpp"

#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>


#ifdef DEBUG_ON
#include <string>
#endif


namespace
{
size_t get_random_field()
{
  return std::rand() % sapper::FIELD_SIZE;
}

using GAME_STATUS = sapper::board_logic_t::GAME_STATUS;
}

namespace sapper
{

/////////////////////////////////////////////////////////
///board_logic_t::impl_t declaration
struct board_logic_t::impl_t
{
  impl_t();
  board_t get_board() const;
  bool open_field(size_t pos);
  bool mark_field(size_t pos, bool bomb);
  GAME_STATUS game_status() const;
  void start_new_game();

  void generate_field();
  std::vector<coord_t> get_around_coords(const coord_t& c) const;

  board_t board;
  board_t opened_board;
  size_t hidden_left;
  GAME_STATUS status;
};
///

/////////////////////////////////////////////////////////
///board_logic_t implementation
board_logic_t::board_logic_t()
 : impl(new impl_t())
{
}

board_logic_t::~board_logic_t() = default;

board_t board_logic_t::get_board() const
{
  return impl->get_board();
}

bool board_logic_t::open_field(const size_t pos)
{
  return impl->open_field(pos);
}

bool board_logic_t::mark_field(const size_t pos, bool bomb)
{
  return impl->mark_field(pos, bomb);
}

GAME_STATUS board_logic_t::game_status() const
{
  return impl->game_status();
}

void board_logic_t::start_new_game()
{
  impl->start_new_game();
}
///

/////////////////////////////////////////////////////////
///board_logic_t::impl_t implementation
board_logic_t::impl_t::impl_t()
  : status(GAME_STATUS::in_progress)
  , hidden_left(0)
{
  std::srand(std::time(nullptr));
  start_new_game();

#ifdef DEBUG_ON
  std::string str;
  for(size_t i = 0; i < board.size(); ++i)
  {
    if(board[i] == ELEMENT::bomb) str.push_back('b');
    else str.push_back(static_cast<char>(board[i]));

    str.push_back(' ');

    if((i + 1) % X_SIZE == 0) str.push_back('\n');
  }
  LOG_DBG<<str;
#endif
}

board_t board_logic_t::impl_t::get_board() const
{
  return opened_board;
}

bool board_logic_t::impl_t::open_field(size_t pos)
{
  if(status != GAME_STATUS::in_progress
     || opened_board[pos] != ELEMENT::hidden) return false;

  opened_board[pos] = board[pos];
  --hidden_left;

  if(board[pos] != ELEMENT::empty)
  {
    if(board[pos] == ELEMENT::bomb)   status = GAME_STATUS::lose;
    else if(hidden_left == BOMBS_NUM) status = GAME_STATUS::win ;

    return true;
  }

  for(auto& c : get_around_coords(to_coord(pos))) open_field(get_pos(c));

  return true;
}

bool board_logic_t::impl_t::mark_field(size_t /*pos*/, bool /*bomb*/)
{
  return true;
}

GAME_STATUS board_logic_t::impl_t::game_status() const
{
  return status;
}

void board_logic_t::impl_t::start_new_game()
{
  status = GAME_STATUS::in_progress;
  board.fill(ELEMENT::empty);
  opened_board.fill(ELEMENT::hidden);
  hidden_left = board.size();

  generate_field();
}

void board_logic_t::impl_t::generate_field()
{
  for(int i = 0; i < BOMBS_NUM; ++i)
  {
    size_t pos = get_random_field();
    while(board[pos] == ELEMENT::bomb) pos = get_random_field();

    board[pos] = ELEMENT::bomb;

    for(auto& c : get_around_coords(to_coord(pos)))
    {
      if(board[get_pos(c)] == ELEMENT::bomb) continue;

      board[get_pos(c)] = static_cast<ELEMENT>(static_cast<int>(board[get_pos(c)]) + 1);
    }
  }
}

std::vector<coord_t> board_logic_t::impl_t::get_around_coords(const coord_t& c) const
{
  std::vector<coord_t> cs {coord_t{c.x - 1, c.y + 1}, coord_t{c.x, c.y + 1}, coord_t{c.x + 1, c.y + 1},
                           coord_t{c.x - 1, c.y    },                        coord_t{c.x + 1, c.y    },
                           coord_t{c.x - 1, c.y - 1}, coord_t{c.x, c.y - 1}, coord_t{c.x + 1, c.y - 1}};

  for(size_t i = 0; i < cs.size();)
  {
    if(!valid(cs[i])) cs.erase(cs.begin() + i);
    else ++i;
  }

  return cs;
}

///

}// namespace sapper
