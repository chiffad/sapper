import QtQuick 2.0

Rectangle
{
  id: root
  color: background.color
  border.color: "dimgray"
  border.width: 1

  Row
  {
    id: row
    property int size: 3

    Item
    {
      id: bombs_counter
      height: root.height
      width: root.width/row.size

      Rectangle
      {
        id: bomb_count_rect
        anchors.centerIn: bombs_counter
        height: bombs_counter.height*(2/3)
        width: bombs_counter.width/2
        color: "transparent"
        border.color: "black"
        border.width: 1

        Text
        {
          anchors.fill: bomb_count_rect
          verticalAlignment: Text.AlignVCenter
          horizontalAlignment: Text.AlignHCenter
          fontSizeMode: Text.Fit; minimumPixelSize: 10; font.pixelSize: 70


          text: '' + GameWorld.bombs_left
          color: "red"
        }
      }
    }
    Item
    {
      id: game_status
      height: root.height
      width: root.width/row.size

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
          anchors.centerIn: button
          width: button.width - button.border.width
          height: button.height - button.border.width
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
      width: root.width/row.size

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
          anchors.centerIn: button2
          width: button2.width - button2.border.width
          height: button2.height - button2.border.width
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

