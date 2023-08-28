import QtQuick
import QtQuick.Controls 2.15

import "../LoginPage" as LoginPageFolder
import "../ClientPage" as ClientPageFolder

import ClientSide 1.0

StackView {
    id: stackPagesView
    anchors.fill: parent
    initialItem: logInPage

    Client {
        id: clientClass
    }
    Component {
        id: wrongPage
        Item {
            InfoPage {
                id: wrong
                onOkClicked: {
                    stackPagesView.pop()
                }
            }
        }
    }
    Component {
        id: logInPage
        Item {
            LoginPageFolder.LoginPage {
                id: login
                width: mainWindow.width
                height: mainWindow.height
                onSignUpRequest: {
                    stackPagesView.push(signUpPage)
                }
            }
        }
    }

    Component {
        id: signUpPage
        Item {
            LoginPageFolder.SignUpPage {
                width: mainWindow.width
                height: mainWindow.height
                anchors.left: mainWindow.left
                onBackClicked: {
                    stackPagesView.pop()
                }
            }
        }
    }
    Component {
        id: clientPage
        Item {
            ClientPageFolder.ClientPage {
                width: mainWindow.width
                height: mainWindow.height
                anchors.left: mainWindow.left
            }
        }
    }

    Connections {
        target: clientClass

        function onRecivedSignUpRequestStatus(status) {
            console.log(" QML = onRecivedSignUpRequestStatus")
            if (status) {
                console.log("SingUp request is successful! Welcome")
                stackPagesView.push(clientPage)
            } else {
                stackPagesView.push(wrongPage)
            }
        }

        function onRecivedSignInRequestStatus(status) {
            if (status) {
                console.log("SingIn request is successful! Welcome")
                stackPagesView.push(clientPage)
            } else {
                stackPagesView.push(wrongPage)
            }
        }
    }
}
