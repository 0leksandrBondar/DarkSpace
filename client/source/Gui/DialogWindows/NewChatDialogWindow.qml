import QtQuick 2.15
import QtQuick.Controls 2.15

import "../SharedComponents" as ShredCompFolder

Dialog {
    title: "Create new chat"
    width: parent.width;
    height: 250;
    background: Rectangle {
        color: "#242625"
    }

    Rectangle {
        id: dialogRect
        anchors.fill: parent
        color: "#242625"
        border.color: "#078491"
        border.width: 1
        ShredCompFolder.InputField {
            id: searchUser
            width: parent.width * 0.85
            height: 30
            font.pointSize: 15
            customPlaceholderText: "Enter userName"
            anchors.centerIn: parent
        }
        Button {
            width: parent.width / 3
            height: 30
            anchors.rightMargin: 20
            anchors.bottomMargin: 20
            anchors.bottom: parent.bottom
            anchors.right: parent.horizontalCenter
            text: "create"
        }
        Button {
            height: 30
            width: parent.width / 3
            anchors.leftMargin: 20
            anchors.bottomMargin: 20
            anchors.bottom: parent.bottom
            anchors.left: parent.horizontalCenter

            text: "cancel"
        }
    }
}