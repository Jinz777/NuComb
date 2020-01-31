import QtQuick 2.0
import QtQuick.Layouts 1.13

Item {
    property string _sCardGround: "qrc:/content/images/card/ground.jpg"
    property string _sCardEmpty: "qrc:/content/images/card/empty.png"
    property string _sCardFrame: "qrc:/content/images/card/frame.png"

    Connections {
        target: _cQmlAdapter

        onSigQmlAdapterHandlingNewCard: {
            console.log("onQmlAdapterHandlingNewCard: " + iPlayer + ", " + iCard + ", " + iValue0 + ", " + iValue1 + ", " + iValue2 + ", " + iValue3)

            if (iPlayer === 1 && iCard === 0)
            {
                player1_0._iValue0 = iValue0
                player1_0._iValue1 = iValue1
                player1_0._iValue2 = iValue2
                player1_0._iValue3 = iValue3
            }
            else if (iPlayer === 1 && iCard === 1)
            {
                player1_1._iValue0 = iValue0
                player1_1._iValue1 = iValue1
                player1_1._iValue2 = iValue2
                player1_1._iValue3 = iValue3
            }
            else if (iPlayer === 1 && iCard === 2)
            {
                player1_2._iValue0 = iValue0
                player1_2._iValue1 = iValue1
                player1_2._iValue2 = iValue2
                player1_2._iValue3 = iValue3
            }
            else if (iPlayer === 1 && iCard === 3)
            {
                player1_3._iValue0 = iValue0
                player1_3._iValue1 = iValue1
                player1_3._iValue2 = iValue2
                player1_3._iValue3 = iValue3
            }
            else if (iPlayer === 2 && iCard === 0)
            {
                player2_0._iValue0 = iValue0
                player2_0._iValue1 = iValue1
                player2_0._iValue2 = iValue2
                player2_0._iValue3 = iValue3
            }
            else if (iPlayer === 2 && iCard === 1)
            {
                player2_1._iValue0 = iValue0
                player2_1._iValue1 = iValue1
                player2_1._iValue2 = iValue2
                player2_1._iValue3 = iValue3
            }
            else if (iPlayer === 2 && iCard === 2)
            {
                player2_2._iValue0 = iValue0
                player2_2._iValue1 = iValue1
                player2_2._iValue2 = iValue2
                player2_2._iValue3 = iValue3
            }
            else if (iPlayer === 2 && iCard === 3)
            {
                player2_3._iValue0 = iValue0
                player2_3._iValue1 = iValue1
                player2_3._iValue2 = iValue2
                player2_3._iValue3 = iValue3
            }
        }

        onQmlAdapterHandlingSetPlayerCard2Ground: {
            // iPlayer, iCard, iX, iY
            var gridChildren = grid.children
            var iIndex = iX * grid.columns + iY
            var item = gridChildren[iIndex]

            console.log("onQmlAdapterHandlingSetPlayerCard2Ground: " + iPlayer + ", " + iCard + ", " + iX + ", " + iY + ", " + iIndex);

            item._iPlayer = iPlayer
            item._source = "qrc:/content/images/card/empty.png"

            if (iPlayer === 1)
            {
                if (iCard === 0)
                {
                    item._iValue0 = player1_0._iValue0
                    item._iValue1 = player1_0._iValue1
                    item._iValue2 = player1_0._iValue2
                    item._iValue3 = player1_0._iValue3
                }
                else if (iCard === 1)
                {
                    item._iValue0 = player1_1._iValue0
                    item._iValue1 = player1_1._iValue1
                    item._iValue2 = player1_1._iValue2
                    item._iValue3 = player1_1._iValue3
                }
                else if (iCard === 2)
                {
                    item._iValue0 = player1_2._iValue0
                    item._iValue1 = player1_2._iValue1
                    item._iValue2 = player1_2._iValue2
                    item._iValue3 = player1_2._iValue3
                }
                else if (iCard === 3)
                {
                    item._iValue0 = player1_3._iValue0
                    item._iValue1 = player1_3._iValue1
                    item._iValue2 = player1_3._iValue2
                    item._iValue3 = player1_3._iValue3
                }
                else
                    console.error("EXCEPTION")
            }
            else if (iPlayer === 2)
            {
                if (iCard === 0)
                {
                    item._iValue0 = player2_0._iValue0
                    item._iValue1 = player2_0._iValue1
                    item._iValue2 = player2_0._iValue2
                    item._iValue3 = player2_0._iValue3
                }
                else if (iCard === 1)
                {
                    item._iValue0 = player2_1._iValue0
                    item._iValue1 = player2_1._iValue1
                    item._iValue2 = player2_1._iValue2
                    item._iValue3 = player2_1._iValue3
                }
                else if (iCard === 2)
                {
                    item._iValue0 = player2_2._iValue0
                    item._iValue1 = player2_2._iValue1
                    item._iValue2 = player2_2._iValue2
                    item._iValue3 = player2_2._iValue3
                }
                else if (iCard === 3)
                {
                    item._iValue0 = player2_3._iValue0
                    item._iValue1 = player2_3._iValue1
                    item._iValue2 = player2_3._iValue2
                    item._iValue3 = player2_3._iValue3
                }
                else
                    console.error("EXCEPTION")
            }
            else
                console.error("EXCEPTION")
        }

        onQmlAdapterHandlingColorizeGroundCard: {
            var gridChildren = grid.children
            var item = gridChildren[iGroundCardIndex]
            item._iPlayer = iPlayer
        }

        onSigQmlHandlingStart: {
            /*var gridChildren = grid.children
            for (var i = 0; i < grid.rows * grid.columns; i++)
            {
                var item = gridChildren[i]
                item._iPlayer = 0
            }*/
            console.log("onSigQmlHandlingStart: " + iGroundX + ", " + iGroundY)
            clearItems();

            grid.columns = iGroundX
            grid.rows = iGroundY

            createItems();
        }

        onSigQmlHandlingActivePlayer: {
            console.log("onSigQmlHandlingActivePlayer: " + iActivePlayer)
            setActivePlayer(iActivePlayer);
        }
    }

    function onItemEntered(iX, iY)
    {
        console.log("entered: " + iX + ", " + iY)
        //!LL colorize style from active player
    }

    function onItemPressed(iX, iY)
    {
        _cQmlAdapter.onPageGroundSelectGroundCard(iX, iY)
    }

    function createItems()
    {
        var color = "transparent"

        for (x = 0; x < grid.rows; x++)
        {
            for (y = 0; y < grid.columns; y++)
            {
                var item = Qt.createComponent("ItemFigure.qml");
                var object = item.createObject(grid)

                object.Layout.fillWidth = true
                object.Layout.fillHeight = true
                object._source = _sCardEmpty
                object._sourceFrame = _sCardFrame
                object._id = "ground_" + x + "_" + y
                object._iX = x
                object._iY = y
                object._iPlayer = 0
                object.sigEntered.connect(onItemEntered)
                object.sigPressed.connect(onItemPressed)

                console.log("createItem: " + x + " " + y)
            }
        }
    }

    function clearItems()
    {
        var gridChildren = grid.children
        for (var i = 0; i<gridChildren.length; i++)
        {
            var item = gridChildren[i]
            item.destroy()
            console.log("destroy item: " + i)
        }
    }

    function setActivePlayer(iActivePlayer)
    {
        var gridChildren = grid.children
        for (var i = 0; i<gridChildren.length; i++)
        {
            var item = gridChildren[i]
            item._iActivePlayer = iActivePlayer
            console.log("set active Player: " + i + " " + iActivePlayer)
        }
    }

    Image {
        anchors.fill: parent
        source: _sCardGround
        fillMode: Image.Stretch

        RowLayout {
            anchors.fill: parent

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.minimumWidth: 10

                ItemFigure {
                    id: player1_0
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    //_source: "file:content/images/card/p1_0.png"
                    _source: _sCardEmpty
                    _sourceFrame: _sCardFrame
                    _iPlayer: 1

                    onSigPressed: _cQmlAdapter.onPageGroundSelectPlayerCard(1, 0)
                }

                ItemFigure {
                    id: player1_1
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    _source: _sCardEmpty
                    _sourceFrame: _sCardFrame
                    _iPlayer: 1

                    onSigPressed: _cQmlAdapter.onPageGroundSelectPlayerCard(1, 1)
                }

                ItemFigure {
                    id: player1_2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    _source: _sCardEmpty
                    _sourceFrame: _sCardFrame
                    _iPlayer: 1

                    onSigPressed: _cQmlAdapter.onPageGroundSelectPlayerCard(1, 2)
                }

                ItemFigure {
                    id: player1_3
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    _source: _sCardEmpty
                    _sourceFrame: _sCardFrame
                    _iPlayer: 1

                    onSigPressed: _cQmlAdapter.onPageGroundSelectPlayerCard(1, 3)
                }
            }

            GridLayout {
                id: grid
                Layout.fillWidth: true
                Layout.fillHeight: true

                //columns: 10
                //rows: 6
            }

            ColumnLayout {
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.minimumWidth: 10

                ItemFigure {
                    id: player2_0
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    _source: _sCardEmpty
                    _sourceFrame: _sCardFrame
                    _iPlayer: 2

                    onSigPressed: _cQmlAdapter.onPageGroundSelectPlayerCard(2, 0)
                }

                ItemFigure {
                    id: player2_1
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    _source: _sCardEmpty
                    _sourceFrame: _sCardFrame
                    _iPlayer: 2

                    onSigPressed: _cQmlAdapter.onPageGroundSelectPlayerCard(2, 1)
                }

                ItemFigure {
                    id: player2_2
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    _source: _sCardEmpty
                    _sourceFrame: _sCardFrame
                    _iPlayer: 2

                    onSigPressed: _cQmlAdapter.onPageGroundSelectPlayerCard(2, 2)
                }

                ItemFigure {
                    id: player2_3
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    _source: _sCardEmpty
                    _sourceFrame: _sCardFrame
                    _iPlayer: 2

                    onSigPressed: _cQmlAdapter.onPageGroundSelectPlayerCard(2, 3)
                }
            }
        }
    }

    Component.onCompleted: {
        //createItems();
    }
}

