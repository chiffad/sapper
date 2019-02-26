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

  Column
  {
    id: elems
    anchors.fill: parent
    spacing: 2

    Rectangle
    {
      id: top_menu
      width: elems.width
      height: elems.height/10
      color: background.color
      border.color: "dimgray"
      border.width: 1
      Row
      {
        Item
        {
          id: game_status
          height: top_menu.height
          width: top_menu.width/2

          Image
          {
            anchors.centerIn: game_status
            height: game_status.height/2
            width: height

            property var res: ["res/in_progress.png", "res/win.png", "res/dead.png"]
            source: res[GameWorld.game_status]
          }
        }

        Rectangle
        {
          id: click_mode
          color: GameWorld.click_mode == 0 ?  "blue" : "white"
          height: top_menu.height
          width: top_menu.width/2

          MouseArea
          {
            anchors.fill: parent
            onClicked:
            {
              GameWorld.change_click_mode();
            }
          }
        }
      }
    }

    Board
    {
      id: board
      height: elems.height - top_menu.height
      width: elems.width
    }

  }//elems
}//root_window
