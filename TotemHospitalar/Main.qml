import QtQuick
import QtQuick.Layouts
import QtQuick.Controls.Basic

import QtQuick.VirtualKeyboard

ApplicationWindow {
    id: window
    width: 1080
    height: 1920
    minimumWidth: 200
    minimumHeight: 250
    visible: true
    title: qsTr("Totem")
    property bool lightMode: Application.styleHints.colorScheme === Qt.Light
    property color reallyDark: "#1f1f1f"
    property color dark: "#262626"
    property color reallyLight: "#e7e7e7"
    property color light: "#e0e0e0"

    color: lightMode ? reallyLight : dark

    Column{
        anchors.centerIn: parent
        spacing: 30

        Text {
            text: qsTr("Bem vindo")
            font.pixelSize: 42
            font.bold: true
            color: window.lightMode ? "#2c3e50":"white"
            anchors.horizontalCenter: parent.horizontalCenter
        }
        TextField {
            id: campoCpf
            width: 400
            height: 60
            font.pixelSize: 28
            placeholderText: "Toque para digitar o CPF... "
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Button{
            text: "Atendimento Normal"
            width: 400
            height: 100
            font.pixelSize: 32
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: totemController.printTicket("NORMAL", campoCpf.text)
        }
        Button{
            text: "Atendimento Prioritário"
            width: 400
            height: 100
            font.pixelSize: 32
            anchors.horizontalCenter: parent.horizontalCenter
            onClicked: totemController.printTicket("PRIORITARIO", campoCpf.text)
        }

    }

    InputPanel {
        id: inputPanel
        z: 99
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges {
                inputPanel.y: window.height - inputPanel.height
            }
        }

        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            NumberAnimation {
                properties: "y"
                easing.type: Easing.InOutQuad
            }
        }
    }


}
