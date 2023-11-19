import QtQuick 2.15

Rectangle
{
    id: correspondenceScene

    property var message: null
    property var imageMessage: null
    property string prefix : "file:"

        function addNewMessage(data, userName)
    {
        if(message == null)
        {
            var component = Qt.createComponent("Message.qml")
            message = component.createObject(messageList)
            if(message !== null)
            {
                message.title = userName
                message.message = data
                flickableContent.contentY = messageList.height - flickableContent.height;
            }
            message = null
        }
    }
    function addNewImageMessage(path)
    {
        if(imageMessage == null)
        {
            console.log(" 0 " + prefix + path)
            var component = Qt.createComponent("ImageMessage.qml")
            imageMessage = component.createObject(messageList)
            if(imageMessage !== null)
            {
                imageMessage.pathToImage = prefix + path
                flickableContent.contentY = messageList.height - flickableContent.height;
            }
            imageMessage = null
        }
    }

    width: parent.width
    height: parent.height - messageField.height
    anchors.top: parent.top
    color: "#242625"
    Flickable
    {
        id: flickableContent
        anchors.fill: parent
        contentWidth: messageList.width
        contentHeight: messageList.height
        Column
        {
            id: messageList
            spacing: 15
        }
    }

    Connections
    {
        target: clientClass
        function onGetMessageFromServer(data, userName)
        {
            addNewMessage(data, userName)
        }
    }
}
