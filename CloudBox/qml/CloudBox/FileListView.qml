import Qt 4.7

Rectangle {
    id:fileListView
    clip: true
    color: "transparent"

    property alias model: listView.model
    property bool animate: false;
    property bool commitSuicide: false;

    Behavior on x {
        enabled: animate;
        SequentialAnimation {
            NumberAnimation {easing.type: Easing.InOutQuad; duration: 300}
            ScriptAction {
                script: {
                    if (commitSuicide)
                        fileListView.destroy();

                    animate = false
                }
            }
        }
    }

    ListView {
        id: listView
        anchors.fill: parent
        delegate:  fileListDelegate

        header:
            Rectangle {
            id: fileHeader
            width: parent.width
            height: 60
            border.color: "black"
            gradient: Gradient {
                GradientStop { position: 0.0; color: "white" }
                GradientStop { position: 1.0; color: "lightsteelblue" }
            }

            Image {
                id: backArrow
                anchors.verticalCenter: parent.verticalCenter
                //TBD Replace with a blue arrow or similar
                source: "qrc:/images/login.svg"
                rotation: 180
            }

            Text {
                x: backArrow.width + 10
                color: "black"
                font.family: "Helvetica"
                font.pixelSize: parent.width/20
                anchors.verticalCenter: parent.verticalCenter
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if (animate)
                        return;

                    fileListView.animate = true
                    fileListView.x = width
                    fileListView.commitSuicide = true
                    container.fileClicked("");
                }
            }
        }
    }

    Component {
        id:fileListDelegate

        Item{
            id:fileListDelegateItem
            width: fileListView.width
            height: fileListView.height/10

            Row {
                spacing: 10

                Rectangle {
                    id: cellBackground
                    x: 5
                    color: "green"
                    width: fileListView.width
                    height: 60
                    border.color: "black"
                    gradient: Gradient {
                        GradientStop { position: 0.0; color: "white" }
                        GradientStop { position: 1.0; color: "lightsteelblue" }
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if (animate)
                                return;

                            fileListView.animate = true
                            fileListView.x = width * -1
                            fileListView.commitSuicide = true
                            //fileList.listFiles("forward", path);
                            container.fileClicked(path);
                        }
                    }

                    Image {
                        id: icon
                        x: 5
                        source: iconPath
                        width: 48
                        height: 48
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Text {
                        id: fileName
                        x: icon.x + icon.width + 10
                        color: "black"
                        font.family: "Helvetica"
                        text: name
                        font.pixelSize: fileListView.width/20
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    Image {
                        x: fileListView.width - 48
                        visible: isFolder
                        anchors.verticalCenter: parent.verticalCenter
                        //TBD Replace with a blue arrow or similar
                        source: "qrc:/images/login.svg"
                    }
                }
            }
        }
    }
}
