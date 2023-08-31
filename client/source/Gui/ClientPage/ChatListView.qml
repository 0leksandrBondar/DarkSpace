import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: mainRect

    function addNewChat() {
        console.log("hello");
        var newChatBlock = Qt.createComponent("ChatBlock.qml")//.createObject(chatListView);
        chatListModel.append({});
        listView.positionViewAtEnd();
    }

    color: "#242625"
    height: parent.height
    width: parent.width

    ControlBar {
        id: controlBar

        anchors.top: mainRect.top
        width: mainRect.width
    }
    ListModel {
        id: chatListModel

    }
    Rectangle {
        id: chatListView

        anchors.top: controlBar.bottom
        color: "#242625"
        height: mainRect.height - controlBar.height
        width: mainRect.width
        border.color: "#078491"
        border.width: 1

        ScrollView {
            ScrollBar.vertical.interactive: true
            height: parent.height
            width: parent.width

            ListView {
                id: listView

                model: chatListModel

                delegate: ChatBlock {
                    height: chatListView.width / 4
                    width: chatListView.width
                }
            }
        }
    }
    Connections {
        target: controlBar
        function onNewChatButtonClicked() {
            addNewChat();
        }
    }
}
