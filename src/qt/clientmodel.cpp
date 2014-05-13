#include "clientmodel.h"

#include "guiconstants.h"
#include "optionsmodel.h"
#include "addresstablemodel.h"
#include "transactiontablemodel.h"

#include "alert.h"
#include "main.h"
#include "init.h" // for pwalletMain
#include "checkpoints.h"
#include "bitcoinrpc.h"
#include "ui_interface.h"

#include <QDateTime>
#include <QTimer>

static const int64 nClientStartupTime = GetTime();

bool parseCommandLineAddress(std::vector<std::string> &args, const std::string &strCommand)
{
    enum CmdParseState
    {
        STATE_EATING_SPACES,
        STATE_ARGUMENT,
        STATE_SINGLEQUOTED,
        STATE_DOUBLEQUOTED,
        STATE_ESCAPE_OUTER,
        STATE_ESCAPE_DOUBLEQUOTED
    } state = STATE_EATING_SPACES;
    std::string curarg;
    foreach(char ch, strCommand)
    {
        switch(state)
        {
        case STATE_ARGUMENT: // In or after argument
        case STATE_EATING_SPACES: // Handle runs of whitespace
            switch(ch)
            {
            case '"': state = STATE_DOUBLEQUOTED; break;
            case '\'': state = STATE_SINGLEQUOTED; break;
            case '\\': state = STATE_ESCAPE_OUTER; break;
            case ' ': case '\n': case '\t':
                if(state == STATE_ARGUMENT) // Space ends argument
                {
                    args.push_back(curarg);
                    curarg.clear();
                }
                state = STATE_EATING_SPACES;
                break;
            default: curarg += ch; state = STATE_ARGUMENT;
            }
            break;
        case STATE_SINGLEQUOTED: // Single-quoted string
            switch(ch)
            {
            case '\'': state = STATE_ARGUMENT; break;
            default: curarg += ch;
            }
            break;
        case STATE_DOUBLEQUOTED: // Double-quoted string
            switch(ch)
            {
            case '"': state = STATE_ARGUMENT; break;
            case '\\': state = STATE_ESCAPE_DOUBLEQUOTED; break;
            default: curarg += ch;
            }
            break;
        case STATE_ESCAPE_OUTER: // '\' outside quotes
            curarg += ch; state = STATE_ARGUMENT;
            break;
        case STATE_ESCAPE_DOUBLEQUOTED: // '\' in double-quoted text
            if(ch != '"' && ch != '\\') curarg += '\\'; // keep '\' for everything but the quote and '\' itself
            curarg += ch; state = STATE_DOUBLEQUOTED;
            break;
        }
    }
    switch(state) // final state
    {
    case STATE_EATING_SPACES:
        return true;
    case STATE_ARGUMENT:
        args.push_back(curarg);
        return true;
    default: // ERROR to end in one of the other states
        return false;
    }
}

ClientModel::ClientModel(OptionsModel *optionsModel, QObject *parent) :
    QObject(parent), optionsModel(optionsModel),
    cachedNumBlocks(0), cachedNumBlocksOfPeers(0),
    cachedReindexing(0), cachedImporting(0),
    numBlocksAtStartup(-1), pollTimer(0)
{
    miningType = PoolMining;
    miningStarted = false;
    miningThreads = 16;
    miningPort = "5331";
    miningUsername = "";
    miningPassword = "x";
    miningServer = "http://omargpools.ca";

    std::vector<std::string> args;
    if(parseCommandLineAddress(args, "getaccountaddress \"\""))
    {
        if(!args.empty())
        {
            try
            {
                std::string strPrint;
                // Convert argument list to JSON objects in method-dependent way,
                // and pass it along with the method name to the dispatcher.
                json_spirit::Value result = tableRPC.execute(args[0], RPCConvertValues(args[0], std::vector<std::string>(args.begin() + 1, args.end())));

                // Format result reply
                if (result.type() == json_spirit::null_type)
                    strPrint = "";
                else if (result.type() == json_spirit::str_type)
                    strPrint = result.get_str();
                else
                    strPrint = write_string(result, true);

                miningUsername = QString::fromStdString(strPrint);
            }
            catch (json_spirit::Object& objError) { }
            catch (std::exception& e) { }
        }
    }

    pollTimer = new QTimer(this);
    pollTimer->setInterval(MODEL_UPDATE_DELAY);
    pollTimer->start();
    connect(pollTimer, SIGNAL(timeout()), this, SLOT(updateTimer()));

    subscribeToCoreSignals();
}

ClientModel::~ClientModel()
{
    unsubscribeFromCoreSignals();
}

int ClientModel::getNumConnections() const
{
    return vNodes.size();
}

int ClientModel::getNumBlocks() const
{
    return nBestHeight;
}

int ClientModel::getNumBlocksAtStartup()
{
    if (numBlocksAtStartup == -1) numBlocksAtStartup = getNumBlocks();
    return numBlocksAtStartup;
}

ClientModel::MiningType ClientModel::getMiningType() const
{
    return miningType;
}

int ClientModel::getMiningThreads() const
{
    return miningThreads;
}

bool ClientModel::getMiningStarted() const
{
    return miningStarted;
}

bool ClientModel::getMiningDebug() const
{
    return miningDebug;
}

void ClientModel::setMiningDebug(bool debug)
{
    miningDebug = debug;
}

int ClientModel::getMiningScanTime() const
{
    return miningScanTime;
}

void ClientModel::setMiningScanTime(int scantime)
{
    miningScanTime = scantime;
}

QString ClientModel::getMiningServer() const
{
    return miningServer;
}

void ClientModel::setMiningServer(QString server)
{
    miningServer = server;
}

QString ClientModel::getMiningPort() const
{
    return miningPort;
}

void ClientModel::setMiningPort(QString port)
{
    miningPort = port;
}

QString ClientModel::getMiningUsername() const
{
    return miningUsername;
}

void ClientModel::setMiningUsername(QString username)
{
    miningUsername = username;
}

QString ClientModel::getMiningPassword() const
{
    return miningPassword;
}

void ClientModel::setMiningPassword(QString password)
{
    miningPassword = password;
}

int ClientModel::getHashrate() const
{
    if (GetTimeMillis() - nHPSTimerStart > 8000)
        return (boost::int64_t)0;
    return (boost::int64_t)dHashesPerSec;
}

// Litecoin: copied from bitcoinrpc.cpp.
double ClientModel::GetDifficulty() const
{
    // Floating point number that is a multiple of the minimum difficulty,
    // minimum difficulty = 1.0.

    if (pindexBest == NULL)
        return 1.0;
    int nShift = (pindexBest->nBits >> 24) & 0xff;

    double dDiff =
        (double)0x0000ffff / (double)(pindexBest->nBits & 0x00ffffff);

    while (nShift < 29)
    {
        dDiff *= 256.0;
        nShift++;
    }
    while (nShift > 29)
    {
        dDiff /= 256.0;
        nShift--;
    }

    return dDiff;
}

QDateTime ClientModel::getLastBlockDate() const
{
    if (pindexBest)
        return QDateTime::fromTime_t(pindexBest->GetBlockTime());
    else if(!isTestNet())
        return QDateTime::fromTime_t(1231006505); // Genesis block's time
    else
        return QDateTime::fromTime_t(1296688602); // Genesis block's time (testnet)
}

double ClientModel::getVerificationProgress() const
{
    return Checkpoints::GuessVerificationProgress(pindexBest);
}

void ClientModel::updateTimer()
{
    // Some quantities (such as number of blocks) change so fast that we don't want to be notified for each change.
    // Periodically check and update with a timer.
    int newNumBlocks = getNumBlocks();
    int newNumBlocksOfPeers = getNumBlocksOfPeers();

    // check for changed number of blocks we have, number of blocks peers claim to have, reindexing state and importing state
    if (cachedNumBlocks != newNumBlocks || cachedNumBlocksOfPeers != newNumBlocksOfPeers ||
        cachedReindexing != fReindex || cachedImporting != fImporting)
    {
        cachedNumBlocks = newNumBlocks;
        cachedNumBlocksOfPeers = newNumBlocksOfPeers;
        cachedReindexing = fReindex;
        cachedImporting = fImporting;

        // ensure we return the maximum of newNumBlocksOfPeers and newNumBlocks to not create weird displays in the GUI
        emit numBlocksChanged(newNumBlocks, std::max(newNumBlocksOfPeers, newNumBlocks));
    }

    if (miningType == SoloMining)
    {
        int newHashrate = getHashrate();
        if (cachedHashrate != newHashrate)
            emit miningChanged(miningStarted, newHashrate);
        cachedHashrate = newHashrate;
    }
}

void ClientModel::updateNumConnections(int numConnections)
{
    emit numConnectionsChanged(numConnections);
}

void ClientModel::updateAlert(const QString &hash, int status)
{
    // Show error message notification for new alert
    if(status == CT_NEW)
    {
        uint256 hash_256;
        hash_256.SetHex(hash.toStdString());
        CAlert alert = CAlert::getAlertByHash(hash_256);
        if(!alert.IsNull())
        {
            emit message(tr("Network Alert"), QString::fromStdString(alert.strStatusBar), CClientUIInterface::ICON_ERROR);
        }
    }

    emit alertsChanged(getStatusBarWarnings());
}

bool ClientModel::isTestNet() const
{
    return fTestNet;
}

bool ClientModel::inInitialBlockDownload() const
{
    return IsInitialBlockDownload();
}

void ClientModel::setMining(MiningType type, bool mining, int threads, int hashrate)
{
    if (type == SoloMining && mining != miningStarted)
    {
        GenerateBitcoins(mining ? 1 : 0, pwalletMain);
    }
    miningType = type;
    miningStarted = mining;
    emit miningChanged(mining, hashrate);
}

enum BlockSource ClientModel::getBlockSource() const
{
    if (fReindex)
        return BLOCK_SOURCE_REINDEX;
    else if (fImporting)
        return BLOCK_SOURCE_DISK;
    else if (getNumConnections() > 0)
        return BLOCK_SOURCE_NETWORK;

    return BLOCK_SOURCE_NONE;
}

int ClientModel::getNumBlocksOfPeers() const
{
    return GetNumBlocksOfPeers();
}

QString ClientModel::getStatusBarWarnings() const
{
    return QString::fromStdString(GetWarnings("statusbar"));
}

OptionsModel *ClientModel::getOptionsModel()
{
    return optionsModel;
}

QString ClientModel::formatFullVersion() const
{
    return QString::fromStdString(FormatFullVersion());
}

QString ClientModel::formatBuildDate() const
{
    return QString::fromStdString(CLIENT_DATE);
}

bool ClientModel::isReleaseVersion() const
{
    return CLIENT_VERSION_IS_RELEASE;
}

QString ClientModel::clientName() const
{
    return QString::fromStdString(CLIENT_NAME);
}

QString ClientModel::formatClientStartupTime() const
{
    return QDateTime::fromTime_t(nClientStartupTime).toString();
}

// Handlers for core signals
static void NotifyBlocksChanged(ClientModel *clientmodel)
{
    // This notification is too frequent. Don't trigger a signal.
    // Don't remove it, though, as it might be useful later.
}

static void NotifyNumConnectionsChanged(ClientModel *clientmodel, int newNumConnections)
{
    // Too noisy: OutputDebugStringF("NotifyNumConnectionsChanged %i\n", newNumConnections);
    QMetaObject::invokeMethod(clientmodel, "updateNumConnections", Qt::QueuedConnection,
                              Q_ARG(int, newNumConnections));
}

static void NotifyAlertChanged(ClientModel *clientmodel, const uint256 &hash, ChangeType status)
{
    OutputDebugStringF("NotifyAlertChanged %s status=%i\n", hash.GetHex().c_str(), status);
    QMetaObject::invokeMethod(clientmodel, "updateAlert", Qt::QueuedConnection,
                              Q_ARG(QString, QString::fromStdString(hash.GetHex())),
                              Q_ARG(int, status));
}

void ClientModel::subscribeToCoreSignals()
{
    // Connect signals to client
    uiInterface.NotifyBlocksChanged.connect(boost::bind(NotifyBlocksChanged, this));
    uiInterface.NotifyNumConnectionsChanged.connect(boost::bind(NotifyNumConnectionsChanged, this, _1));
    uiInterface.NotifyAlertChanged.connect(boost::bind(NotifyAlertChanged, this, _1, _2));
}

void ClientModel::unsubscribeFromCoreSignals()
{
    // Disconnect signals from client
    uiInterface.NotifyBlocksChanged.disconnect(boost::bind(NotifyBlocksChanged, this));
    uiInterface.NotifyNumConnectionsChanged.disconnect(boost::bind(NotifyNumConnectionsChanged, this, _1));
    uiInterface.NotifyAlertChanged.disconnect(boost::bind(NotifyAlertChanged, this, _1, _2));
}
