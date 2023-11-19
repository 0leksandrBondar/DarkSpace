import QtQuick 2.15
import QtQuick.Dialogs

FileDialog
{
    id: fileDialog
    title: "Select file"
    nameFilters: ["file txt (*.txt)", "all files(*)"]
    onAccepted:
    {
        console.log("Selected file: " + fileDialog.fileUrl)
    }
    onRejected:
    {
        console.log("Reject file selection")
    }
}