import Qt 4.7

Rectangle {
    color: "transparent"

    Rectangle {
        color: "blue"
        opacity: .05
        anchors.fill: parent
    }

    GridView {
        id:fileListView
        anchors.fill: parent
        model:FileListModel
        delegate:  fileListDelegate
        width: 100
        height: 62
        cellWidth: parent.width
        cellHeight: parent.height/7

    }

    Component {
        id:fileListDelegate
        Text {
            color: "red"
            font.family: "Helvetica"
            id: fileName
            text: display
        }
    }
}
