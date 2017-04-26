import QtQuick 2.5
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.0

Dialog {
    id: mainWin

    visible: true
    width: 640
    height: 640
    title: qsTr("Corporations")

    property alias dialogStackView: dialogStackView

    property alias startItem: start
    property alias gameItem: game
    property alias connectItem: connect

    contentItem: StackView {
        id: dialogStackView

        width: parent.width
        height: parent.height

        pushEnter: Transition {}
        popEnter: Transition {}
        pushExit: Transition {}
        popExit: Transition {}
        focus: true
        initialItem: start
    }

    MainForm {
        id: start

        startBtn.visible: game.map.isConnected
        startBtn.onClicked: dialogStackView.push(gameItem)

        reconnectBtn.visible: !game.map.isConnected
        reconnectBtn.onClicked: game.map.reconnect();

        connectBtn.onClicked: dialogStackView.push(connectItem)
        aboutBtn.onClicked: aboutDlg.open()
        exitBtn.onClicked: close()
    }

    GameForm{
        id: game

        backButton.onClicked:dialogStackView.push(startItem);
        goButton.onClicked: map.setTurn();
    }

    ConnectForm{
        id: connect

        backButton.onClicked: dialogStackView.push(startItem)
        serverButton.onClicked: game.map.makeServer();
    }

    AboutDialog{
        id: aboutDlg
        height: 500
        width: 400
    }
}
