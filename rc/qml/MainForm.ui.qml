import QtQuick 2.5
import QtQuick.Controls 1.4

Rectangle {

    property alias startBtn: startBtn
    property alias modeBtn: modeBtn
    property alias aboutBtn: aboutBtn
    property alias exitBtn: exitBtn

    color: "#0A2E36"

    MainButton{
        id: startBtn
        name: "Start"
        y: parent.height/9
        height: parent.height/9
        width: parent.height/3
        anchors.horizontalCenter: parent.horizontalCenter
    }
    MainButton{
        id: modeBtn
        name: "Mode"
        anchors.top: startBtn.bottom
        anchors.topMargin: parent.height/9
        height: parent.height/9
        width: parent.height/3
        anchors.horizontalCenter: parent.horizontalCenter
    }
    MainButton{
        id: aboutBtn
        name: "About"
        anchors.top: modeBtn.bottom
        anchors.topMargin: parent.height/9
        height: parent.height/9
        width: parent.height/3
        anchors.horizontalCenter: parent.horizontalCenter
    }
    MainButton{
        id: exitBtn
        name: "Exit"
        anchors.top: aboutBtn.bottom
        anchors.topMargin: parent.height/9
        height: parent.height/9
        width: parent.height/3
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
