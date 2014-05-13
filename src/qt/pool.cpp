#include "pool.h"

#include <QTimer>
#include <QFileInfo>
#include <QDir>
#include <QProcess>

PoolDownloader::PoolDownloader(QObject *parent): QObject(parent)
{
    cIndex = 0;

    #if defined(Q_OS_WIN)
    url = DOWNLOAD_URL + "win32/";
    files.push_back(WIN32_FILE_0);
    files.push_back(WIN32_FILE_1);
    files.push_back(WIN32_FILE_2);
    #elif defined(Q_OS_MACX)
    url = DOWNLOAD_URL + "mac/";
    files.push_back(MAC_FILE_0);
    #else
    url = DOWNLOAD_URL + "linux/";
    files.push_back(LINUX_FILE_0);
    #endif
}

PoolDownloader::~PoolDownloader()
{
}

bool PoolDownloader::check()
{
    bool result = true;

    for(std::vector<QString>::iterator it = files.begin(); it != files.end(); ++it)
    {
        if(!QFile::exists(QDir::current().filePath(*it)))
        {
            result = false;
            break;
        }
    }

    return result;
}

void PoolDownloader::downloadAndSave()
{
    QTimer::singleShot(0, this, SLOT(startDownload()));
}

void PoolDownloader::startDownload()
{
    QString filename = files.at(cIndex);
    QUrl fileUrl = QUrl(url + filename);

    output.setFileName(filename);
    if(!output.open(QIODevice::WriteOnly)) {
        fprintf(stderr, "Problem opening save file '%s' for download '%s': %s\n",
                qPrintable(filename), fileUrl.toEncoded().constData(),
                qPrintable(output.errorString()));

        return;
    }

    QNetworkRequest request(fileUrl);
    currentDownload = manager.get(request);

    connect(currentDownload, SIGNAL(downloadProgress(qint64,qint64)), SLOT(downloadProgress(qint64,qint64)));
    connect(currentDownload, SIGNAL(finished()), SLOT(downloadFinished()));
    connect(currentDownload, SIGNAL(readyRead()), SLOT(downloadReadyRead()));

    printf("Downloading %s...\n", fileUrl.toEncoded().constData());
}


void PoolDownloader::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
}

void PoolDownloader::downloadFinished()
{
    output.close();
	
    #if !defined(Q_OS_WIN)
	QProcess::execute("chmod 777 " + QDir::current().filePath(files.at(cIndex)));
    #endif

    if(++cIndex < files.size()) {
        startDownload();
    }
    else
    {
        currentDownload->deleteLater();
        downloaded();
    }
}

void PoolDownloader::downloadReadyRead()
{
    output.write(currentDownload->readAll());
}
