#include <QQmlContext>
#include "CQmlAdapter.h"
#include "../include/Math/CGeometry.h"
#include "../include/Log/CLog.h"

#define EXCEPTION                   { CLog::writeStringInFile("log/exception.txt", QString("\t%0:%1(%2)").arg(QString("0x%1").arg(reinterpret_cast<quintptr>(this), QT_POINTER_SIZE * 2, 16, QChar('0'))).arg(__FILE__).arg(__LINE__)); }
#define EXCEPTION_LOG(sText)        { CLog::writeStringInFile("log/exception.txt", QString("\t%0:%1(%2): %3").arg(QString("0x%1").arg(reinterpret_cast<quintptr>(this), QT_POINTER_SIZE * 2, 16, QChar('0'))).arg(__FILE__).arg(__LINE__).arg(sText)); }
#define LOG(sText)                  { CLog::writeStringInFile("log/log.txt", QString("\t%0:%1(%2)\t%3").arg(QString("0x%1").arg(reinterpret_cast<quintptr>(this), QT_POINTER_SIZE * 2, 16, QChar('0'))).arg(__FILE__).arg(__LINE__).arg(sText)); }

CQmlAdapter::CQmlAdapter(QObject *parent) :
    QObject(parent)
{
    _qmlApplicationEngine = new QQmlApplicationEngine();

    _qmlContext = _qmlApplicationEngine->rootContext();
    if (!_qmlContext)
    {
        EXCEPTION
    }
    _qmlContext->setContextProperty("_cQmlAdapter", this);

    if (!connect(_qmlApplicationEngine, &QQmlApplicationEngine::objectCreated, this, &CQmlAdapter::onQmlApplicationEngineObjectCreated))
    {
        EXCEPTION
    }

    if (!connect(&_cHandling, &CHandling::sigPlayerNewCard, this, &CQmlAdapter::onHandlingPlayerNewCard))
    {
        EXCEPTION
    }

    if (!connect(&_cHandling, &CHandling::sigSetPlayerCard2Ground, this, &CQmlAdapter::onHandlingSetPlayerCard2Ground))
    {
        EXCEPTION
    }

    if (!connect(&_cHandling, &CHandling::sigColorizeGroundCard, this, &CQmlAdapter::onHandlingColorizeGroundCard))
    {
        EXCEPTION
    }

    if (!connect(&_cHandling, &CHandling::sigStart, this, &CQmlAdapter::onHandlingStart))
    {
        EXCEPTION
    }

    if (!connect(&_cHandling, &CHandling::sigActivePlayer, this, &CQmlAdapter::onHandlingActivePlayer))
    {
        EXCEPTION
    }

    _qmlApplicationEngine->load(QUrl(QLatin1String("qrc:/main.qml")));

    _cHandling.start();
}

void CQmlAdapter::onQmlApplicationEngineObjectCreated(QObject *object, const QUrl& /*url*/)
{
    //!LL if OpenGL is needed
}

void CQmlAdapter::onPageGroundSelectPlayerCard(const int iPlayer, const int iCard)
{
    _cHandling.selectPlayerCard(iPlayer, iCard);
}

void CQmlAdapter::onPageGroundSelectGroundCard(const int iX, const int iY)
{
    _cHandling.selectGroundCard(iX, iY);
}

void CQmlAdapter::onPageSettingsStart(const int iX, const int iY)
{
    _cHandling.start(iX, iY);
}

void CQmlAdapter::onHandlingPlayerNewCard(const int iPlayer, const int iCard, const int iValue0, const int iValue1, const int iValue2, const int iValue3)
{
    qDebug() << "onHandlingPlayerNewCard:" << iPlayer << iCard << iValue0 << iValue1 << iValue2 << iValue3;
    emit sigQmlAdapterHandlingNewCard(iPlayer, iCard, iValue0, iValue1, iValue2, iValue3);
}

void CQmlAdapter::onHandlingSetPlayerCard2Ground(const int iPlayer, const int iCard, const int iX, const int iY)
{
    emit qmlAdapterHandlingSetPlayerCard2Ground(iPlayer, iCard, iX, iY);
}

void CQmlAdapter::onHandlingColorizeGroundCard(const int iPlayer, const int iGroundCardIndex)
{
    emit qmlAdapterHandlingColorizeGroundCard(iPlayer, iGroundCardIndex);
}

void CQmlAdapter::onHandlingStart(const int iGroundX, const int iGroundY)
{
    emit sigQmlHandlingStart(iGroundX, iGroundY);
}

void CQmlAdapter::onHandlingActivePlayer(const int iActivePlayer)
{
    emit sigQmlHandlingActivePlayer(iActivePlayer);
}
