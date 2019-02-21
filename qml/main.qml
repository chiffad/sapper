import QtQuick 2.12
import QtQuick.Window 2.12

Window
{
  id: root_window
  visible: true
  visibility: Window.FullScreen
  title: qsTr("Hello World")

  Repeater
  {
    id: rep
    anchors.fill: parent
    model: BoardEntryModel

    property int el_width: root_window.width/15//rep.count;
    property int el_height: root_window.height/20// rep.count;
    Image
    {
      id: img

      x: posX * rep.el_width
      y: posY * rep.el_height

      width: rep.el_width
      height: rep.el_height

      source:
      {
        console.log("aaaaaaaa: ", type)
        if(type == 98 || type == 104) return "res/bomb.png"
        else return "res/1.png"
      }
    }
  }
}
