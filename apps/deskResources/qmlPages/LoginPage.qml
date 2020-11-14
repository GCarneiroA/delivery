
import QtQuick 2.15
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.15

Item {
    id: loginPage

    Image {
        id: loginBackground
        anchors.fill: parent
        source: "qrc:///images/images/loginBackground.jpg"
        fillMode: Image.Stretch
    }

    Rectangle {
        id: loginArea
        x: 192
        y: 437
        width: 350
        height: 140
        color: "#4d000000"
        radius: 20
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        
        Text {
            id: text1
            x: 75
            color: "#ffffff"
            text: qsTr("Username:")
            anchors.top: parent.top
            font.pixelSize: 12
            anchors.topMargin: 27
            transformOrigin: Item.Center
        }

        TextField {
            id: txtUsername
            x: 143
            width: 132
            height: 25
            color: "#000000"
            placeholderText: qsTr("Username:")
            anchors.top: parent.top
            font.pixelSize: 12
            anchors.topMargin: 25
            transformOrigin: Item.Center
        }

        Text {
            id: text2
            x: 75
            color: "#ffffff"
            text: qsTr("Password:")
            anchors.top: parent.top
            font.pixelSize: 12
            anchors.topMargin: 57
        }

        TextField {
            id: txtPassword
            x: 143
            width: 132
            height: 25
            placeholderText: qsTr("Password:")
            anchors.top: parent.top
            anchors.topMargin: 55
            font.pixelSize: 12
            echoMode: TextInput.Password
        }

        Button {
            y: 85
            width: 200
            height: 30
            text: qsTr("Login")
            highlighted: true
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: {
                LoginWrapper.login(txtUsername.text, txtPassword.text)
            }
        }
    }
}
