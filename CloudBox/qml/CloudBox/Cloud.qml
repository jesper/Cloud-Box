import Qt 4.7

Image {
    id: cloud
    property int speed
    property bool constructed: false

    source: "qrc:/images/cloud.svg"
    width: sourceSize.width
    height: sourceSize.height

    SequentialAnimation on x {
        running: constructed
        PropertyAnimation { to:cloud.width*-1; duration: speed;easing.type: Easing.Linear}
        ScriptAction {
            // Hope this actually does delete the cloud, because we certainly don't need it anymore.
            script: cloud.destroy();
        }
    }

}
