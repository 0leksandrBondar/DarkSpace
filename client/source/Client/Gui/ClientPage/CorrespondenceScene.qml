import QtQuick 2.15

Rectangle
{
    id: mainCorrespondenceScene

    CorrespondenceView
    {
        id: correspondenceView
    }

    InputMessageField
    {
        id: messageField
        height: 60
        width: mainWindow.width - mainWindow.width / 3
        anchors.bottom: parent.bottom
        Connections
        {
            target: messageField
            function onCreateNewMessage(data, userName)
            {
                correspondenceView.addNewMessage(data, userName)
            }
        }
    }

}
