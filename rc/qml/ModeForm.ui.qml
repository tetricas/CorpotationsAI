import QtQuick 2.4
import QtQuick.Controls 2.0
import game_space 1.0

Item {
    property alias backButton: backButton

    property alias easyBtn: easyBtn
    property alias normalBtn: normalBtn
    property alias hardBtn: hardBtn

    Rectangle{
        anchors.fill: parent
        color: "#0A2E36"
    }

    MainButton{
        id: backButton
        height: width/3
        name: "back"
        anchors.top: parent.top
        anchors.topMargin: easyBtn.width/30
        anchors.right: easyBtn.left
        anchors.rightMargin: easyBtn.width/30
        anchors.left: parent.left
        anchors.leftMargin: easyBtn.width/30
    }

    MainButton{
        id: easyBtn
        name: "Easy mode"
        anchors.bottom: normalBtn.top
        anchors.bottomMargin: parent.height/9
        height: parent.height/9
        width: parent.height/2
        anchors.horizontalCenter: parent.horizontalCenter
    }
    MainButton{
        id: normalBtn
        name: "Normal mode"
        anchors.centerIn: parent
        height: parent.height/9
        width: parent.height/2
    }
    MainButton{
        id: hardBtn
        name: "Hard mode"
        anchors.top: normalBtn.bottom
        anchors.topMargin: parent.height/9
        height: parent.height/9
        width: parent.height/2
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
