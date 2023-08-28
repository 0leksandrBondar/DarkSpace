import QtQuick
import QtQuick.Controls 2.15

//TODO: Move this component to separate directory

Rectangle {
    id: mainRect
    anchors.fill: parent
    color: "#242625"

    signal okClicked()

    Text {
        font.pixelSize: 20
        text: "something vent wrong. Please try again!"
        color: "white"
        anchors.centerIn: parent
    }

    Button {
        id: signUpButtom
        width: parent.width / 3
        height: 50
        text: qsTr("ok")
        anchors.leftMargin: 20
        anchors.bottomMargin: 20
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: mainRect.horizontalCenter
        onClicked: okClicked()
    }
}