import QtQuick 2.15

Rectangle
{
    id: chatRect
    border.color: "#078491"
    border.width: 1
    color: "#242625"

    property string chatName


    Text {
        anchors.centerIn: chatRect
        width: chatRect.width / 2
        height: chatRect.height / 2
        text: "1111"
        color: "#1cfc6a"
    }
    MouseArea
    {
        id: mouseArea
        anchors.fill: parent
        onClicked:
        {
            console.log("ChatBlock was clicked!")
        }
        onEntered:
        {
            color = "#505151"
        }
        onExited:
        {
            color = "#242625"
        }
    }
}
