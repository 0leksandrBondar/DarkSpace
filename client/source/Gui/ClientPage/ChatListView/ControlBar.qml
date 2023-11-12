import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root
    z: 1
    height: 50
    color: "#242625"
    border.color: "#078491"
    border.width: 1

    signal newChatButtonClicked()

    Text
    {
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 5
        text: clientClass.userName()
        font.pointSize: 15
        color: "white"
    }

    Button {
        id: settingsButton
        width: 60
        height: 40
        text: qsTr("Settings")
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 5
    }

    Button {
        id: newChatButton
        width: 60
        height: 40
        text: qsTr("new chat")
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: settingsButton.left
        anchors.rightMargin: 5
        onClicked: newChatButtonClicked()
    }
}