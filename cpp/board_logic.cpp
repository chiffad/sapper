#include "board_logic.hpp"
#include "logger.hpp"

#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>

#include <iostream>
#include <fstream>


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
  ~impl_t();
  board_t get_board() const;
  bool open_field(size_t pos);
  bool mark_field(size_t pos);
  GAME_STATUS game_status() const;
  void start_new_game();
  int bombs_left() const;

  void generate_field();
  std::vector<coord_t> get_around_coords(const coord_t& c) const;
  void save_game() const;
  bool load_game();

  board_t board;
  board_t opened_board;
  GAME_STATUS status;
  size_t hidden_left;
  int hidden_bombs;
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

bool board_logic_t::mark_field(const size_t pos)
{
  return impl->mark_field(pos);
}

GAME_STATUS board_logic_t::game_status() const
{
  return impl->game_status();
}

void board_logic_t::start_new_game()
{
  impl->start_new_game();
}

int board_logic_t::bombs_left() const
{
  return impl->bombs_left();
}
///

/////////////////////////////////////////////////////////
///board_logic_t::impl_t implementation
board_logic_t::impl_t::impl_t()
  : status(GAME_STATUS::in_progress)
  , hidden_left(0)
  , hidden_bombs(BOMBS_NUM)
{
  std::srand(std::time(nullptr));
  if(!load_game()) start_new_game();

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

board_logic_t::impl_t::~impl_t()
{
  save_game();
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

bool board_logic_t::impl_t::mark_field(size_t pos)
{
  LOG_DBG<<"try_to_mark: "<<pos;
  if(status != GAME_STATUS::in_progress) return false;

  if(opened_board[pos] == ELEMENT::flag)
  {
    LOG_DBG<<"mark from flag to hidden: "<<pos;
    ++hidden_bombs;
    opened_board[pos] = ELEMENT::hidden;
    return true;
  }

  if(opened_board[pos] != ELEMENT::hidden) return false;

  LOG_DBG<<"mark flag: "<<pos;
  opened_board[pos] = ELEMENT::flag;
  --hidden_bombs;

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
  hidden_left  = board.size();
  hidden_bombs = BOMBS_NUM;

  generate_field();
}

int board_logic_t::impl_t::bombs_left() const
{
  return hidden_bombs;
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

void board_logic_t::impl_t::save_game() const
{
  std::ofstream outdata;
  outdata.open("board.save");
  if(!outdata)
  {
    LOG_DBG<<"Error: file could not be opened";
    return;
  }

  for(auto el : board) outdata<<static_cast<char>(el);
  outdata<<std::endl;

  for(auto el : opened_board) outdata<<static_cast<char>(el);
  outdata<<std::endl;
}

bool board_logic_t::impl_t::load_game()
{
  std::ifstream is("board.save");

  if(!is)
  {
    LOG_DBG<<"Error: file could not be opened";
    return false;
  }

  std::array<char, FIELD_SIZE> tmp;
  if(is.getline(tmp.data(), FIELD_SIZE))
  {
    for(size_t i = 0; i < FIELD_SIZE; ++i) board[i] = static_cast<ELEMENT>(tmp[i]);

    is.getline(tmp.data(), tmp.size());
    for(size_t i = 0; i < FIELD_SIZE; ++i) opened_board[i] = static_cast<ELEMENT>(tmp[i]);
  }

  return true;
}
///

}// namespace sapper
