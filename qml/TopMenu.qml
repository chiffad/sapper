import QtQuick 2.0

Rectangle
{
  id: root
  color: background.color
  border.color: "dimgray"
  border.width: 1

  Row
  {
    Item
    {
      id: game_status
      height: root.height
      width: root.width/2

      Rectangle
      {
        id: button
        anchors.centerIn: game_status
        height: game_status.height/2
        width: height
        color: "transparent"
        border.color: "black"
        border.width: 1

        Image
        {
          anchors.fill: button
          property var res: ["res/in_progress.png", "res/win.png", "res/dead.png"]
          source: res[GameWorld.game_status]
        }

        MouseArea
        {
          anchors.fill: button
          onPressed:
          {
            button.color = "grey"
            GameWorld.start_new_game();
          }
          onReleased: button.color = "transparent"
        }
      }
    }

    Item
    {
      id: click_mode
      height: root.height
      width: root.width/2

      Rectangle
      {
        id: button2
        anchors.centerIn: click_mode
        height: click_mode.height/2
        width: height
        color: "transparent"
        border.color: "black"
        border.width: 1

        Image
        {
          anchors.fill: button2
          property var res: ["res/bomb.png", "res/flag.png"]
          source: res[GameWorld.click_mode]
        }

        MouseArea
        {
          anchors.fill: button2
          onPressed:
          {
            button2.color = "grey"
            GameWorld.change_click_mode();
          }
          onReleased: button.color = "transparent"
        }
      }
    }
  }//row
}//root

