#ifndef UPDATE_H
#define UPDATE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTime>
#include <QFile>
#include <QString>
#include <QUrl>

const static QString PREISCOIN_UPDATE_URL = "http://preiscoin.org/update.txt";
const static QString PREISCOIN_LATEST_URL = "http://preiscoin.org/preiscoin-latest";
const static int PREISCOIN_VERSION = 2;

class UpdateManager : public QObject
{
    Q_OBJECT

public:

    UpdateManager(QObject *parent);
    virtual ~UpdateManager();

    void checkUpdate();
    bool isLatest() const;
    void downloadAndSave(const QString& inFilename);

signals:
    void latest(bool);
    void downloaded();

private slots:
    void update();
    void startDownload();

    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyRead();

private:
    QString saveFileName(const QUrl &url);

    QNetworkAccessManager manager;
    QNetworkReply *updateReply, *currentDownload;
    QFile output;
    QTime downloadTime;
    QString mFile;

    int mLatest;
};

#endif // UPDATE_H

