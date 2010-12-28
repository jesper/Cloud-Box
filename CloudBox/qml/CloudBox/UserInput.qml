import Qt 4.7

Rectangle {
    id: container
    property alias text : text.text
    property alias echoMode : input.echoMode
    property alias input : input

    border.color: "black"
    border.width: 1
    gradient: Gradient {
        GradientStop { position: 0.0; color: "white" }
        GradientStop { position: 1.0; color: "lightsteelblue" }
    }

    smooth: true
    radius: 7

    Text {
        id: text
        color: "#6E7678"
        font.family: "Helvetica"
        font.pixelSize: (container.height) - (container.height/2)
        x: 5
        opacity:.5
        anchors.centerIn: parent
    }

    TextInput {
        id: input
        x: 5
        color: "#304C53"
        font.family: "Helvetica"
        anchors.centerIn: parent
        width: parent.width - (container.height/3)
        font.pixelSize: text.font.pixelSize
        horizontalAlignment: TextInput.AlignHCenter
        selectByMouse: true
        onFocusChanged: {
            text.visible = !focus

            if (input.text.length != 0)
                text.visible = false;
        }
    }
}
