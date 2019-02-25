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
}

namespace sapper
{

/////////////////////////////////////////////////////////
///board_logic_t::impl_t declaration
struct board_logic_t::impl_t
{
  impl_t();
  board_t get_board() const;
  void open_field(size_t pos);
  void mark_field(size_t pos, bool bomb);

  void generate_field();
  std::vector<coord_t> get_around_not_bomb_fields(const coord_t& c) const;

  board_t board;
  board_t opened_board;
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

void board_logic_t::open_field(const size_t pos)
{
  impl->open_field(pos);
}

void board_logic_t::mark_field(const size_t pos, bool bomb)
{
  impl->mark_field(pos, bomb);
}
///

/////////////////////////////////////////////////////////
///board_logic_t::impl_t implementation
board_logic_t::impl_t::impl_t()
{
  std::srand(std::time(nullptr));
  board.fill(ELEMENT::empty);
  opened_board.fill(ELEMENT::hidden);

  generate_field();

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

void board_logic_t::impl_t::open_field(size_t pos)
{
  opened_board[pos] = board[pos];
}

void board_logic_t::impl_t::mark_field(size_t /*pos*/, bool /*bomb*/)
{
}

void board_logic_t::impl_t::generate_field()
{
  for(int i = 0; i < BOMBS_NUM; ++i)
  {
    size_t pos = get_random_field();
    while(board[pos] == ELEMENT::bomb) pos = get_random_field();

    board[pos] = ELEMENT::bomb;

    for(auto& c : get_around_not_bomb_fields(to_coord(pos))) board[get_pos(c)] = static_cast<ELEMENT>(static_cast<int>(board[get_pos(c)]) + 1);
  }
}

std::vector<coord_t> board_logic_t::impl_t::get_around_not_bomb_fields(const coord_t& c) const
{
  std::vector<coord_t> cs {coord_t{c.x - 1, c.y + 1}, coord_t{c.x, c.y + 1}, coord_t{c.x + 1, c.y + 1},
                           coord_t{c.x - 1, c.y    },                        coord_t{c.x + 1, c.y    },
                           coord_t{c.x - 1, c.y - 1}, coord_t{c.x, c.y - 1}, coord_t{c.x + 1, c.y - 1}};

  for(size_t i = 0; i < cs.size();)
  {
    if(!valid(cs[i]) || board[get_pos(cs[i])] == ELEMENT::bomb) cs.erase(cs.begin() + i);
    else ++i;
  }

  return cs;
}

///

}// namespace sapper
