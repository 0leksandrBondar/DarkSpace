import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle
{
    width: 300
    height: 400
    property string pathToImage
    id: imageRect
    Image
    {
        anchors.fill: parent
        source: pathToImage //"file:C:/Users/aleks/Desktop/a.png"
    }
}