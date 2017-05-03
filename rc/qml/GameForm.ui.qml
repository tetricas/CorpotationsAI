import QtQuick 2.4
import QtQuick.Controls 2.0
import game_space 1.0

Item {
    property alias backButton: backButton
    property alias goButton: goButton
    property alias map: map

    Rectangle{
        anchors.fill: parent
        color: "#0A2E36"
    }

    MainButton{
        id: backButton
        height: map.width/20
        name: "back"
        anchors.bottom: map.top
        anchors.bottomMargin: map.width/30
        anchors.right: map.left
        anchors.rightMargin: map.width/30
        anchors.left: parent.left
        anchors.leftMargin: map.width/30
    }

    MainButton{
        id: goButton
        height: width
        name: "Go"
        anchors.top: map.top
        anchors.topMargin: map.width/30
        anchors.left: map.right
        anchors.leftMargin: map.width/30
        anchors.right: parent.right
        anchors.rightMargin: map.width/30
    }

    GameSpace{
        id: map
        height: parent.height/4*3
        width: height
        anchors.centerIn: parent
        blockSideSize: height/blocksCount - shift
    }
}
