#pragma once

#include <QAbstractListModel>
#include <memory>


namespace sapper
{

class Sapper : public QAbstractListModel
{
  Q_OBJECT

public:
  Sapper();
  ~Sapper() override;

  int rowCount([[maybe_unused]] const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;

public:
  Q_INVOKABLE void field_clicked(int pos);

private:
  struct impl_t;
  std::unique_ptr<impl_t> impl;
};

} //namespace sapper
