import Qt 4.7

Rectangle {
    id:container
    width: Helper.getScreenWidth();
    height: Helper.getScreenHeight();

    gradient: Gradient {
        GradientStop { position: 0.0; color: "#83A7C4" }
        GradientStop { position: 1.0; color: "#00509C" }
    }


    Login {
        id: loginWindow
        //  visible: !Dropbox.hasValidKeys();
        visible: false
    }

    AccountInfo {
        anchors.fill: parent
        visible: false
    }

    Rectangle {
        id:filler
        anchors.fill: parent
        color:"transparent"
       // visible: false

        Text {
            id:fillerText
            z: loginWindow.z - 1
            text: "Filler Logged In"
            font.pixelSize: 50
        }

        FileListView {
            y: fillerText.y + fillerText.height + 10
            height: parent.height - y
            width: parent.width
        }

    }

    BusyOverlay
    {
        id:busyOverlay
        visible: false
    }

}
