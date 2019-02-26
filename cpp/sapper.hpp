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
  Q_INVOKABLE void change_click_mode();

  Q_PROPERTY(int click_mode READ click_mode NOTIFY click_modeChanged);
  int click_mode() const;

  Q_PROPERTY(int game_status READ game_status NOTIFY game_statusChanged);
  int game_status() const;

signals:
  void game_statusChanged();
  void click_modeChanged();

private:
  struct impl_t;
  std::unique_ptr<impl_t> impl;
};

} //namespace sapper
