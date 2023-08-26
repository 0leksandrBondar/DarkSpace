import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle
{
    color: "#242625"

    ChatListView
    {
        id: chatListView

        width: parent.width / 3
        height: parent.height
    }

    CorrespondenceScene
    {
        id: correspondenceScene
        anchors.right: parent.right
        width: parent.width - chatListView.width
        height: parent.height
    }
}
