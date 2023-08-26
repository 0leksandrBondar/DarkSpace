import QtQuick
import QtQuick.Controls 2.15

import "./Controllers" as ControllersPageFolder

ApplicationWindow
{
    id: mainWindow
    width: 750
    height: 650
    minimumWidth: 450
    minimumHeight: 350
    visible: true
    title: qsTr("DarkSpace")

    ControllersPageFolder.SwitchPagesController
    {
    }
}
