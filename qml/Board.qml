import QtQuick 2.0

Item
{
  id: board

  Repeater
  {
    id: rep
    anchors.fill: board
    model: GameWorld

    property int el_width: rep.width/15
    property int el_height: rep.height/20
    Rectangle
    {
      id: rect
      width: rep.el_width
      height: rep.el_height
      x: posX * rep.el_width
      y: posY * rep.el_height

      color: "transparent"
      border.color: "dark grey"
      border.width: 1

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
            GameWorld.field_clicked(index);
          }
        }
      }
    }//rect
  }//rep
}//board
