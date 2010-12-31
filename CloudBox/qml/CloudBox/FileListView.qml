import Qt 4.7

Rectangle {

    color: "transparent"

    Rectangle {
        color: "blue"
        opacity: .05
        anchors.fill: parent
    }

    ListView {
        id:fileListView
        anchors.fill: parent
        model:FileListModel
        delegate:  fileListDelegate
    }

    Component {
        id:fileListDelegate

        Item{
            width: fileListView.width
            height: fileListView.height/10
            Row {
                spacing: 10
                Rectangle {
                    id: cellBackground
                    x: 5
                    color: "green"
                    width: fileListView.width
                    height: 60
                    border.color: "black"
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "white" }
                        GradientStop { position: 1.0; color: "lightsteelblue" }
                    }

                    Image {
                        id: icon
                        x: 5
                        source: iconPath
                        width: 48
                        height: 48
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        x: icon.x + icon.width + 10
                        color: "black"
                        font.family: "Helvetica"
                        id: fileName
                        text: name
                        font.pixelSize: fileListView.width/20
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        x: fileListView.width - 48
                        visible: true
                        text: "!" + isFolder
                    }
                }
            }
        }
    }
}
