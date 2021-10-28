// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2020-2021, The Monero Project.

#ifndef FEATHER_COINSWIDGET_H
#define FEATHER_COINSWIDGET_H

#include <QMenu>
#include <QWidget>
#include <QtSvg/QSvgWidget>

#include "appcontext.h"
#include "model/CoinsModel.h"
#include "model/CoinsProxyModel.h"
#include "libwalletqt/Coins.h"

namespace Ui {
    class CoinsWidget;
}

class CoinsWidget : public QWidget
{
Q_OBJECT

public:
    explicit CoinsWidget(QSharedPointer<AppContext> ctx, QWidget *parent = nullptr);
    void setModel(CoinsModel * model, Coins * coins);
    ~CoinsWidget() override;

public slots:
    void setSearchbarVisible(bool visible);
    void focusSearchbar();

private slots:
    void showHeaderMenu(const QPoint& position);
    void setShowSpent(bool show);
    void freezeAllSelected();
    void thawAllSelected();
    void viewOutput();
    void onSweepOutputs();
    void setSearchFilter(const QString &filter);
    void editLabel();

private:
    void freezeCoins(QStringList &pubkeys);
    void thawCoins(QStringList &pubkeys);

    enum copyField {
        PubKey = 0,
        KeyImage,
        TxID,
        Address,
        Label,
        Height,
        Amount
    };

    QScopedPointer<Ui::CoinsWidget> ui;
    QSharedPointer<AppContext> m_ctx;

    QMenu *m_contextMenu;
    QMenu *m_headerMenu;
    QMenu *m_copyMenu;
    QAction *m_showSpentAction;
    QAction *m_freezeOutputAction;
    QAction *m_freezeAllSelectedAction;
    QAction *m_thawOutputAction;
    QAction *m_thawAllSelectedAction;
    QAction *m_viewOutputAction;
    QAction *m_sweepOutputAction;
    QAction *m_sweepOutputsAction;
    QAction *m_editLabelAction;
    Coins *m_coins;
    CoinsModel * m_model;
    CoinsProxyModel * m_proxyModel;

    void showContextMenu(const QPoint & point);
    void copy(copyField field);
    CoinsInfo* currentEntry();
    QVector<CoinsInfo*> currentEntries();
    QStringList selectedPubkeys();
};


#endif //FEATHER_COINSWIDGET_H