About DDBrokenLine
## DDBrokenLine Powered QML Module On QtQuick 1.1
Designing cool, interactive interfaces. DuoDuoZhijiao came up with a much better answer for DDBrokenLine: `QML`, a declarative language perfect for designing UIs (and much more). Here's a sample of how DDBrokenLine Plugin For QML 1 looks like:

## PreView

![Image](http://7qn7mv.com1.z0.glb.clouddn.com/dduiQQ%E5%9B%BE%E7%89%8720160308181002.png)

![Image](http://7qn7mv.com1.z0.glb.clouddn.com/dduixxxx.png)

```
import QtQuick 1.1
import com.ddui.qmlcomponents 1.0
 
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
```

This project aims at bringing the power of brokenLine to qml designer UI.


# Summary
* [How to build](#how-to-build)
* [How to use with DDBrokenLine](#how-to-use-with-qml-plugins)
* [How to extend](#how-to-extend)
* [Todo](#todo)

## How to Build
#### Add the source code  to your local machine on Mac Windows Linux.
#### Make Sure Setting your env for Qt SDK
#### Use Command
Git clone it.

* Build Command

```
make clean(mingw32-make clean)
qmake
make （mingw32-make mingw) | nmake(vc)
sudo make install (*unix)
```

## Use QtCreator
You may use qtcreator to build it.


## How to use with DDBrokenLine
Note that for the following, you need to have `Qt SDK` for Qt4.7.x and Qt4.8.x installed.

#### DDBrokenLine
You can use DDBrokenLine to draw brokenLine your QML


#### FeedBack

contact information

* Email(373955953#qq.com, Change#to@)
* QQ: 39559539234
* QQ Group:312125701
* github: [寒山-居士](https://github.com/toby20130333)


#### About Author

```
  var duoduozhijiao = {
    nickName  : "寒山-居士",
    site : "http://www.heilqt.com",
    blog : "http://blog.heilqt.com"
  }

```