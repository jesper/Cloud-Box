import Qt 4.7

Rectangle {
    id: button

    border.color: "black"
    border.width: 2
    gradient: Gradient {
        GradientStop { position: 0.0; color: "white" }
        GradientStop { position: 1.0; color: "lightblue" }
    }

    smooth: true
    radius: 7

    Text {
        id: text
        color: "black"
        text: "Login"
        font.pixelSize: (button.height) - (button.height/2)
        anchors.centerIn: parent
        x: 5
    }

    Image
    {
        source: "qrc:/images/login.svg"
        anchors.verticalCenter: parent.verticalCenter
        x: button.width - width - 5
    }

    Keys.onPressed: {
        if (event.key == Qt.Key_Enter || event.key == Qt.Key_Return || event.key == Qt.Key_Space) {
            state = "pressed"
        }
    }

    onFocusChanged: {
        if (focus)
            border.width = 3
        else
            border.width = 2
    }

    MouseArea {
        id:mouse
        anchors.fill: parent
        onClicked: {
            parent.state = "pressed";
        }
    }

    states: [
        State {
            name: "pressed"
            PropertyChanges { target: button; scale: 1.05 }
        }
    ]
    transitions: Transition {
        SequentialAnimation {
            NumberAnimation { properties: "scale"; duration: 100; easing.type: Easing.InOutQuad }
            ScriptAction {
                script: button.state = ""
            }
        }
    }

}
