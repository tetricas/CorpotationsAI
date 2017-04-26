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

        startBtn.onClicked: dialogStackView.push(gameItem)

        aboutBtn.onClicked: aboutDlg.open()
        exitBtn.onClicked: close()
    }

    GameForm{
        id: game

        backButton.onClicked:dialogStackView.push(startItem);
        goButton.onClicked: map.setTurn();
    }

    AboutDialog{
        id: aboutDlg
        height: 500
        width: 400
    }
}
