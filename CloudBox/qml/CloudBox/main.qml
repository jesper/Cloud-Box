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

    FileList {
        id:fileList
        anchors.fill: parent
        // visible: false
    }

    BusyOverlay
    {
        id:busyOverlay
        visible: false
    }
}
