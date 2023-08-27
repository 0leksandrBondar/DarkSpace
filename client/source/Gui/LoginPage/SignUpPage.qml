import QtQuick 2.15
import QtQuick.Controls 2.15

import "../SharedComponents" as ShredCompFolder

Rectangle {
    id: mainRect

    signal backClicked()
    signal signUpClicked()

    color: "#242625"
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

    // TODO: implement it latter
    //    ShredCompFolder.InputField
    //    {
    //        id: confirmationPassword
    //        anchors.top: password.bottom
    //        anchors.topMargin: 10
    //        anchors.horizontalCenter:  mainRect.horizontalCenter
    //        echoMode: TextInput.Password
    //        customPlaceholderText: "Confirmation password"
    //    }

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
        text: qsTr("Back")
        anchors.rightMargin: 20
        anchors.bottomMargin: 20
        anchors.bottom: parent.bottom
        anchors.right: mainRect.horizontalCenter
        onClicked: backClicked()
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
        onClicked: signUpClicked()
    }
    Connections {
        target: mainRect

        function onSignUpClicked() {
            clientClass.fillSignUpData(email.text, password.text, userName.text)
        }


    }
}
