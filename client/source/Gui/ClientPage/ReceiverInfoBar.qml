import QtQuick 2.15

Rectangle {
    id: receiverInfoBar
    color: "#242625"
    border.color: "#078491"
    border.width: 1
    width: parent.width
    height: 50

    Loader {
        id: loader
        source: "ChatBlock.qml"
        onLoaded: console.log("dasdsadasdsad")//item.newChatIsSelected.connect(updateChatName)
    }

    Text {
        id: chatName
        width: parent.width / 3
        text: "chat name"
        anchors.left: parent.left
        anchors.leftMargin: 20
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 23
        color: "white"
    }

    function updateChatName(chatNameValue) {
        console.log("mouse clicked!")
        chatName.text = chatNameValue;
    }

    Connections
    {
        target: loader
        onNewChatIsSelected: updateChatName(chatName)
    }
}
