var componentFileListView = Qt.createComponent("FileListView.qml");

function createFileListView(direction, model, y)
{
    if(componentFileListView.status == Component.Ready){
        var dynamicObject = componentFileListView.createObject(fileList);
        if(dynamicObject == null){
            console.log("error creating filelistview");
            console.log(componentFileListView.errorString());
            return 0;
        }

        dynamicObject.height = fileList.height - y
        dynamicObject.width = fileList.width
        dynamicObject.y = y
        dynamicObject.model = model

        if (direction == "forward")
            dynamicObject.x = fileList.width
        else
            dynamicObject.x = dynamicObject.width * -1

        dynamicObject.animate = true
        dynamicObject.x = 0

    }else{
        console.log("error loading filelistview component");
        console.log(componentFileListView.errorString());
        return 0;
    }

    return dynamicObject;
}
