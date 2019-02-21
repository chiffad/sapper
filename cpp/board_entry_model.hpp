#pragma once

#include <QAbstractListModel>
#include <memory>


namespace sapper
{

class BoardEntryModel : public QAbstractListModel
{
  Q_OBJECT

public:
  BoardEntryModel();
  ~BoardEntryModel();

  int rowCount([[maybe_unused]] const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

private:
  struct impl_t;
  std::unique_ptr<impl_t> impl;
};

} //namespace sapper
