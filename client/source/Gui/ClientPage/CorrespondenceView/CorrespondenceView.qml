import QtQuick 2.15

Rectangle {
    id: mainCorrespondenceScene

    function updateChatName(chatName)
    {
        receiverInfoBar.newChatName = chatName
    }

    CorrespondenceScene {
        id: correspondenceView
        height: parent.height - receiverInfoBar.height
        anchors.top: receiverInfoBar.bottom
    }

    InputMessageField {
        id: messageField
        height: 60
        width: mainWindow.width - mainWindow.width / 3
        anchors.bottom: parent.bottom
        Connections {
            target: messageField

            function onCreateNewMessage(data, userName) {
                correspondenceView.addNewMessage(data, userName)
            }
        }
    }
    ReceiverInfoBar {
        id: receiverInfoBar
        anchors.top: parent.top
    }
}
