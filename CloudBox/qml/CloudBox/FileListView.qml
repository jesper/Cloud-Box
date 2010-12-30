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

                Image {
                    id: icon
                    source:decoration
                    width: 48
                    height: 48
                }

                Text {
                    color: "black"
                    font.family: "Helvetica"
                    id: fileName
                    text: display
                }
            }
        }
    }
}
