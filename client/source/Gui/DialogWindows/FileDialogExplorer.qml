import QtQuick 2.15
import QtQuick.Dialogs

FileDialog
{
    id: fileDialog
    title: "Select file"
    nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
    onRejected:
    {
        console.log("Reject file selection")
    }
}