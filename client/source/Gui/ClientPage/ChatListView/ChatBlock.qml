import QtQuick 2.15

Rectangle
{
    border.color: "#078491"
    border.width: 1
    color: "#242625"

    property string chatName: ""
    signal newChatIsSelected(string chatName);

    Text
    {
        anchors.centerIn: parent
        text: chatName
        color: "white"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("ChatBlock was clicked!")
            newChatIsSelected(chatName)
        }
        onEntered: {
            color = "#505151"
        }
        onExited: {
            color = "#242625"
        }
    }
}
