import Qt 4.7

Rectangle {
    id: background
    anchors.fill: parent

    color: "transparent"
    Rectangle {
        anchors.fill:  parent
        opacity: 0.90
        color: "black"
    }


    MouseArea {
        anchors.fill: parent
    }

    Image {
        source: "qrc:/images/cloud.svg"
        anchors.centerIn: parent
        sourceSize.width: parent.width - parent.width/3
        sourceSize.height: parent.width - parent.width/3
        width: sourceSize.width
        height: sourceSize.height

        SequentialAnimation on rotation  {
            loops: Animation.Infinite
            PropertyAnimation { from: 0; to:360; duration: 1500;}

        }
    }



}
