import Qt 4.7

Item {
    id:container
    width: Helper.getScreenWidth();
    height: Helper.getScreenHeight();

    Login {
        id: loginWindow
        visible: !Dropbox.hasValidKeys();
    }

}
