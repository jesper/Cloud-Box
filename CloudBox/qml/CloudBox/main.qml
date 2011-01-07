import Qt 4.7

Rectangle {
    id:container
    width: Helper.getScreenWidth();
    height: Helper.getScreenHeight();

    signal signal_pathClicked(string path);

    function pathClicked(path)
    {
        signal_pathClicked(path);
    }

    gradient: Gradient {
        GradientStop { position: 0.0; color: "#83A7C4" }
        GradientStop { position: 1.0; color: "#00509C" }
    }


    Login {
        id: loginWindow
        visible: !Dropbox.hasValidKeys();
    }

    AccountInfo {
        anchors.fill: parent
        visible: false
    }

    FileList {
        id:fileList
        anchors.fill: parent
        visible: !loginWindow.visible
    }

    BusyOverlay
    {
        id:busyOverlay
        visible: false
    }
}
