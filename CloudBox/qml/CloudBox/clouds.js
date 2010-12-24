var componentCloud = Qt.createComponent("Cloud.qml");

function spawnRandomCloud()
{
    spawnCloudAt(Math.floor(Math.random() * loginWindow.width)-100)
}

function spawnCloud()
{
    spawnCloudAt(loginWindow.width);
}

function spawnCloudAt(origin)
{
    if(componentCloud.status == Component.Ready){
        var dynamicObject = componentCloud.createObject(loginWindow);
        if(dynamicObject == null){
            console.log("error creating cloud");
            console.log(componentCloud.errorString());
            return false;
        }

        dynamicObject.speed = Math.floor(Math.random() * 15000 + 15000);
        dynamicObject.sourceSize.width = Math.floor(Math.random() * 75 + 50);
        dynamicObject.sourceSize.height = dynamicObject.sourceSize.width;
        dynamicObject.width = dynamicObject.sourceSize.width;
        dynamicObject.height = dynamicObject.sourceSize.height;
        dynamicObject.y = Math.floor(Math.random() * loginWindow.height/2 - 20);
        dynamicObject.x = origin;
        dynamicObject.constructed = true;

    }else{
        console.log("error loading cloud component");
        console.log(componentCloud.errorString());
        return false;
    }
    return true;


}
