#include <QRandomGenerator>
#include <QDebug>
#include <QPixmap>
#include <QPainter>
#include <QFont>
#include <QFile>
#include "CHandling.h"
#include "../include/Log/CLog.h"

#define EXCEPTION                   { CLog::writeStringInFile("log/exception.txt", QString("\t%0:%1(%2)").arg(QString("0x%1").arg(reinterpret_cast<quintptr>(this), QT_POINTER_SIZE * 2, 16, QChar('0'))).arg(__FILE__).arg(__LINE__)); }
#define EXCEPTION_LOG(sText)        { CLog::writeStringInFile("log/exception.txt", QString("\t%0:%1(%2): %3").arg(QString("0x%1").arg(reinterpret_cast<quintptr>(this), QT_POINTER_SIZE * 2, 16, QChar('0'))).arg(__FILE__).arg(__LINE__).arg(sText)); }
#define LOG(sText)                  { CLog::writeStringInFile("log/log.txt", QString("\t%0:%1(%2)\t%3").arg(QString("0x%1").arg(reinterpret_cast<quintptr>(this), QT_POINTER_SIZE * 2, 16, QChar('0'))).arg(__FILE__).arg(__LINE__).arg(sText)); }

CHandling::CHandling(QObject *parent) : QObject(parent)
{
    //start(10, 6);
}

void CHandling::selectPlayerCard(const int iPlayer, const int iCard)
{
    _iActivePlayerCard = -1;

    if (iPlayer != _iActivePlayer)
    {
        EXCEPTION
                return;
    }

    _iActivePlayerCard = iCard;

    if (!playerCardToGround())
        EXCEPTION
}

void CHandling::selectGroundCard(const int iX, const int iY)
{
    _pointGroundCard.setX(iX);
    _pointGroundCard.setY(iY);

    if (!playerCardToGround())
        EXCEPTION
}

void CHandling::start(const int iGroundX, const int iGroundY)
{
    emit sigStart(iGroundX, iGroundY);

    _lstCardGround.clear();
    _lstCardPlayer1.clear();
    _lstCardPlayer2.clear();

    for (int x=0; x<iGroundX; x++)
        for (int y=0; y<iGroundY; y++)
            _lstCardGround.append(StCard());

    for (int i=0; i<4; ++i)
    {
        _lstCardPlayer1.append(StCard());
        _lstCardPlayer2.append(StCard());
    }

    _pointGroundResolution.setX(iGroundX);
    _pointGroundResolution.setY(iGroundY);

    //!LL refresh intern ground list for handling the new one
    QRandomGenerator *gen =  QRandomGenerator::system();

    _iActivePlayer = gen->bounded(1, 3);
    qDebug() << "_iActivePlayer:" << _iActivePlayer;
    emit sigActivePlayer(_iActivePlayer);

    for (int iPlayer = 1; iPlayer<3; ++iPlayer)
        for (int iCard=0; iCard<4; ++iCard)
            if (!generateCard(iPlayer, iCard))
                EXCEPTION
}

bool CHandling::generateCard(const int iPlayer, const int iCard)
{
    QRandomGenerator *gen =  QRandomGenerator::system();
    QList<int> lstReturn;
    QList<int> lstReturn2;
    QList<int> lstReturn3;

    StCard stCardNew;
    for (int i=0; i<4; ++i)
    {
        lstReturn.append(gen->bounded(3, 40));
        lstReturn2.append(gen->bounded(3, 40));
        lstReturn3.append(gen->bounded(3, 40));

        if (i==0)
            stCardNew.iValue0 = lstReturn.at(i) + lstReturn2.at(i) + lstReturn3.at(i);
        else if (i==1)
            stCardNew.iValue1 = lstReturn.at(i) + lstReturn2.at(i) + lstReturn3.at(i);
        else if (i==2)
            stCardNew.iValue2 = lstReturn.at(i) + lstReturn2.at(i) + lstReturn3.at(i);
        else if (i==3)
            stCardNew.iValue3 = lstReturn.at(i) + lstReturn2.at(i) + lstReturn3.at(i);
    }

    if (iPlayer == 1)
        _lstCardPlayer1[iCard] = stCardNew;
    else if (iPlayer == 2)
        _lstCardPlayer2[iCard] = stCardNew;
    else
        EXCEPTION;

    qDebug() << iPlayer << iCard << stCardNew.iValue0 << stCardNew.iValue1 << stCardNew.iValue2 << stCardNew.iValue3;

    /*QFile file(_sCardPath);
    if (!file.exists())
    {
        EXCEPTION;
        return false;
    }

    QPixmap pixmap(_sCardPath);
    if (pixmap.isNull())
    {
        EXCEPTION;
        return false;
    }

    QPainter p(&pixmap);
    file.setFileName(_sCardPath);
    if (!file.exists())
    {
        EXCEPTION;
        return false;
    }
    QPixmap pixmapFrame(_sCardFrame);
    const int iBorder = pixmap.width()/15;
    int iFrameSize = pixmap.width()/3;

    p.drawPixmap(pixmap.width()/2 - iFrameSize/2, iBorder, iFrameSize, iFrameSize, pixmapFrame);
    p.drawPixmap(pixmap.width() - iFrameSize - iBorder, pixmap.height()/2 - iFrameSize/2, iFrameSize, iFrameSize, pixmapFrame);
    p.drawPixmap(pixmap.width()/2 - iFrameSize/2, pixmap.height() - iFrameSize - iBorder, iFrameSize, iFrameSize, pixmapFrame);
    p.drawPixmap(iBorder, pixmap.height()/2 - iFrameSize/2, iFrameSize, iFrameSize, pixmapFrame);
    int iFactorFont = pixmap.width()/7;
    p.setFont(QFont("Meera", pixmap.width()/7, QFont::Bold));
    p.setPen (Qt::black);
    p.drawText(pixmap.width()/2 - iFrameSize/2 + iFactorFont/2, iBorder + iFactorFont*1.5f, QString("%1").arg(lstReturn.at(0)));
    p.drawText(pixmap.width() - iFrameSize, pixmap.height()/2 +  iFactorFont/2, QString("%1").arg(lstReturn.at(1)));
    p.drawText(pixmap.width()/2 - iFrameSize/2 +iFactorFont/2, pixmap.height() - iFrameSize/2, QString("%1").arg(lstReturn.at(2)));
    p.drawText(iFrameSize/2 - iFactorFont/3, pixmap.height()/2 + iFactorFont/2, QString("%1").arg(lstReturn.at(3)));
    p.end();

    pixmap.save(QString("./content/images/card/p%1_%2.png").arg(iPlayer).arg(iCard));*/

    emit sigPlayerNewCard(iPlayer, iCard, stCardNew.iValue0, stCardNew.iValue1, stCardNew.iValue2, stCardNew.iValue3);

    return true;
}

bool CHandling::playerCardToGround()
{
    if (_iActivePlayerCard != -1 && _pointGroundCard != QPoint(-1, -1))
    {
        emit sigSetPlayerCard2Ground(_iActivePlayer, _iActivePlayerCard, _pointGroundCard.x(), _pointGroundCard.y());

        // compare values to colorize ground
        StCard stCardIndex = determineCardCompareIndices();

        // value 0
        StCard stCardCurrent;
        if (_iActivePlayer == 1)
            stCardCurrent = _lstCardPlayer1.at(_iActivePlayerCard);
        else if (_iActivePlayer == 2)
            stCardCurrent = _lstCardPlayer2.at(_iActivePlayerCard);
        else
            EXCEPTION;

        int iGroundIndex = _pointGroundCard.x() * _pointGroundResolution.x() + _pointGroundCard.y();
        _lstCardGround[iGroundIndex] = stCardCurrent;

        // value0 from current card
        if (stCardIndex.iValue0 != -1 && _lstCardGround.at(stCardIndex.iValue0).iValue2 != -1 && _lstCardGround.at(stCardIndex.iValue0).iValue2 <= stCardCurrent.iValue0)
        {
            emit sigColorizeGroundCard(_iActivePlayer, stCardIndex.iValue0);
        }
        // value1 from current card
        if (stCardIndex.iValue1 != -1 && _lstCardGround.at(stCardIndex.iValue1).iValue3 != -1 && _lstCardGround.at(stCardIndex.iValue1).iValue3 <= stCardCurrent.iValue1)
        {
            emit sigColorizeGroundCard(_iActivePlayer, stCardIndex.iValue1);
        }
        // value2 from current card
        if (stCardIndex.iValue2 != -1 && _lstCardGround.at(stCardIndex.iValue2).iValue0 != -1 && _lstCardGround.at(stCardIndex.iValue2).iValue0 <= stCardCurrent.iValue2)
        {
            emit sigColorizeGroundCard(_iActivePlayer, stCardIndex.iValue2);
        }
        // value3 from current card
        if (stCardIndex.iValue3 != -1 && _lstCardGround.at(stCardIndex.iValue3).iValue1 != -1 && _lstCardGround.at(stCardIndex.iValue3).iValue1 <= stCardCurrent.iValue3)
        {
            emit sigColorizeGroundCard(_iActivePlayer, stCardIndex.iValue3);
        }

        // new card because this one is already played
        if (!generateCard(_iActivePlayer, _iActivePlayerCard))
        {
            EXCEPTION return false;
        }

        if (_iActivePlayer == 1)
            _iActivePlayer = 2;
        else
            _iActivePlayer = 1;

        emit sigActivePlayer(_iActivePlayer);

        qDebug() << "_iActivePlayer:" << _iActivePlayer;

        _iActivePlayerCard = -1;
        _pointGroundCard = QPoint(-1, -1);
    }

    return true;
}

StCard CHandling::determineCardCompareIndices()
{
    int iGroundIndex = _pointGroundCard.x() * _pointGroundResolution.x() + _pointGroundCard.y();
    StCard stCardIndex;
    stCardIndex.iValue0 = iGroundIndex - _pointGroundResolution.x();
    stCardIndex.iValue1 = iGroundIndex + 1;
    stCardIndex.iValue2 = iGroundIndex + _pointGroundResolution.x();
    stCardIndex.iValue3 = iGroundIndex - 1;

    if (stCardIndex.iValue0 < 0)
        stCardIndex.iValue0 = -1;

    if (stCardIndex.iValue1 > _lstCardGround.count() - 1)
        stCardIndex.iValue1 = -1;

    if (stCardIndex.iValue2 > _lstCardGround.count() - 1)
        stCardIndex.iValue2 = -1;

    if ((iGroundIndex + 1) % _pointGroundResolution.x() == 0)    // right border
        stCardIndex.iValue1 = -1;

    if ((iGroundIndex) % _pointGroundResolution.x() == 0)   // left border
        stCardIndex.iValue3 = -1;

    return stCardIndex;
}
