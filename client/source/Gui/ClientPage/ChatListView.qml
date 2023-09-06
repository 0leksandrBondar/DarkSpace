import QtQuick 2.15
import QtQuick.Controls 2.15

import "../DialogWindows"

Rectangle {
    id: mainRect


    property var newChatBlock: null
    property string  customChatName: ""

    function addNewChat(name) {
        var component = Qt.createComponent("ChatBlock.qml");
        newChatBlock = component.createObject();

        if (component.status === Component.Ready) {
            console.log(name)
            customChatName = name;
            chatListModel.append({ chatBlock: newChatBlock });
            listView.positionViewAtEnd();
        }
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
                    chatName: customChatName
                }
            }
        }
    }
    NewChatDialogWindow {
        id: newChatWindow
    }
    Connections {
        target: clientClass

        function onUserIsConnectedToServer(userName) {
            console.log("add new  chat slot is called ")
            addNewChat(userName)
            newChatWindow.close()
        }
    }

    Connections {
        target: controlBar

        function onNewChatButtonClicked() {
            newChatWindow.open()
        }
    }
}