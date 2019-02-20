import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    visible: true
    visibility: Window.FullScreen
    title: qsTr("Hello World")

    Rectangle
    {
      id: rect
      anchors.fill: parent
      property bool foo: false
      color: foo ? "blue" : "green"

      MouseArea
      {
        anchors.fill: parent
        onClicked:
        {
          rect.foo  = !rect.foo;
        }
      }
    }
}
