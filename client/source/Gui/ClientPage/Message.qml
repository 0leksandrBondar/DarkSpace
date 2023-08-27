import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle
{
    id: messageBlock
    width: 300
    height: 60
    color: "#F5F5F5" // Background color

    border.color: "#CCCCCC"
    border.width: 1

    radius: 10

    property string title: ""
    property string message: ""

    Column
    {
        spacing: 5

        Text
        {
            id: titleMessage

            text: title
            font.bold: true
            color: "black"
            font.pixelSize: 14
            wrapMode: Text.Wrap
            anchors.leftMargin: 110
        }

        Text
        {
            id: messageText
            text: message
            color: "black"
            font.pixelSize: 14
            wrapMode: Text.Wrap
            anchors.leftMargin: 110
        }
    }
}
