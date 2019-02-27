#include "sapper.hpp"

#include "board_logic.hpp"
#include "helper.hpp"
#include "logger.hpp"


namespace sapper
{

struct obj_t
{
  char type;
  int posX;
  int posY;
};

/////////////////////////////////////////////////////////
///Sapper::impl_t declaration
struct Sapper::impl_t
{
  enum RoleNames {
    type = Qt::UserRole,
    posX = Qt::UserRole+2,
    posY = Qt::UserRole+3,
  };

  enum CLICK_MODE {open, mark_bomb};

  impl_t();

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QHash<int, QByteArray> roleNames() const;

  void field_clicked(size_t pos, Sapper& list);
  int click_mode() const;
  void start_new_game(Sapper& list);
  void change_click_mode();
  int game_status() const;
  void update_board(Sapper& list);

  board_logic_t board_logic;
  CLICK_MODE mode;
  QHash<int, QByteArray> role_names;
  QList<obj_t> objs;
};
///

/////////////////////////////////////////////////////////
///Sapper implementation
Sapper::Sapper()
  : impl(new impl_t)
{
}

Sapper::~Sapper() = default;

int Sapper::rowCount(const QModelIndex &parent) const
{
  return impl->rowCount(parent);
}

QVariant Sapper::data(const QModelIndex &index, int role) const
{
  return impl->data(index, role);
}

QHash<int, QByteArray> Sapper::roleNames() const
{
  return impl->roleNames();
}

void Sapper::field_clicked(int pos)
{
  impl->field_clicked(static_cast<size_t>(pos), *this);
}

void Sapper::change_click_mode()
{
  impl->change_click_mode();
  emit click_modeChanged();
}

void Sapper::start_new_game()
{
  impl->start_new_game(*this);
  emit game_statusChanged();
}

int Sapper::click_mode() const
{
  return impl->click_mode();
}

int Sapper::game_status() const
{
  return impl->game_status();
}
///

/////////////////////////////////////////////////////////
///Sapper::impl_t implementation
Sapper::impl_t::impl_t()
  : mode(CLICK_MODE::open)
{
  role_names[type] = "type";
  role_names[posX] = "posX";
  role_names[posY] = "posY";

  size_t i = 0;
  for(auto& el : board_logic.get_board())
  {
    const auto coord = to_coord(i);
    objs.append({static_cast<char>(el), coord.x, coord.y});
    ++i;
  }
}

int Sapper::impl_t::rowCount([[maybe_unused]] const QModelIndex &parent) const
{
  return objs.size();
}

QVariant Sapper::impl_t::data(const QModelIndex &index, int role) const
{
  const int row = index.row();
  if(!index.isValid() || row >= objs.size()) return {};

  const auto& obj = objs.at(row);
  switch(role)
  {
    case type: return obj.type;
    case posX: return obj.posX;
    case posY: return obj.posY;
  }

  return {};
}

QHash<int, QByteArray> Sapper::impl_t::roleNames() const
{
  return role_names;
}

void Sapper::impl_t::field_clicked(size_t pos, Sapper& list)
{
  LOG_DBG<<"clicked on element: "<<pos;

  if(mode == CLICK_MODE::mark_bomb && board_logic.mark_field(pos, false)) return;
  else if(!board_logic.open_field(pos)) return;

  update_board(list);

  if(board_logic.game_status() != board_logic_t::GAME_STATUS::in_progress) emit list.game_statusChanged();
}

void Sapper::impl_t::change_click_mode()
{
  switch(mode)
  {
    case CLICK_MODE::open     : mode = CLICK_MODE::mark_bomb; break;
    case CLICK_MODE::mark_bomb: mode = CLICK_MODE::open     ; break;
  }
}

void Sapper::impl_t::start_new_game(Sapper& list)
{
  board_logic.start_new_game();
  update_board(list);
}

int Sapper::impl_t::click_mode() const
{
  return static_cast<int>(mode);
}

int Sapper::impl_t::game_status() const
{
  return board_logic.game_status();
}

void Sapper::impl_t::update_board(Sapper& list)
{
  size_t i = 0;
  for(auto& el : board_logic.get_board())
  {
    auto& i_obj_t = objs[i].type;
    if(i_obj_t != static_cast<char>(el))
    {
      i_obj_t = static_cast<char>(el);
      QModelIndex topLeft = list.createIndex(i, 0);
      QModelIndex bottomRight = list.createIndex(i, 0);
      emit list.dataChanged(topLeft, bottomRight);
    }
    ++i;
  }
}

///


} //namespace sapper
