import QtQuick 2.4
import QtQuick.Controls 2.0

Item {
    property alias backButton: backButton
    property alias serverButton: serverButton

    Button{
        id: serverButton
        height: 40
        width: 80
        text: "Server"
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Button{
        id: backButton
        height: 40
        width: 80
        text: "back"
        anchors.top: serverButton.bottom
        anchors.topMargin: height/2
        anchors.horizontalCenter: parent.horizontalCenter
    }
}
