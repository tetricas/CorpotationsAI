import QtQuick 2.5
import QtQuick.Controls 1.4

Rectangle {

    property alias startBtn: startBtn
    property alias reconnectBtn: reconnectBtn
    property alias connectBtn: connectBtn
    property alias aboutBtn: aboutBtn
    property alias exitBtn: exitBtn

    color: "#504747"

    MainButton{
        id: startBtn
        name: "Start"
        y: parent.height/9
        height: parent.height/9
        width: parent.height/3
        anchors.horizontalCenter: parent.horizontalCenter
    }

    MainButton{
        id: reconnectBtn
        name: "Reconnect"
        y: parent.height/9
        height: parent.height/9
        width: parent.height/3
        anchors.horizontalCenter: parent.horizontalCenter
    }

    MainButton{
        id: connectBtn
        name: "Connection"
        anchors.top: startBtn.bottom
        anchors.topMargin: parent.height/9
        height: parent.height/9
        width: parent.height/3
        anchors.horizontalCenter: parent.horizontalCenter
    }
    MainButton{
        id: aboutBtn
        name: "About"
        anchors.top: connectBtn.bottom
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
