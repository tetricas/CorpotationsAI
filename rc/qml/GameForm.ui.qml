import QtQuick 2.4
import QtQuick.Controls 2.0
import game_space 1.0

Item {
    property alias backButton: backButton
    property alias goButton: goButton
    property alias map: map

    Button{
        id: backButton
        height: 20
        width: 80
        text: "back"
        anchors.bottom: map.top
        anchors.bottomMargin: height/2
        anchors.left: map.left
    }

    Button{
        id: goButton
        height: 40
        width: 40
        text: "Go"
        anchors.top: map.top
        anchors.topMargin: height/2
        anchors.left: map.right
        anchors.leftMargin: height/2
    }

    GameSpace{
        id: map
        height: parent.height/4*3
        width: height
        anchors.centerIn: parent
        blockSideSize: height/blocksCount
    }
}
