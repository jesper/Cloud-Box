import Qt 4.7
import "filelists.js" as FileLists

Rectangle {
    id:fileList

    function listFiles(path) {
        var y = fillerText.y + fillerText.height + 10
        var view = FileLists.createFileListView(y);
        Dropbox.listFiles(path);
    }

    color:"transparent"

    Text {
        id:fillerText
        z: loginWindow.z - 1
        text: "Filler Text"
        font.pixelSize: 50
        MouseArea {
            anchors.fill: parent
            onClicked:listFiles("");
        }
    }
}
