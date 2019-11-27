import QtQuick 2.0
import QtQuick.Controls 2.12

Item {
    Rectangle {
        anchors.centerIn: parent
        width: 400
        height: 400
        color: "darkgray"
        border {
            width: 2
            color: "white"
        }

        Column {
            anchors.centerIn: parent

            SpinBox {
                width: 100
                height: 30
                id: spinWidth
                from: 3
                to: 20
                value: 10
            }

            SpinBox {
                width: 100
                height: 30
                id: spinHeight
                from: 3
                to: 20
                value: 6
            }

            Button {
                height: 50
                width: 100
                text: "start"

                onClicked: _cQmlAdapter.onPageSettingsStart(spinWidth.value, spinHeight.value)
            }
        }
    }
}
