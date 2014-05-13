#include "update.h"

#include <QTimer>
#include <QFileInfo>

UpdateManager::UpdateManager(QObject *parent): QObject(parent)
{
}

UpdateManager::~UpdateManager()
{
}

void UpdateManager::checkUpdate()
{
    QNetworkRequest request(PREISCOIN_UPDATE_URL);
    updateReply = manager.get(request);

    connect(updateReply, SIGNAL(finished()), this, SLOT(update()));
}

bool UpdateManager::isLatest() const
{
    return mLatest <= PREISCOIN_VERSION;
}

void UpdateManager::update()
{
    QString ver(updateReply->readAll().data());
    mLatest = ver.toInt();
    latest(isLatest());
}

void UpdateManager::downloadAndSave(const QString& inFilename)
{
    mFile = inFilename;
    QTimer::singleShot(0, this, SLOT(startDownload()));
}

void UpdateManager::startDownload()
{
    QString latestUrl = PREISCOIN_LATEST_URL;

    #if defined(Q_OS_WIN)
    latestUrl += ".exe";
    #elif defined(Q_OS_MACX)
    latestUrl += ".dmg";
    #endif

    QUrl url = QUrl(latestUrl);
    QString filename = saveFileName(url);
    if(!mFile.isEmpty()) filename = mFile;

    #if defined(Q_OS_WIN)
    if(!filename.endsWith(".exe")) {
        filename.append(".exe");
    }
    #elif defined(Q_OS_MACX)
    if(!filename.endsWith(".dmg")) {
        filename.append(".dmg");
    }
    #endif

    output.setFileName(filename);

    if(!output.open(QIODevice::WriteOnly)) {
        fprintf(stderr, "Problem opening save file '%s' for download '%s': %s\n",
                qPrintable(filename), url.toEncoded().constData(),
                qPrintable(output.errorString()));

        return;
    }

    QNetworkRequest request(url);
    currentDownload = manager.get(request);

    connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)), SLOT(downloadProgress(qint64,qint64)));
    connect(currentDownload, SIGNAL(finished()), SLOT(downloadFinished()));
    connect(currentDownload, SIGNAL(readyRead()), SLOT(downloadReadyRead()));

    printf("Downloading %s...\n", url.toEncoded().constData());
    downloadTime.start();
}

void UpdateManager::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
}

void UpdateManager::downloadFinished()
{
    output.close();
    currentDownload->deleteLater();

    downloaded();
}

void UpdateManager::downloadReadyRead()
{
    output.write(currentDownload->readAll());
}

QString UpdateManager::saveFileName(const QUrl &url)
{
    QString path = url.path();
    QString basename = QFileInfo(path).fileName();

    if(basename.isEmpty()) {
        basename = "preiscoin-qt";
    }

    if(QFile::exists(basename))
    {
        int i = 0;
        basename += '.';

        while(QFile::exists(basename + QString::number(i))) {
            ++i;
        }

        basename += QString::number(i);
    }

    return basename;
}
