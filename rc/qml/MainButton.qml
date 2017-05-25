import QtQuick 2.5
import QtQuick.Controls 1.4

Item{
    property alias name: name.text
    signal clicked

    Rectangle{
        color:"#036D19"
        anchors.fill: parent
        radius: height/2
        width: parent.width
    }

    Text{
        id: name
        color: "#1D263B"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: parent.height/2
    }

    MouseArea{
        anchors.fill: parent
        onClicked: parent.clicked()
    }
}
