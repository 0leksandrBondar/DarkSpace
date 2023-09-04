import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    color: "#242625"

    Rectangle {
        id: chatListView

        width: parent.width / 3
        height: parent.height
        ChatListView {

        }
    }
    CorrespondenceScene
    {
        id: correspondenceScene
        anchors.right: parent.right
        width: parent.width - chatListView.width
        height: parent.height
    }
}
