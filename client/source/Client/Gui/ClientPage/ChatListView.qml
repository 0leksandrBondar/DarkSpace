import QtQuick 2.15

Rectangle
{
    id: mainRect
    color: "#242625"

    Flickable
    {
        anchors.fill: parent
        contentWidth: column.width
        contentHeight: column.height
        Column
        {
            id: column
            width: mainRect.width
            Repeater
            {
                model: 30 // number of items created
                ChatBlock
                {
                    id: chatBlock
                    Text
                    {
                        anchors.centerIn: chatBlock
                        width: chatBlock.width / 2;
                        height: chatBlock.height / 2;
                        text: "Some chat"
                        color: "#1cfc6a"
                    }
                }
            }
        }
    }
}
