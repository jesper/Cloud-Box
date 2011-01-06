import Qt 4.7
import "filelists.js" as FileLists

Rectangle {
    id:fileList

    function listFiles(direction, path) {
        var y = fillerText.y + fillerText.height + 10
        var view = FileLists.createFileListView(direction,y);
        Dropbox.listFiles(path);
    }

    color:"transparent"

    Text {
        id:fillerText
        z: loginWindow.z - 1
        text: "[Status]  [More]"
        font.pixelSize: 50
        MouseArea {
            anchors.fill: parent
            onClicked: {
                fileList.listFiles("forward", "")
            }
        }
    }
}
