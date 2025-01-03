#ifndef DLG_CONNECT_H
#define DLG_CONNECT_H

#include "../server/handle_public_servers.h"
#include "../server/user/user_info_connection.h"
#include "../utility/macros.h"

#include <QDialog>
#include <QLineEdit>

class QCheckBox;
class QComboBox;
class QGridLayout;
class QGroupBox;
class QHBoxLayout;
class QLabel;
class QPushButton;
class QRadioButton;
class QVBoxLayout;

class DlgConnect : public QDialog
{
    Q_OBJECT
signals:
    void sigStartForgotPasswordRequest();
    void sigPublicServersDownloaded();

public:
    explicit DlgConnect(QWidget *parent = nullptr);
    ~DlgConnect() override;
    QString getHost() const;
    int getPort() const
    {
        return portEdit->text().toInt();
    }
    QString getPlayerName() const
    {
        return playernameEdit->text();
    }
    QString getPassword() const
    {
        return passwordEdit->text();
    }

public slots:
    void downloadThePublicServers();

private slots:
    void actOk();

    void passwordSaved(QT_STATE_CHANGED_T state);
    void previousHostSelected(bool state);
    void newHostSelected(bool state);
    void actForgotPassword();
    void actRemoveSavedServer();
    void updateDisplayInfo(const QString &saveName);
    void preRebuildComboBoxList();
    void rebuildComboBoxList(int failure = -1);

private:
    QGridLayout *connectionLayout, *loginLayout, *serverInfoLayout, *grid;
    QHBoxLayout *newHolderLayout, *forgotPasswordLayout;
    QGroupBox *loginGroupBox, *serverInfoGroupBox, *restrictionsGroupBox;
    QVBoxLayout *mainLayout;
    QLabel *hostLabel, *portLabel, *playernameLabel, *passwordLabel, *saveLabel, *serverIssuesLabel,
        *serverContactLabel, *serverContactLink, *forgotPasswordLabel;
    QLineEdit *hostEdit, *portEdit, *playernameEdit, *passwordEdit, *saveEdit;
    QCheckBox *savePasswordCheckBox, *autoConnectCheckBox;
    QComboBox *previousHosts;
    QRadioButton *newHostButton, *previousHostButton;
    QPushButton *btnConnect, *btnForgotPassword, *btnRefreshServers, *btnDeleteServer;
    QMap<QString, std::pair<QString, UserConnection_Information>> savedHostList;
    HandlePublicServers *hps;
    const QString placeHolderText = tr("Downloading...");
};
#endif
