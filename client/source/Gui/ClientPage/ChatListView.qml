import QtQuick 2.15
import QtQuick.Controls 2.15

import "../DialogWindows"

Rectangle {
    id: mainRect

    signal updateChatNameInInfoBar(string newChatName)

    property var newChatBlock: null
    property string  customChatName: ""

    function addNewChat(name) {
        var component = Qt.createComponent("ChatBlock.qml");
        newChatBlock = component.createObject();

        if (component.status === Component.Ready) {
            console.log(name)
            customChatName = name;
            chatListModel.append({chatBlock: newChatBlock});
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
                    id: chatBlock
                    height: chatListView.width / 4
                    width: chatListView.width
                    chatName: customChatName
                    onNewChatIsSelected: {
                        clientClass.setReceiver(chatBlock.chatName)
                        updateChatNameInInfoBar(chatBlock.chatName)
                    }
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
            addNewChat(userName)
            newChatWindow.close()
        }
        function onCreateNewChat(senderName)
        {
            addNewChat(senderName)
        }
    }
    Connections {
        target: controlBar

        function onNewChatButtonClicked() {
            newChatWindow.open()
        }
    }
}
