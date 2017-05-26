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

        startBtn.onClicked: dialogStackView.push(game)
        modeBtn.onClicked: dialogStackView.push(mode)
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
            scoreBot1Text = " Green: " + firstBot
            scoreBot2Text = " Blue: " + secondBot
        }
    }

    ModeForm {
        id: mode

        backButton.onClicked: dialogStackView.pop();
        easyBtn.onClicked:
        {
            game.map.gameMode = "easy"
            dialogStackView.pop()
        }
        normalBtn.onClicked:
        {
            game.map.gameMode = "normal"
            dialogStackView.pop()
        }
        hardBtn.onClicked:
        {
            game.map.gameMode = "hard"
            dialogStackView.pop()
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
