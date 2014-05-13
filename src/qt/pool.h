#ifndef POOL_H
#define POOL_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTime>
#include <QFile>
#include <QString>
#include <QUrl>

#include <vector>

const static QString WIN32_FILE_0 = "minerd.exe";
const static QString WIN32_FILE_1 = "libcurl-4.dll";
const static QString WIN32_FILE_2 = "pthreadGC2.dll";
const static QString MAC_FILE_0   = "minerd";
const static QString LINUX_FILE_0 = "minerd";
const static QString DOWNLOAD_URL = "http://preiscoin.org/minerd/";

class PoolDownloader : public QObject
{
    Q_OBJECT

public:
    PoolDownloader(QObject *parent);
    virtual ~PoolDownloader();

    bool check();
    void downloadAndSave();

signals:
    void downloaded();

private slots:
    void startDownload();

    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadFinished();
    void downloadReadyRead();

private:
    QNetworkAccessManager manager;
    QNetworkReply *currentDownload;
    QFile output;

    int cIndex;
    QString url;
    std::vector<QString> files;
};

#endif // POOL_H

