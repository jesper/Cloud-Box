import Qt 4.7
import "clouds.js" as Clouds

Rectangle {
    id: loginWindow
    anchors.fill:  parent
    color: "transparent"

    Timer {
        interval: 3500; running: true; repeat: true
        onTriggered: Clouds.spawnCloud();
    }

    Image {
        id: logo
        z: 1
        source: "qrc:/images/box.svg"
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height/10
        sourceSize.width: parent.width - parent.width/3
        sourceSize.height: parent.width - parent.width/3
        width: sourceSize.width
        height: sourceSize.height
        fillMode: Image.PreserveAspectFit

        onStatusChanged: {
            //TBD fix the speed of these clouds - way too slow since they get a headstart.
            script: Clouds.spawnRandomCloud();
        }

        MouseArea
        {
            anchors.fill: parent
            onClicked: {
                Clouds.spawnCloud();
            }
        }
    }

    Text {
        z: 1
        y: logo.y + logo.height + 10
        anchors.horizontalCenter: parent.horizontalCenter
        style: Text.Raised
        styleColor: "black"
        color: "white"

        text: "Take your Dropbox <i>with you!</i>"
        font.pixelSize: parent.width/15

        MouseArea {
            anchors.fill: parent
            onClicked: {
                Helper.openDropboxPage();
            }
        }
    }

    UserInput
    {
        id:email
        anchors.horizontalCenter: parent.horizontalCenter
        y: (parent.height/8) * 5
        width: parent.width - 20
        height: parent.height/11
        text: "example@company.com"
        KeyNavigation.tab: password.input
        KeyNavigation.backtab: loginButton
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

        KeyNavigation.tab: loginButton
        KeyNavigation.backtab: email.input

        Keys.onPressed: {
            if (event.key == Qt.Key_Enter || event.key == Qt.Key_Return) {
                loginButton.state = "pressed";
            }
        }
    }

    Button
    {
        id:loginButton
        height: parent.height/11
        width: parent.width - 20
        anchors.horizontalCenter: parent.horizontalCenter
        y: password.y + password.height + 6

        KeyNavigation.tab: email.input
        KeyNavigation.backtab: password.input

        onStateChanged: {
            if (state == "pressed")
                busyOverlay.visible = true
        }
    }

    Text {
        y: parent.height - height - 10
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
