
import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15

Item {
    id: mainPage

    Rectangle {
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter

        width: 250
        height: 150

        Text {
            anchors.centerIn: parent
            text: qsTr("Hello")
        }
    }
}
