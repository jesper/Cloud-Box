import Qt 4.7

Column {
    id:info
    spacing: 10

    StyledText {
        text: Dropbox.getAccountName()
        font.pixelSize: parent.width/15
    }

    StyledText {
        text: Dropbox.getAccountEmail()
        font.pixelSize: parent.width/15
    }
}
