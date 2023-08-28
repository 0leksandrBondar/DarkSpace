import QtQuick 2.15

Rectangle
{
    width: parent.width
    height: parent.width / 4
    border.color: "#078491"
    border.width: 1
    color: "#242625"

    MouseArea
    {
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
