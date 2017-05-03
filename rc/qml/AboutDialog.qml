import QtQuick 2.0
import QtQuick.Dialogs 1.2

Dialog {
    id: customDialog
    title: "About"
    contentItem:Rectangle{
        color: "#0A2E36"
        anchors.fill: parent

        Image {
            id: corpImg
            source: "qrc:/images/tree.jpg"
            height: 180
            width: 180
            anchors.top: parent.top
            anchors.topMargin: parent.height/20
            anchors.left: parent.left
            anchors.leftMargin: parent.width/20
        }
        Text{
            anchors.top: parent.top
            anchors.topMargin: parent.height/20
            anchors.left: corpImg.right
            anchors.leftMargin: parent.width/20
            font.pixelSize: 22
            color: "#00A53A"
            text: "Что-то о нас"
        }

        Text{
            anchors.top: corpImg.bottom
            anchors.topMargin: parent.height/20
            anchors.left :parent.left
            anchors.leftMargin: parent.width/20
            font.pixelSize: 22
            color: "#00A53A"
            text: "Что-то о программе"
        }

        MainButton{
            anchors.bottom: parent.bottom
            anchors.bottomMargin: parent.height/20
            anchors.right :parent.right
            anchors.rightMargin: parent.width/20
            height: parent.height/10
            width: height*2
            name: "Ok"
            onClicked: customDialog.close()
        }
    }
}
