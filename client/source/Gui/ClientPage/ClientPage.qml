import QtQuick 2.15
import QtQuick.Controls 2.15

import "./ChatListView"
import "./CorrespondenceView"

Rectangle {
    color: "#242625"

    Rectangle {
        id: chatListView

        width: parent.width / 3
        height: parent.height
        ChatListView {
            id: chatList
        }
        Connections
        {
            target: chatList

            function onUpdateChatNameInInfoBar(newChatName) {
                console.log(newChatName)
                correspondenceScene.updateChatName(newChatName)
            }
        }
    }
    CorrespondenceView
    {
        id: correspondenceScene
        anchors.right: parent.right
        width: parent.width - chatListView.width
        height: parent.height
    }
}
