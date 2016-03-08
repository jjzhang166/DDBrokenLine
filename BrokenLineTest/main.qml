import QtQuick 1.1
import com.ddui.qmlcomponents 1.0

Rectangle {
    width: 360
    height: 360
    function randomNum(Min,Max){
    var Range = Max - Min;
    var Rand = Math.random();
    var num = Min + Math.round(Rand * Range);
    return num;
    }

    DDBrokenLine{
        id:bLine
        width: parent.width
        height: parent.height
        qrBackground:"#2B3E6A"
        lineColor:"#0FC542"
        xyColor:"#ffffff"
        visible: true
        penWidth:3;
        showPoints:false
    }
    Component.onCompleted: {
        bLine.showAnimation();
    }

    Timer{
        id:ti
        interval: 600
        running: true; repeat: true
        onTriggered: {
            bLine.append(randomNum(10,20));
        }
    }

}
