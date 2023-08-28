import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: mainRect
    width: parent.width
    height: parent.height
    color: "#242625"

    Rectangle {
        id: controlBar
        width: mainRect.width
        height: 50
        color: "red"
        anchors.top: mainRect.top
    }

    Rectangle {
        id: list
        width: mainRect.width
        height: mainRect.height - controlBar.height
        anchors.top: controlBar.bottom
        color: "blue"
        ScrollView {
            anchors.fill: list
            ListView {
                width: list.width
                model: 30
                delegate: ChatBlock {
                    id: chatBlock
                    width: list.width
                    height: list.width / 4
                    Text {
                        anchors.centerIn: parent
                        width: chatBlock.width / 2
                        height: chatBlock.height / 2
                        text: "Some chat " + (index + 1)
                        color: "#1cfc6a"
                    }
                }
            }
            ScrollBar.vertical.background: Rectangle {
                color: "#242625"
            }
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
        }
    }
}
