#include "board.hpp"

#include <cstdlib>
#include <ctime>
#include <vector>


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
  void open_field(const coord_t& pos);

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

void board_logic_t::open_field(const coord_t& pos)
{
  impl->open_field(pos);
}
///

/////////////////////////////////////////////////////////
///board_logic_t::impl_t implementation
board_logic_t::impl_t::impl_t()
{
  std::srand(std::time(nullptr));
  generate_field();
  board.fill(ELEMENT::empty);
  opened_board.fill(ELEMENT::hidden);
}

board_t board_logic_t::impl_t::get_board() const
{
  return opened_board;
}

void board_logic_t::impl_t::open_field(const coord_t& /*pos*/)
{
}

void board_logic_t::impl_t::generate_field()
{
  for(int i = 0; i < FIELD_SIZE; ++i)
  {
    size_t pos = get_random_field();
    while(board[pos] == ELEMENT::bomb) pos = get_random_field();

    board[pos] = ELEMENT::bomb;

    for(auto& c : get_around_not_bomb_fields(to_coord(pos))) ++board[get_pos(c)];
  }
}

std::vector<coord_t> board_logic_t::impl_t::get_around_not_bomb_fields(const coord_t& c) const
{
  std::vector<coord_t> cs {coord_t{c.x - 1, c.y + 1}, coord_t{c.x, c.y + 1}, coord_t{c.x + 1, c.y + 1},
                           coord_t{c.x - 1, c.y    },                        coord_t{c.x + 1, c.y    },
                           coord_t{c.x - 1, c.y - 1}, coord_t{c.x, c.y - 1}, coord_t{c.x + 1, c.y - 1}};

  for(size_t i = 0; i < cs.size(); ++i)
  {
    if(!valid(cs[i]) || board[get_pos(cs[i])] == ELEMENT::bomb) cs.erase(cs.begin() + 1);
  }

  return cs;
}

///

}// namespace sapper
