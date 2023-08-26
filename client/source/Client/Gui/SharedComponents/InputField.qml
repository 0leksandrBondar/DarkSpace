import QtQuick 2.15
import QtQuick.Controls 2.15

TextField
{
    property string customPlaceholderText

    font.pointSize: 23
    cursorVisible: true
    placeholderText: customPlaceholderText
    width: parent.width / 1.75
    height: 40
}
