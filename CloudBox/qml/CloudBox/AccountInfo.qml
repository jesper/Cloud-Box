import Qt 4.7

Row {
    spacing: 10

    Column {
        spacing: 10
        StyledText {
            text: "Name"
        }
        Rectangle { color: "green"; width: 20; height: 50 }
        Rectangle { color: "blue"; width: 20; height: 50 }
    }

    Column {
        spacing: 10
        Rectangle { color: "red"; width: 20; height: 50 }
        Rectangle { color: "green"; width: 20; height: 50 }
        Rectangle { color: "blue"; width: 20; height: 50 }
    }
}
