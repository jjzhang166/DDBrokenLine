#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    ,mAnimGrowth(new QPropertyAnimation(this,"growthFactor"))
{
    mAnimGrowth->setStartValue(0.);
    mAnimGrowth->setEndValue(1.);
    mAnimGrowth->setDuration(1000);

    mData.clear();
    totalNum = 40;
    perXValue = this->width()/(totalNum-1.);
    perYValue = this->height()/(totalNum-1.);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotUpdatePieView()));
    //timer->start(600);
    initData();
}

Widget::~Widget()
{

}

///
/// \brief Widget::showAnimation
///设置动画开始
void Widget::showAnimation(){

    setVisible(true);
    mAnimGrowth->start();
}
///
/// \brief Widget::initData
///初始化原始数据
void Widget::initData()
{
    for(int i=0;i<totalNum;i++){
        double randomd =qrand()%totalNum;
        if(randomd<3)randomd=3;
        if(randomd> this->height()-20) randomd = totalNum-3;
        mData.append(QString::number(randomd));
    }
}

///
/// \brief Widget::isFull
/// \return
///是否满入一屏
bool Widget::isFull()
{
    return mData.size()>= totalNum;
}

///
/// 设置增长因子
void Widget::setGrowthFactor(qreal factor)
{
    mGrowthFactor = factor;
    update();
}

///
/// \brief Widget::slotUpdatePieView
/// 定时器即时更新数据内容(仅测试) 也可以由外部数据驱动
void Widget::slotUpdatePieView()
{
    if(isFull()){
        mData.removeFirst();
    }
    double randomd =qrand()%totalNum;
    if(randomd<3)randomd=3;
    if(randomd> this->height()-20) randomd = totalNum-3;
    mData.append(QString::number(randomd));
    qDebug()<<"many points "<<mData.size();
    repaint();
}

///
/// \brief Widget::paintEvent
///绘制X和Y轴 以及折线和动画处理
void Widget::paintEvent(QPaintEvent *)
{
    int cnt = mData.size();
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.fillRect(this->rect(),QColor("#3C5C1B"));
    QPen pen(Qt::white);
    pen.setWidth(2);
    p.setPen(pen);
    int penWid = pen.width();
    int height = this->height();
    //简单绘制x和y轴
    p.drawLine(QPoint(penWid,penWid),QPoint(penWid,height-penWid*10));
    p.drawLine(QPoint(penWid,height-penWid*10),QPoint(this->width()-penWid,height-penWid*10));

    pen.setColor(Qt::white);
    pen.setWidth(10);
    p.setPen(pen);
    //简单绘制X轴的刻度内容
    for(int j=0;j<totalNum;j++){
        p.drawText(QRect(j*perXValue,height-penWid*6,12,10),Qt::AlignCenter,QString::number(j));
    }

    QVector<QLineF> mPoints;
    QLineF tmpPointF;
    QPointF f1;
    QPointF f2;

    //设置属性动画
    cnt = cnt * mGrowthFactor;
    //拼装多线段进行绘制
    for(int i=0;i<cnt;i++){
        if(i==0){
            f1=QPointF(penWid,height-mData.at(i).toDouble()*perYValue);
            f2= f1;
            tmpPointF.setP1(f1);
            tmpPointF.setP2(f1);
        }else{
            f1=QPointF((i-1)*perXValue,height-mData.at(i-1).toDouble()*perYValue);
            f2=QPointF(i*perXValue,height-mData.at(i).toDouble()*perYValue);
            tmpPointF.setP1(f1);
            tmpPointF.setP2(f2);
        }
        pen.setColor(Qt::white);
        pen.setWidth(10);
        p.setPen(pen);
        p.drawPoint(f2);
        mPoints.append(tmpPointF);
    }
    p.setBrush(Qt::NoBrush);
    pen.setColor("#60C018");
    pen.setWidth(3);
    p.setPen(pen);
    p.drawLines(mPoints);
}

///
/// \brief Widget::resizeEvent
/// \param e
///重新计算x和y轴的单位像素
void Widget::resizeEvent(QResizeEvent *e)
{
    if(e->size().isValid()){
        perXValue = this->width()/(totalNum-1.);
        perYValue = this->height()/(totalNum-1.);
    }
}
