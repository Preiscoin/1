#ifndef MININGPAGE_H
#define MININGPAGE_H

#include "clientmodel.h"

#include <QWidget>

#include <QDir>
#include <QFile>
#include <QProcess>
#include <QTime>
#include <QTimer>
#include <QStringList>
#include <QMap>
#include <QSettings>

#include "configfile.h"
#include "update.h"
#include "pool.h"

// Log types
#define STARTED 0
#define SHARE_SUCCESS 1
#define SHARE_FAIL 2
#define ERROR 3
#define LONGPOLL 4

#define TIMER_INTERVAL 1000

namespace Ui {
    class MiningPage;
}
class ClientModel;

class MiningPage : public QWidget
{
    Q_OBJECT

public:
    explicit MiningPage(QWidget *parent = 0);
    ~MiningPage();

    void setHashes(const qint64 hashes);

    bool minerActive;
    bool minerSet;

    QProcess *minerProcess;


    QMap<int, double> threadSpeed;

    QTimer *readTimer;

    int acceptedShares;
    int rejectedShares;

    int roundAcceptedShares;
    int roundRejectedShares;

    int initThreads;


public slots:
    void startPressed();

    void startPoolMining();
    void stopPoolMining();

    void updateSpeed();
    void updateSpeedSolo(bool mining, int count);

    void setModel(ClientModel *model);

    void loadSettings();
    void saveSettings();

    void reportToList(QString, int, QString);

    void minerStarted();

    void minerError(QProcess::ProcessError);
    void minerFinished();

    void readProcessOutput();

    QString getTime(QString);
    void enableMiningControls(bool enable);
    void enablePoolMiningControls(bool enable);
    ClientModel::MiningType getMiningType();
    void typeChanged(int index);
    void debugToggled(bool checked);

private slots:

private:
    Ui::MiningPage *ui;
    ClientModel *model;

    ConfigFile config;
    qint64 hashes;
    QVector<double> chartX, chartY;
    int hTime, maxRange;
    PoolDownloader poolDownloader;

    void resetMiningButton();
};

#endif // MININGPAGE_H
