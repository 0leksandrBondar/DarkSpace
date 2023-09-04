import QtQuick 2.15
import QtQuick.Controls 2.15

Dialog {
    title: "Create new chat"
    width: 250;
    height: 350;
    background: Rectangle {
        color: "#242625"
    }
    Rectangle {
        id: dialogRect
        anchors.fill: parent
        color: "#242625"
        border.color: "#078491"
        border.width: 1
        Button {
            anchors.bottom: parent.bottom
            text: "create"
        }
        Button {
            anchors.bottom: parent.bottom
            anchors.right: parent.right

            text: "cancel"
        }
    }
}