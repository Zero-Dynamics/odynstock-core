// Copyright (c) 2011-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef STOCK_QT_WALLETFRAME_H
#define STOCK_QT_WALLETFRAME_H

#include <QFrame>
#include <QMap>
#include <QHBoxLayout>
#include <QPushButton>


class StockGUI;
class ClientModel;
class PlatformStyle;
class SendCoinsRecipient;
class WalletModel;
class WalletView;

QT_BEGIN_NAMESPACE
class QStackedWidget;
QT_END_NAMESPACE

class WalletFrame : public QFrame
{
    Q_OBJECT

public:
    explicit WalletFrame(const PlatformStyle *platformStyle, StockGUI *_gui = 0);
    ~WalletFrame();

    void setClientModel(ClientModel *clientModel);

    bool addWallet(const QString& name, WalletModel *walletModel);
    bool setCurrentWallet(const QString& name);
    bool removeWallet(const QString &name);
    void removeAllWallets();

    bool handlePaymentRequest(const SendCoinsRecipient& recipient);

    WalletView *currentWalletView();

    QWidget *topMenu;
    QVBoxLayout *menuLayout;
    QVBoxLayout *headerLayout;
    QHBoxLayout *headLayout;
    QHBoxLayout *balanceLayout;
    QHBoxLayout *statusLayout;

Q_SIGNALS:
    /** Notify that the user has requested more information about the out-of-sync warning */
    void requestedSyncWarningInfo();

    void daoEntriesChanged(int count);

private:
    QStackedWidget *walletStack;
    StockGUI *gui;
    ClientModel *clientModel;
    QMap<QString, WalletView*> mapWalletViews;

    bool bOutOfSync;

    const PlatformStyle *platformStyle;


public Q_SLOTS:

    /** Switch to overview (home) page */
    void gotoOverviewPage();
    /** Switch to history (transactions) page */
    void gotoHistoryPage();
    /** Switch to settings page */
    void gotoSettingsPage();
    /** Switch to community fund page */
    void gotoCommunityFundPage();
    /** Switch to receive coins page */
    void gotoReceiveCoinsPage();
    /** Switch to send coins page */
    void gotoSendCoinsPage(QString addr = "");
    void gotoRequestPaymentPage();

    /** Show Sign/Verify Message dialog and switch to sign message tab */
    void gotoSignMessageTab(QString addr = "");
    /** Show Sign/Verify Message dialog and switch to verify message tab */
    void gotoVerifyMessageTab(QString addr = "");



    /** Encrypt the wallet */
    void encryptWallet(bool status);
    /** Encrypt the wallet txdata */
    void encryptTx();
    /** Backup the wallet */
    void backupWallet();
    /** Change encrypted wallet passphrase */
    void changePassphrase();
    /** Ask for passphrase to unlock wallet temporarily */
    void unlockWallet();
    void unlockWalletStaking();
    void lockWallet();
    void importPrivateKey();
    void exportMasterPrivateKeyAction();
    void exportMnemonicAction();

    void setStakingStats(QString day, QString week, QString month, QString year, QString all);

    void splitRewards();

    /** Show used sending addresses */
    void usedSendingAddresses();
    /** Show used receiving addresses */
    void usedReceivingAddresses();
    /** Pass on signal over requested out-of-sync-warning information */
    void outOfSyncWarningClicked();

    void onDaoEntriesChanged(int count);
};

#endif // STOCK_QT_WALLETFRAME_H
