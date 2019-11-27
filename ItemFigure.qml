import QtQuick 2.0
import QtGraphicalEffects 1.12

Item {
    id: _id

    property string _source
    property string _sourceFrame
    property string _id
    property string _iX
    property string _iY
    property int _iPlayer: -1
    property int _iActivePlayer: -1
    property int _iValue0
    property int _iValue1
    property int _iValue2
    property int _iValue3

    property color colorNoPlayer: "#77111111"
    property color colorPlayer1: "#44ff0000"
    property color colorPlayer2: "#4400ff00"

    signal sigPressed(int iX, int iY)
    signal sigEntered(int iX, int iY)

    function reloadImage()
    {
        var oldSource = image.source
        image.source = ""
        image.source = oldSource
    }

    function getActivePlayerColor()
    {
        if (_iActivePlayer === 1)
            return colorPlayer1
        else if (_iActivePlayer === 2)
            return colorPlayer2
        else
            return colorNoPlayer
    }

    on_SourceChanged: {
        image.source = _source
    }

    on_IPlayerChanged: {
        if (_iPlayer === 1)
        {
            //effectRectGlow.color = "#77ff0000"
            colorOverlay.color = colorPlayer1
            colorOverlayImage0.color = colorPlayer1
            colorOverlayImage1.color = colorPlayer1
            colorOverlayImage2.color = colorPlayer1
            colorOverlayImage3.color = colorPlayer1
            image0.visible = true
            image1.visible = true
            image2.visible = true
            image3.visible = true
        }
        else if (_iPlayer === 2)
        {
            //effectRectGlow.color = "#7700ff00"
            colorOverlay.color = colorPlayer2
            colorOverlayImage0.color = colorPlayer2
            colorOverlayImage1.color = colorPlayer2
            colorOverlayImage2.color = colorPlayer2
            colorOverlayImage3.color = colorPlayer2
            image0.visible = true
            image1.visible = true
            image2.visible = true
            image3.visible = true
        }
        else
        {
            colorOverlay.color = colorNoPlayer
            colorOverlayImage0.color = colorNoPlayer
            colorOverlayImage1.color = colorNoPlayer
            colorOverlayImage2.color = colorNoPlayer
            colorOverlayImage3.color = colorNoPlayer
            image0.visible = false
            image1.visible = false
            image2.visible = false
            image3.visible = false
        }
    }

    Rectangle {
        id: rect
        anchors.fill: parent
        color: "transparent"
        radius: 3
        state: "RELEASED"

        RectangularGlow {
            id: rectGlowPressed
            width: rect.width
            height: rect.height
            glowRadius: 20
            spread: 0
            cornerRadius: 20
            visible: false
        }

        Image {
            id: image
            anchors.fill: parent
            source: _source
            fillMode: Image.PreserveAspectFit
            cache: false
        }

        ColorOverlay {
            id: colorOverlay
            anchors.fill: parent
            source: image
            color: "#77111111"
        }

        Image {
            id: image0
            width: image.width/3; height: image.height/3
            anchors.left: image.left
            anchors.top: image.top
            anchors.leftMargin: image.width/2 - width/2
            anchors.topMargin: image.height/15
            source: _sourceFrame
            fillMode: Image.PreserveAspectFit
            cache: false

            ColorOverlay {
                id: colorOverlayImage0
                anchors.fill: parent
                source: image0
                color: "#77111111"
            }

            Text {
                anchors.centerIn: parent
                font {
                    pointSize: image0.width/4
                    bold: true
                }
                text: qsTr(Number(_iValue0).toLocaleString(Qt.locale("de_DE"), 'f', 0))
            }
        }

        Image {
            id: image1
            width: image.width/3; height: image.height/3
            anchors.right: image.right
            anchors.top: image.top
            anchors.rightMargin: image.width/15
            anchors.topMargin: image.height/2 - height/2
            source: _sourceFrame
            fillMode: Image.PreserveAspectFit
            cache: false

            ColorOverlay {
                id: colorOverlayImage1
                anchors.fill: parent
                source: image1
                color: "#77111111"
            }

            Text {
                anchors.centerIn: parent
                font {
                    pointSize: image1.width/4
                    bold: true
                }
                text: qsTr(Number(_iValue1).toLocaleString(Qt.locale("de_DE"), 'f', 0))
            }
        }

        Image {
            id: image2
            width: image.width/3; height: image.height/3
            anchors.left: image.left
            anchors.bottom: image.bottom
            anchors.leftMargin: image.width/2 - width/2
            anchors.bottomMargin: image.height/15
            source: _sourceFrame
            fillMode: Image.PreserveAspectFit
            cache: false

            ColorOverlay {
                id: colorOverlayImage2
                anchors.fill: parent
                source: image2
                color: "#77111111"
            }

            Text {
                anchors.centerIn: parent
                font {
                    pointSize: image0.width/4
                    bold: true
                }
                text: qsTr(Number(_iValue2).toLocaleString(Qt.locale("de_DE"), 'f', 0))
            }
        }

        Image {
            id: image3
            width: image.width/3; height: image.height/3
            anchors.left: image.left
            anchors.top: image.top
            anchors.leftMargin: image.width/15
            anchors.topMargin: image.height/2 - height/2
            source: _sourceFrame
            fillMode: Image.PreserveAspectFit
            cache: false

            ColorOverlay {
                id: colorOverlayImage3
                anchors.fill: parent
                source: image3
                color: "#77111111"
            }

            Text {
                anchors.centerIn: parent
                font {
                    pointSize: image0.width/4
                    bold: true
                }
                text: qsTr(Number(_iValue3).toLocaleString(Qt.locale("de_DE"), 'f', 0))
            }
        }

        MouseArea{
            anchors.fill: parent
            drag.target: _id
            hoverEnabled: true
            onPressed:{
                image.source = _source
                sigPressed(_iX, _iY)
                rect.state = "PRESSED"
            }
            onEntered: {
                rect.state = "ENTERED"
                sigEntered(_iX, _iY)
            }
            onExited: rect.state = "EXITED"
            onReleased: rect.state = "RELEASED"
        }

        states: [
            State {
                name: "PRESSED"
                PropertyChanges { target: rectGlowPressed; color: getActivePlayerColor() }
                PropertyChanges { target: rectGlowPressed; visible: true}
            },
            State {
                name: "ENTERED"
                PropertyChanges { target: rectGlowPressed; color: getActivePlayerColor() }
                PropertyChanges { target: rectGlowPressed; visible: true}
            },
            State {
                name: "RELEASED"
                //PropertyChanges { target: rect; color: "lightblue"}
                PropertyChanges { target: rectGlowPressed; visible: false}
            },
            State {
                name: "EXITED"
                PropertyChanges { target: rectGlowPressed; color: getActivePlayerColor() }
                PropertyChanges { target: rectGlowPressed; visible: false}
            }
        ]

        transitions: [
            Transition {
                from: "PRESSED"
                to: "RELEASED"
                ColorAnimation { target: rect; duration: 100}
            },
            Transition {
                from: "RELEASED"
                to: "PRESSED"
                ColorAnimation { target: rect; duration: 100}
            },
            Transition {
                from: "ENTERED"
                to: "EXITED"
                ColorAnimation { target: rect; duration: 100}
            },
            Transition {
                from: "EXITED"
                to: "ENTERED"
                ColorAnimation { target: rect; duration: 100}
            }
        ]
    }
}
