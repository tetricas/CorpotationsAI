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

        width: mainWin.width
        height: mainWin.height

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

        backButton.onClicked: dialogStackView.pop();
        goButton.onClicked: map.setTurn();
        map.onGameFinished:
        {
            console.log(winner)
            winMsg.text = winner+ "win"
            winMsg.open()
            dialogStackView.pop();
        }
        map.onUpdateScore:
        {
            scoreYouText = "You: " + player
            scoreBot1Text = " Clac: " + firstBot
            scoreBot2Text = " Cloc: " + secondBot
        }
    }

    AboutDialog{
        id: aboutDlg
        height: 500
        width: 400
    }

    MessageDialog  {
        id: winMsg
        title: "Game finished"
    }
}
