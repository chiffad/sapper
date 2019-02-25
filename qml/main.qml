import QtQuick 2.12
import QtQuick.Window 2.12

Window
{
  id: root_window
  visible: true
  visibility: Window.FullScreen
  title: qsTr("Hello World")

  Rectangle
  {
    id: background
    color: "dark grey"
    anchors.fill: parent
  }

  Repeater
  {
    id: rep
    anchors.fill: parent
    model: BoardEntryModel

    property int el_width: root_window.width/15
    property int el_height: root_window.height/20
    Rectangle
    {
      id: rect
      width: rep.el_width
      height: rep.el_height
      x: posX * rep.el_width
      y: posY * rep.el_height

      color: "transparent"
      border.color: "dark grey"
      border.width: rect.width/20

      Image
      {
        id: img
        width: rect.width - rect.border.width
        height: rect.height - rect.border.width

        source:
        {
          switch(type)
          {
            case "b".charCodeAt(0): return "res/bomb.png"
            case "h".charCodeAt(0): return "res/hidden.png"
            case "0".charCodeAt(0): return "res/empty.png"
            default : return "res/1.png"
          }
        }

        MouseArea
        {
          anchors.fill: parent

          onClicked:
          {
            BoardEntryModel.field_clicked(index);
          }
        }
      }
    }
  }
}
