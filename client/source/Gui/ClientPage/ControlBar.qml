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

    Button {
        id: settingsButton
        width: 60
        height: 40
        text: qsTr("Settings")
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: parent.right
        anchors.rightMargin: 30
    }

    Button {
        id: newChatButton
        width: 60
        height: 40
        text: qsTr("new chat")
        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.leftMargin: 30
        onClicked: newChatButtonClicked()
    }
}