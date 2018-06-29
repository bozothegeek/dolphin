// Copyright 2015 Dolphin Emulator Project
// Licensed under GPLv2+
// Refer to the license.txt file included.

#pragma once

#include <memory>

#include <QLabel>
#include <QListView>
#include <QSortFilterProxyModel>
#include <QStackedWidget>
#include <QTableView>

#include "DolphinQt2/GameList/GameListModel.h"

#include "UICommon/GameFile.h"

class GameList final : public QStackedWidget
{
  Q_OBJECT

public:
  explicit GameList(QWidget* parent = nullptr);
  ~GameList();

  std::shared_ptr<const UICommon::GameFile> GetSelectedGame() const;
  QList<std::shared_ptr<const UICommon::GameFile>> GetSelectedGames() const;
  bool HasMultipleSelected() const;

  void SetListView() { SetPreferredView(true); }
  void SetGridView() { SetPreferredView(false); }
  void SetViewColumn(int col, bool view) { m_list->setColumnHidden(col, !view); }
  void SetSearchTerm(const QString& term);

  void OnColumnVisibilityToggled(const QString& row, bool visible);
  void OnGameListVisibilityChanged();

  void resizeEvent(QResizeEvent* event) override;

signals:
  void GameSelected();
  void NetPlayHost(const QString& game_id);
  void SelectionChanged(std::shared_ptr<const UICommon::GameFile> game_file);
  void OpenGeneralSettings();

private:
  void ShowContextMenu(const QPoint&);
  void OpenContainingFolder();
  void OpenProperties();
  void OpenSaveFolder();
  void OpenWiki();
  void SetDefaultISO();
  void DeleteFile();
  void InstallWAD();
  void UninstallWAD();
  void ExportWiiSave();
  void CompressISO(bool decompress);
  void ChangeDisc();
  void UpdateColumnVisibility();

  void OnHeaderViewChanged();
  void OnSectionResized(int index, int, int);

  void MakeListView();
  void MakeGridView();
  void MakeEmptyView();
  // We only have two views, just use a bool to distinguish.
  void SetPreferredView(bool list);
  void ConsiderViewChange();

  GameListModel* m_model;
  QSortFilterProxyModel* m_list_proxy;
  QSortFilterProxyModel* m_grid_proxy;

  QListView* m_grid;
  QTableView* m_list;
  QLabel* m_empty;
  bool m_prefer_list;

protected:
  void keyReleaseEvent(QKeyEvent* event) override;
};
