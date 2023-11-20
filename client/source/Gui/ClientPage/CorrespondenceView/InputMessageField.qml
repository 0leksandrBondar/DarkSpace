import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic

import "../../DialogWindows"

Rectangle
{
    id: inputMessageField

    signal createNewImageMessage(string path)
    signal createNewMessage(string data, string userName)

    property bool isInputEmpty: textField.text.trim().length === 0

    FileDialogExplorer
    {
        id: fileExplorer
        onAccepted:
        {
            createNewImageMessage(fileExplorer.currentFile.toString().replace("file:///",""))
        }
    }

    Button
    {
        id: sendButton
        text: "Send"
        width: inputMessageField.width / 7
        height: inputMessageField.height
        anchors.right: parent.right
        enabled: !messageField.isInputEmpty
        onClicked:
        {
            console.log("Send button clicked")
            clientClass.fillMessageData(textField.text)
            createNewMessage(textField.text, qsTr("You"))
            textField.text = placeholderText.text
        }
    }
    Button
    {
        id: fileButton
        text: "File"
        width: sendButton.width
        height: inputMessageField.height
        anchors.right: sendButton.left
        onClicked:
        {
            fileExplorer.open()
        }
    }
    TextField
    {
        id: textField
        width: inputMessageField.width - sendButton.width * 2
        height: inputMessageField.height
        anchors.left: inputMessageField.left
        font.pointSize: 23
        color: "white"
        background: Rectangle
        {
            color: "#242625"
            border.color: "#078491"
            border.width: 1
        }
        PlaceholderText
        {
            font.pointSize: 23
            id: placeholderText
            color: "white"
            text: "Enter message..."
        }
        Keys.onReturnPressed:
        {
            if (!isInputEmpty)
            {
                clientClass.fillMessageData(textField.text)
                createNewMessage(textField.text,  qsTr("You"))
                textField.text = placeholderText.text
            }
        }
        onActiveFocusChanged:
        {
            if (activeFocus)
                placeholderText.text = "";

            else if (textField.text.length === 0)
                placeholderText.text = "Enter text ...";
        }
    }
}
