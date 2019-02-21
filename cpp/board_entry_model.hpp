#pragma once

#include "board_logic.hpp"

#include <QAbstractListModel>
#include <QObject>


namespace sapper
{

class BoardEntryModel : public QAbstractListModel
{
  Q_OBJECT

public:
  explicit BoardEntryModel(QObject *parent = 0)
    : QAbstractListModel(parent)
  {
  }

  int rowCount([[maybe_unused]] const QModelIndex &parent = QModelIndex()) const override
  {
    return board.get_board().size();
  }

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
  {
    int row = index.row();
    if(!index.isValid() || row >= rowCount()) return QVariant();

    switch(role)
    {
      case Qt::DisplayRole: return "b";//board.get_board()[row];
    }

    return QVariant();
  }

private:
  board_logic_t board;
};

} //namespace sapper
