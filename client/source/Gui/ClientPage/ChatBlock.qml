import QtQuick 2.15

Rectangle {
    border.color: "#078491"
    border.width: 1
    color: "#242625"

    property string chatName: ""

    signal newChatIsSelected(string chatName);

    Text {
        id: text
        anchors.centerIn: parent
        color: "white"
        text: chatName
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            console.log("ChatBlock was clicked!")
            newChatIsSelected(text.text)
        }
        onEntered: {
            color = "#505151"
        }
        onExited: {
            color = "#242625"
        }
    }
}
