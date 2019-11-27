#ifndef CQMLADAPTER_H
#define CQMLADAPTER_H

#include <QObject>
#include <QQmlApplicationEngine>
#include "CHandling.h"

class CQmlAdapter : public QObject
{
    Q_OBJECT

public:
    explicit CQmlAdapter(QQmlApplicationEngine* qmlApplicationEngine, QObject *parent = nullptr);
    explicit CQmlAdapter(QObject *parent = nullptr);

public slots:
    void onQmlApplicationEngineObjectCreated(QObject *object, const QUrl &url);
    void onPageGroundSelectPlayerCard(const int iPlayer, const int iCard);
    void onPageGroundSelectGroundCard(const int iX, const int iY);
    void onPageSettingsStart(const int iX, const int iY);
    void onHandlingPlayerNewCard(const int iPlayer, const int iCard, const int iValue0, const int iValue1, const int iValue2, const int iValue3);
    void onHandlingSetPlayerCard2Ground(const int iPlayer, const int iCard, const int iX, const int iY);
    void onHandlingColorizeGroundCard(const int iPlayer, const int iGroundCardIndex);
    void onHandlingStart(const int iGroundX, const int iGroundY);
    void onHandlingActivePlayer(const int iActivePlayer);

signals:
    void sigQmlAdapterHandlingNewCard(const int iPlayer, const int iCard, const int iValue0, const int iValue1, const int iValue2, const int iValue3);
    void qmlAdapterHandlingSetPlayerCard2Ground(const int iPlayer, const int iCard, const int iX, const int iY);
    void qmlAdapterHandlingColorizeGroundCard(const int iPlayer, const int iGroundCardIndex);
    void sigQmlHandlingStart(const int iGroundX, const int iGroundY);
    void sigQmlHandlingActivePlayer(const int iActivePlayer);

private:
    QQmlApplicationEngine* _qmlApplicationEngine = nullptr;
    QQmlContext* _qmlContext = nullptr;
    CHandling _cHandling;
};

#endif // CQMLADAPTER_H
