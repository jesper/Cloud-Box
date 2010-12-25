import Qt 4.7

Item {
    id:container
    width: Helper.getScreenWidth();
    height: Helper.getScreenHeight();

    Login {
        id: loginWindow
        visible: !Dropbox.hasValidKeys();
    }

    Text {
        z: loginWindow.z - 1
        text: "Filler Logged In"
        font.pixelSize: 50
    }

    BusyOverlay
    {
        id:busyOverlay
        visible: false
    }

}
