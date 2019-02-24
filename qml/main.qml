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
    color: "black"
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
      width: rep.el_width
      height: rep.el_width
      x: posX * rep.el_width
      y: posY * rep.el_height

      color: "grey"
      border.color: "black"
      border.width: 2
      radius: 3


      Image
      {
        id: img

        anchors.fill: parent

        source:
        {
          //console.log("aaaaaaaa: ", type)
          if(type == 98) return "res/bomb.png"
          else if(type == 104) return "res/hidden.jpg"
          else return "res/1.png"
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
