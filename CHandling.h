#ifndef CHANDLING_H
#define CHANDLING_H

#include <QObject>
#include <QPoint>

struct StCard
{
    int iValue0 = -1;
    int iValue1 = -1;
    int iValue2 = -1;
    int iValue3 = -1;

    void reset()
    {
        iValue0 = -1;
        iValue1 = -1;
        iValue2 = -1;
        iValue3 = -1;
    }
};

class CHandling : public QObject
{
    Q_OBJECT

public:
    explicit CHandling(QObject *parent = nullptr);
    void selectPlayerCard(const int iPlayer, const int iCard);
    void selectGroundCard(const int iX, const int iY);
    void start(const int iGroundX = 5, const int iGroundY = 5);

signals:
    void sigStart(const int iGroundX, const int iGroundY);
    void sigPlayerNewCard(const int iPlayer, int iCard, const int iValue0, const int iValue1, const int iValue2, const int iValue3);
    void sigSetPlayerCard2Ground(const int iPlayer, int iCard, const int iX, const int iY);
    void sigColorizeGroundCard(const int iPlayer, const int iGroundIndex);
    void sigActivePlayer(const int iActivePlayer);

public slots:

private:
    bool generateCard(const int iPlayer, const int iCard);
    bool playerCardToGround();
    StCard determineCardCompareIndices();

    int _iActivePlayer = -1;
    int _iActivePlayerCard = -1;
    QPoint _pointGroundCard = QPoint(-1, -1);
    QList<StCard> _lstCardGround;
    QPoint _pointGroundResolution = QPoint(-1, -1);
    QList<StCard> _lstCardPlayer1;
    QList<StCard> _lstCardPlayer2;
    QString _sCardPath = "./content/images/card/empty.png";
    QString _sCardFrame = "./content/images/card/frame.png";
};

#endif // CHANDLING_H
