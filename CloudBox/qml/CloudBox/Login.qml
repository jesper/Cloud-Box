import Qt 4.7

Rectangle {
    id: loginWindow
    anchors.fill:  parent

    gradient: Gradient {
        GradientStop { position: 0.0; color: "#83A7C4" }
        GradientStop { position: 1.0; color: "#00509C" }
    }

    Image {
        source: "qrc:/images/box.svg"
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height/10
        sourceSize.width: parent.width - 100
        sourceSize.height: parent.width - 100
        width: sourceSize.width
        height: sourceSize.height
        fillMode: Image.PreserveAspectFit
    }

    UserInput
    {
        id:email
        anchors.horizontalCenter: parent.horizontalCenter
        y: (parent.height/4) * 3
        width: parent.width - 20
        height: parent.height/11
        text: "john@doe.com"
    }

    UserInput
    {
        id:password
        anchors.horizontalCenter: parent.horizontalCenter
        y: email.height + email.y + 6
        width: parent.width - 20
        height: parent.height/11
        echoMode: TextInput.Password
        text: "********"
    }

    Text {
        y: parent.height - height - 3
        anchors.horizontalCenter: parent.horizontalCenter
        style: Text.Raised
        styleColor: "black"
        color: "white"

        text: "Dont have Dropbox? <u>Click here.</u>"
        font.pixelSize: parent.height/40

        MouseArea {
            anchors.fill: parent
            onClicked: {
                Helper.openDropboxPage();
            }
        }
    }

}
