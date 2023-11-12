import QtQuick 2.15
import QtQuick.Controls 2.15

import "../../DialogWindows"

Rectangle {
    id: chatListViewBlock

    signal updateChatNameInInfoBar(string newChatName)

    color: "#242625"
    height: parent.height
    width: parent.width

    ControlBar
     {
        id: controlBar

        anchors.top: chatListViewBlock.top
        width: chatListViewBlock.width
    }

    function addChat(chatName)
    {
         console.log("addChat")
         chatList.append({ name : chatName })
    }

    NewChatDialogWindow
    {
        id: newChatWindow
    }

    Rectangle
    {
        id: chatListView
         anchors.top: controlBar.bottom
         color: "#242625"
         height: chatListViewBlock.height - controlBar.height
         width: chatListViewBlock.width
         border.color: "#078491"
         border.width: 1

        ListModel
        {
            id: chatList
        }
        Component
        {
            id: chatBlockDelegate
            ChatBlock
            {
                id: chatBlock
                width: parent.width
                height: 50
                chatName: model.name
                onNewChatIsSelected:
                {
                    clientClass.setReceiver(chatBlock.chatName)
                    updateChatNameInInfoBar(chatBlock.chatName)
                }
            }
        }
        ListView
        {
            anchors.fill: parent
            model: chatList
            delegate: chatBlockDelegate
        }
    }
    Connections
    {
        target: clientClass

        function onUserIsConnectedToServer(userName) {
            addChat(userName)
            newChatWindow.close()
        }
        function onCreateNewChat(senderName)
        {
            addChat(senderName)
        }
    }
    Connections
     {
        target: controlBar
        function onNewChatButtonClicked()
        {
            newChatWindow.open()
        }
    }
}
