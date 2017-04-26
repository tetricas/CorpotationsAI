import QtQuick 2.5
import QtQuick.Controls 1.4

Button{
    property alias name: name.text

    Rectangle{
        color:parent.parent.color
        y: parent.top - 10
        x: parent.left - 10
        height: parent.height + 10
        width: parent.width + 10
    }

    Rectangle{
        color:"#C6C0C0"
        anchors.fill: parent
        radius: height/2
        width: parent.width
    }

    Text{
        id: name
        color: "#3F903D"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: parent.height/2
    }
}
