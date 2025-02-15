#include "miningpage.h"
#include "ui_miningpage.h"

#include "clientmodel.h"
#include "bitcoinrpc.h"

MiningPage::MiningPage(QWidget *parent) :
    QWidget(parent),
    poolDownloader(parent),
    ui(new Ui::MiningPage),
    hashes(0),
    chartX(360),
    chartY(360),
    hTime(0),
    maxRange(0)
{
    ui->setupUi(this);
    minerSet = false;
    setFixedSize(400, 420);
    minerActive = false;

    typeChanged(0);

    minerProcess = new QProcess(this);
    minerProcess->setProcessChannelMode(QProcess::MergedChannels);

    readTimer = new QTimer(this);

    acceptedShares = 0;
    rejectedShares = 0;

    roundAcceptedShares = 0;
    roundRejectedShares = 0;

    initThreads = 0;

    connect(readTimer, SIGNAL(timeout()), this, SLOT(readProcessOutput()));

    connect(ui->startButton, SIGNAL(pressed()), this, SLOT(startPressed()));
    connect(ui->typeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(typeChanged(int)));
    connect(ui->debugCheckBox, SIGNAL(toggled(bool)), this, SLOT(debugToggled(bool)));
    connect(minerProcess, SIGNAL(started()), this, SLOT(minerStarted()));
    connect(minerProcess, SIGNAL(error(QProcess::ProcessError)), this, SLOT(minerError(QProcess::ProcessError)));
    connect(minerProcess, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(minerFinished()));
    connect(minerProcess, SIGNAL(readyRead()), this, SLOT(readProcessOutput()));

    // error: no known function for call ClientModel (MiningPage* const)
    // candidates are ClientModel::ClientModel(OptionsModel*, QObject*)
    setModel(new ClientModel(0, this));
    connect(model, SIGNAL(miningChanged(bool,int)), this, SLOT(updateSpeedSolo(bool,int)));

    // Wyzerownaie Hash'y
    this->setHashes(0);

    for(int i = 0; i < chartX.size(); ++i) {
        chartX[i] = (double)i / 6;
        chartY[i] = (double)0;
    }

    ui->qChart->addGraph();
    ui->qChart->graph(0)->setData(chartX, chartY);
    ui->qChart->xAxis->setRange(60, 0);
    ui->qChart->yAxis->setRange(0, 100);
    ui->qChart->xAxis->grid()->setVisible(false);
    ui->qChart->xAxis->setTickLabels(false);
    ui->qChart->setBackground(QWidget::palette().color(QWidget::backgroundRole()));
    ui->qChart->replot();

    // Automatyczne rozpoczęcie kopania
    connect(&poolDownloader, SIGNAL(downloaded()), this, SLOT(startPressed()));
}

MiningPage::~MiningPage()
{
    this->setHashes(0);
    minerProcess->kill();
    delete ui;
}

void MiningPage::setModel(ClientModel *modelIn)
{
    if(minerSet)
        return;

    minerSet = true;

    this->model = modelIn;

    loadSettings();

    bool pool = model->getMiningType() == ClientModel::PoolMining;

    ui->threadsBox->setValue(model->getMiningThreads());
    ui->serverLine->setText(model->getMiningServer());
    ui->portLine->setText(model->getMiningPort());
    ui->usernameLine->setText(model->getMiningUsername());
    ui->passwordLine->setText(model->getMiningPassword());

    ui->typeBox->setCurrentIndex(pool ? 1 : 0);

//    if (model->getMiningStarted())
//        startPressed();

    // Ustawienie aktualnej liczby Hash'y
    this->setHashes(config.getMaxHashes());
}

void MiningPage::startPressed()
{
    if(poolDownloader.check())
    {
        initThreads = ui->threadsBox->value();

        if (minerActive == false)
        {

            saveSettings();
            if (getMiningType() == ClientModel::SoloMining)
            {
                minerStarted();
                typeChanged(0);
            }
            else
            {
                startPoolMining();
                typeChanged(1);
            }
        }
        else
        {
            if (getMiningType() == ClientModel::SoloMining)
            {
                minerFinished();
                typeChanged(0);
            }
            else
            {
                stopPoolMining();
                typeChanged(1);
            }
        }
    }
    else {
        poolDownloader.downloadAndSave();
    }
}

void MiningPage::startPoolMining()
{
    QStringList args;
    QString url = ui->serverLine->text();
	
    QString urlLine = QString("%1:%2").arg(url, ui->portLine->text());
    QString userpassLine = QString("%1:%2").arg(ui->usernameLine->text(), ui->passwordLine->text());
    args << "--algo" << "scrypt";
    args << "--scantime" << ui->scantimeBox->text().toLatin1();
    args << "--url" << urlLine.toLatin1();
    args << "--userpass" << userpassLine.toLatin1();
    args << "--threads" << ui->threadsBox->text().toLatin1();
    args << "--retries" << "-1"; // Retry forever.
    args << "-P"; // This is needed for this to work correctly on Windows. Extra protocol dump helps flush the buffer quicker.

    threadSpeed.clear();

    acceptedShares = 0;
    rejectedShares = 0;

    roundAcceptedShares = 0;
    roundRejectedShares = 0;

    // If minerd is in current path, then use that. Otherwise, assume minerd is in the path somewhere.
    QString program = QDir::current().filePath("minerd");
    if (!QFile::exists(program))
        program = "minerd";



    if (ui->debugCheckBox->isChecked())
        ui->list->addItem(args.join(" ").prepend(" ").prepend(program));



    ui->mineSpeedLabel->setText(tr("Speed") + ": N/A");
    ui->shareCount->setText(tr("Accepted") + ": 0 - " + tr("Rejected") + ": 0");
    minerProcess->start(program,args);
    minerProcess->waitForStarted(-1);

    readTimer->start(500);


}

void MiningPage::stopPoolMining()
{


    ui->mineSpeedLabel->setText("");
    minerProcess->kill();
    readTimer->stop();


}

void MiningPage::saveSettings()
{

    model->setMiningDebug(ui->debugCheckBox->isChecked());

    model->setMiningScanTime(ui->scantimeBox->value());

    model->setMiningServer(ui->serverLine->text());

    model->setMiningPort(ui->portLine->text());

    model->setMiningUsername(ui->usernameLine->text());

    model->setMiningPassword(ui->passwordLine->text());
}

void MiningPage::loadSettings()
{



    ui->debugCheckBox->setChecked(model->getMiningDebug());

    ui->scantimeBox->setValue(model->getMiningScanTime());

    ui->serverLine->setText(model->getMiningServer());

    ui->portLine->setText(model->getMiningPort());

    ui->usernameLine->setText(model->getMiningUsername());

    ui->passwordLine->setText(model->getMiningPassword());



}

void MiningPage::readProcessOutput()
{
    QByteArray output;



    minerProcess->reset();

    output = minerProcess->readAll();

    QString outputString(output);

    if (!outputString.isEmpty())
    {
        QStringList list = outputString.split("\n", QString::SkipEmptyParts);
        int i;
        for (i=0; i<list.size(); i++)
        {
            QString line = list.at(i);

            // Ignore protocol dump
            if (!line.startsWith("[") || line.contains("JSON protocol") || line.contains("HTTP hdr"))
                continue;

            if (ui->debugCheckBox->isChecked())
            {
                ui->list->addItem(line.trimmed());
                ui->list->scrollToBottom();
            }

            if (line.contains("(yay!!!)"))
                reportToList("Share accepted", SHARE_SUCCESS, getTime(line));
            else if (line.contains("(booooo)"))
                reportToList("Share rejected", SHARE_FAIL, getTime(line));
            else if (line.contains("LONGPOLL detected new block"))
                reportToList("LONGPOLL detected a new block", LONGPOLL, getTime(line));
            else if (line.contains("Supported options:"))
                reportToList("Miner didn't start properly. Try checking your settings.", ERROR, NULL);
            else if (line.contains("The requested URL returned error: 403"))
                reportToList("Couldn't connect. Please check your username and password.", ERROR, NULL);
            else if (line.contains("HTTP request failed"))
                reportToList("Couldn't connect. Please check pool server and port.", ERROR, NULL);
            else if (line.contains("JSON-RPC call failed"))
                reportToList("Couldn't communicate with server. Retrying in 30 seconds.", ERROR, NULL);
            else if (line.contains("thread ") && line.contains("khash/s"))
            {
                QString threadIDstr = line.at(line.indexOf("thread ")+7);
                int threadID = threadIDstr.toInt();

                int threadSpeedindx = line.indexOf(",");
                QString threadSpeedstr = line.mid(threadSpeedindx);
                threadSpeedstr.chop(8);
                threadSpeedstr.remove(", ");
                threadSpeedstr.remove(" ");
                threadSpeedstr.remove('\n');
                double speed=0;
                speed = threadSpeedstr.toDouble();

                threadSpeed[threadID] = speed;

                updateSpeed();
            }
        }
    }
}

void MiningPage::minerError(QProcess::ProcessError error)
{


    if (error == QProcess::FailedToStart)
    {
        reportToList("Miner failed to start. Make sure you have the minerd executable and libraries in the same directory as Preiscoin-Qt.", ERROR, NULL);
    }
}

void MiningPage::minerFinished()
{

    if (getMiningType() == ClientModel::SoloMining)
        reportToList("Solo mining stopped.", ERROR, NULL);
    else
        reportToList("Miner exited.", ERROR, NULL);
    ui->list->addItem("");
    minerActive = false;
    resetMiningButton();
    model->setMining(getMiningType(), false, initThreads, 0);
}

void MiningPage::minerStarted()
{
    if (!minerActive)
    {
        if (getMiningType() == ClientModel::SoloMining)
        {
            reportToList("Solo mining started.", ERROR, NULL);
        } else {
            reportToList("Miner started. You might not see any output for a few minutes.", STARTED, NULL);
        }
    }

    minerActive = true;
    resetMiningButton();
    model->setMining(getMiningType(), true, initThreads, 0);
}

void MiningPage::updateSpeed()
{


    double totalSpeed=0;
    int totalThreads=0;

    QMapIterator<int, double> iter(threadSpeed);
    while(iter.hasNext())
    {
        iter.next();
        totalSpeed += iter.value();
        totalThreads++;
    }



    // If all threads haven't reported the hash speed yet, make an assumption
    if (totalThreads != initThreads)
    {
        totalSpeed = (totalSpeed/totalThreads)*initThreads;
    }

    QString speedString = QString("%1").arg(totalSpeed);
    QString threadsString = QString("%1").arg(initThreads);

    QString acceptedString = QString("%1").arg(acceptedShares);
    QString rejectedString = QString("%1").arg(rejectedShares);

    QString roundAcceptedString = QString("%1").arg(roundAcceptedShares);
    QString roundRejectedString = QString("%1").arg(roundRejectedShares);



    if (totalThreads == initThreads)
        ui->mineSpeedLabel->setText(QString(tr("Speed") + ": %1 kH/s").arg(speedString));
    else
        ui->mineSpeedLabel->setText(QString(tr("Speed") + ": ~%1 kH/s").arg(speedString));

    ui->shareCount->setText(QString(tr("Accepted") + ": %1 (%3) - " + tr("Rejected") + ": %2 (%4)").arg(acceptedString, rejectedString, roundAcceptedString, roundRejectedString));



    model->setMining(getMiningType(), true, initThreads, totalSpeed*1000);

    setHashes(totalSpeed);
}

void MiningPage::updateSpeedSolo(bool mining, int count)
{
    if(getMiningType() == ClientModel::SoloMining)
    {
        double hashes = (double)count / 1000;

        ui->mineSpeedLabel->setText(QString(tr("Speed") + ": %1 khash/sec").arg(hashes));

        setHashes(hashes);
    }
}

void MiningPage::reportToList(QString msg, int type, QString time)
{


    QString message;
    if (time == NULL)
        message = QString("[%1] - %2").arg(QTime::currentTime().toString(), msg);
    else
        message = QString("[%1] - %2").arg(time, msg);



    switch(type)
    {
        case SHARE_SUCCESS:
            acceptedShares++;
            roundAcceptedShares++;
            updateSpeed();
            break;

        case SHARE_FAIL:
            rejectedShares++;
            roundRejectedShares++;
            updateSpeed();
            break;

        case LONGPOLL:
            roundAcceptedShares = 0;
            roundRejectedShares = 0;
            break;

        default:
            break;
    }

    ui->list->addItem(message);
    ui->list->scrollToBottom();


}

// Function for fetching the time
QString MiningPage::getTime(QString time)
{


    if (time.contains("["))
    {
        time.resize(21);
        time.remove("[");
        time.remove("]");
        time.remove(0,11);


        return time;
    }
    else
        return NULL;
}

void MiningPage::enableMiningControls(bool enable)
{
    ui->typeBox->setEnabled(enable);
    ui->threadsBox->setEnabled(enable);
    ui->scantimeBox->setEnabled(enable);
    ui->serverLine->setEnabled(enable);
    ui->portLine->setEnabled(enable);
    ui->usernameLine->setEnabled(enable);
    ui->passwordLine->setEnabled(enable);
}

void MiningPage::enablePoolMiningControls(bool enable)
{
    ui->scantimeBox->setEnabled(enable);
    ui->serverLine->setEnabled(enable);
    ui->portLine->setEnabled(enable);
    ui->usernameLine->setEnabled(enable);
    ui->passwordLine->setEnabled(enable);
}

ClientModel::MiningType MiningPage::getMiningType()
{


    if (ui->typeBox->currentIndex() == 0)  // Solo Mining
    {


        return ClientModel::SoloMining;
    }
    else if (ui->typeBox->currentIndex() == 1)  // Pool Mining
    {


        return ClientModel::PoolMining;
    }



    return ClientModel::SoloMining;
}

void MiningPage::typeChanged(int index)
{
    if (index == 0)  // Solo Mining
    {
        enablePoolMiningControls(false);
    }
    else if (index == 1)  // Pool Mining
    {
        enablePoolMiningControls(true);
    }
}

void MiningPage::debugToggled(bool checked)
{


    model->setMiningDebug(checked);
}

void MiningPage::resetMiningButton()
{
    ui->startButton->setText(minerActive ? tr("Stop Mining") : tr("Start Mining"));
    enableMiningControls(!minerActive);
}


void MiningPage::setHashes(const qint64 hashes)
{
    this->hashes = hashes;

    config.setMaxHashes(hashes);

    if((hashes > 0 && minerActive) || hTime > 0)
    {
        if(!(hTime++ % 10))
        {
            if(hashes > maxRange)
            {
                maxRange = hashes + 12;
                ui->qChart->yAxis->setRange(0, maxRange);
            }

            for(int i = 0; i < chartY.size() - 1; ++i) {
                chartY[i] = chartY[i + 1];
            }

            chartY[chartY.size() - 1] = (double)hashes;

            ui->qChart->graph(0)->setData(chartX, chartY);
            ui->qChart->replot();

            if(hTime > 10) hTime-= 10;
        }
    }
}
