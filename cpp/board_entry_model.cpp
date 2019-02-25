#include "board_entry_model.hpp"

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

struct BoardEntryModel::impl_t
{
  enum RoleNames {
    type = Qt::UserRole,
    posX = Qt::UserRole+2,
    posY = Qt::UserRole+3,
  };

  impl_t();

  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
  QHash<int, QByteArray> roleNames() const;

  void field_clicked(int pos, BoardEntryModel& list);


  board_logic_t board_logic;
  QHash<int, QByteArray> role_names;
  QList<obj_t> objs;
};


/////////////////////////////////////////////////////////
///BoardEntryModel implementation
BoardEntryModel::BoardEntryModel()
  : impl(new impl_t)
{
}

BoardEntryModel::~BoardEntryModel() = default;

int BoardEntryModel::rowCount(const QModelIndex &parent) const
{
 // createIndex(1,0);
  return impl->rowCount(parent);
}

QVariant BoardEntryModel::data(const QModelIndex &index, int role) const
{
  return impl->data(index, role);
}

QHash<int, QByteArray> BoardEntryModel::roleNames() const
{
  return impl->roleNames();
}

void BoardEntryModel::field_clicked(int pos)
{
  impl->field_clicked(pos, *this);
}

///

/////////////////////////////////////////////////////////
///BoardEntryModel::impl_t implementation
BoardEntryModel::impl_t::impl_t()
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

int BoardEntryModel::impl_t::rowCount([[maybe_unused]] const QModelIndex &parent) const
{
  return objs.size();
}

QVariant BoardEntryModel::impl_t::data(const QModelIndex &index, int role) const
{
  const int row = index.row();
  if(!index.isValid() || row>= objs.size()) return {};

  const auto& obj = objs.at(row);
  switch(role)
  {
    case type: return obj.type;
    case posX: return obj.posX;
    case posY: return obj.posY;
  }

  return {};
}

QHash<int, QByteArray> BoardEntryModel::impl_t::roleNames() const
{
  return role_names;
}

void BoardEntryModel::impl_t::field_clicked(int pos, BoardEntryModel& list)
{
  LOG_DBG<<"clicked on element: "<<pos;

  if(!board_logic.open_field(pos)) return;

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
