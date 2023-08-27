import QtQuick 2.15
import QtQuick.Controls 2.15

import "../SharedComponents" as ShredCompFolder

Rectangle {
    id: mainRect

    signal signInRequest();
    signal signUpRequest();

    Image {
        id: loginPageBackground
        source: "qrc:/images/darkSpace.jpg"
        anchors.fill: parent
        fillMode: loginPageBackground.fillMode
    }

    ShredCompFolder.InputField {
        id: email
        anchors.top: mainRect.top
        anchors.topMargin: 20
        anchors.horizontalCenter: mainRect.horizontalCenter
        customPlaceholderText: "Enter login"
    }

    ShredCompFolder.InputField {
        id: password
        anchors.top: email.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: mainRect.horizontalCenter
        echoMode: TextInput.Password
        customPlaceholderText: "Enter password"
    }

    ShredCompFolder.InputField {
        id: userName
        anchors.top: password.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: mainRect.horizontalCenter
        customPlaceholderText: "Enter username"
    }

    Button {
        id: signInButtom
        width: parent.width / 3
        height: 50
        text: qsTr("Sign In")
        anchors.rightMargin: 20
        anchors.bottomMargin: 20
        anchors.bottom: parent.bottom
        anchors.right: mainRect.horizontalCenter
        onClicked: signInRequest()
    }

    Button {
        id: signUpButtom
        width: parent.width / 3
        height: 50
        text: qsTr("Sign Up")
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.bottom: parent.bottom
        anchors.left: mainRect.horizontalCenter
        onClicked: signUpRequest()
    }

    Connections {
        target: mainRect

        function onSignInRequest() {
            clientClass.setUsername(userName.text)
            clientClass.fillSignInData(email.text, password.text)
        }
    }
}
