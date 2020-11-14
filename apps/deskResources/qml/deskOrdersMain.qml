
import QtQuick 2.15
import QtQuick.Controls 2.15

import "qmlPages"

ApplicationWindow {
    id: mainWindow
    title: qsTr("Delivery Desk")

    visible: true
    visibility: "Maximized"
    width: 1500
    height: 800

    StackView {
        id: stackView
        anchors.fill: parent
        initialItem: LoginPage {}
    }

    Connections {
        target: LoginWrapper
        function onAuthChanged(isLogged) {
            if (isLogged) {
                stackView.push("qrc:///qmlPages/MainPage.qml")
            } else {
                stackView.pop()
            }
        }
    }
}
