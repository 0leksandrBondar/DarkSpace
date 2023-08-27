import QtQuick
import QtQuick.Controls 2.15

import "../LoginPage" as LoginPageFolder
import "../ClientPage" as ClientPageFolder

import ClientSide 1.0

StackView
{
    id: stackPagesView
    anchors.fill: parent
    initialItem: logInPage

    Client
    {
        id: clientClass
    }

    Component
    {
        id: logInPage
        Item
        {
            LoginPageFolder.LoginPage
            {
                width: mainWindow.width
                height: mainWindow.height
                onSignInRequest:
                {
                    stackPagesView.push(clientPage)
                }
                onSignUpRequest:
                {
                    stackPagesView.push(signUpPage)
                }
            }
        }
    }

    Component
    {
        id: signUpPage
        Item
        {
            LoginPageFolder.SignUpPage
            {
                width: mainWindow.width
                height: mainWindow.height
                anchors.left: mainWindow.left
                onBackClicked:
                {
                    stackPagesView.pop()
                }
            }
        }
    }
    Component
    {
        id: clientPage
        Item
        {
            ClientPageFolder.ClientPage
            {
                width: mainWindow.width
                height: mainWindow.height
                anchors.left: mainWindow.left
            }
        }
    }
}
