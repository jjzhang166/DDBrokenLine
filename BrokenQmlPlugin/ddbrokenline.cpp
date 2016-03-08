#include "ddbrokenline.h"

#include <qdeclarative.h>
#include <QDebug>

DDBrokenLine::DDBrokenLine(QDeclarativeItem *parent):
    QDeclarativeItem(parent),mAnimGrowth(new QPropertyAnimation(this,"growthFactor"))
{
    //    QGraphicsItem::ItemHasNoContents
    mbackground = QColor("#3C5C1B");
    mlineColor = QColor("#60C018");
    mxyColor  = QColor(Qt::black);
    mShow = false;
    setFlag(QGraphicsItem::ItemHasNoContents,false);
    setCacheMode(QGraphicsItem::NoCache);
    setAcceptHoverEvents(true);
    mAnimGrowth->setStartValue(0.);
    mAnimGrowth->setEndValue(1.);
    mAnimGrowth->setDuration(1000);

    mData.clear();
    totalNum = col=row=40;
    perXValue = this->width()/(col-1.);
    perYValue = this->height()/(row-1.);
    initData();
}

DDBrokenLine::~DDBrokenLine()
{
}

///
/// \brief DDBrokenLine::showAnimation
///设置动画开始
void DDBrokenLine::showAnimation(){

    setVisible(true);
    update();
    mAnimGrowth->start();
}
///
/// \brief DDBrokenLine::append
/// \param value
///追加数据 保持数据数量显示不变
void DDBrokenLine::append(double value)
{
    if(isFull()){
        mData.removeFirst();
    }
    mData.append(QString::number(value));
    update();
}
///
/// \brief DDBrokenLine::initData
///初始化原始数据
void DDBrokenLine::initData()
{
    for(int i=0;i<totalNum/2;i++){
        double randomd =qrand()%totalNum;
        mData.append(QString::number(randomd));
    }
}

///
/// \brief DDBrokenLine::isFull
/// \return
///是否满入一屏
bool DDBrokenLine::isFull()
{
    return mData.size()>= totalNum;
}

///
/// 设置增长因子
void DDBrokenLine::setGrowthFactor(qreal factor)
{
    mGrowthFactor = factor;
    update();
}

///
/// \brief DDBrokenLine::slotUpdatePieView
/// 定时器即时更新数据内容(仅测试) 也可以由外部数据驱动
//void DDBrokenLine::slotUpdatePieView()
//{
//    if(isFull()){
//        mData.removeFirst();
//    }
//    double randomd =qrand()%totalNum;
//    if(randomd<3)randomd=3;
//    if(randomd> this->height()-20) randomd = totalNum-3;
//    mData.append(QString::number(randomd));
//    qDebug()<<"many points "<<mData.size();
//    update();
//}

///
/// \brief DDBrokenLine::paintEvent
///绘制X和Y轴 以及折线和动画处理
void DDBrokenLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *DDBrokenLine)
{
    mRectF = QRectF(0,0,this->width(),this->height());
    perXValue = this->width()/(totalNum-1.);
    perYValue = this->height()/(totalNum-1.);

    int cnt = mData.size();
    painter->setRenderHint(QPainter::Antialiasing);
    //    painter->fillRect(this->boundingRect(),background);
    painter->setBrush(mbackground);
    painter->drawRect(0,0,this->width(),this->height());
    QPen pen(mxyColor);
    pen.setWidth(mPenWidth);
    painter->setPen(pen);
    int penWid = mPenWidth;
    int height = this->height();
    //简单绘制x和y轴
    painter->drawLine(QPoint(penWid,penWid),QPoint(penWid,height-penWid*10));
    painter->drawLine(QPoint(penWid,height-penWid*10),QPoint(this->width()-penWid,height-penWid*10));

    pen.setColor(mxyColor);
    pen.setWidth(mPenWidth);
    painter->setPen(pen);
    //简单绘制X轴的刻度内容
    for(int j=0;j<totalNum;j++){
        painter->drawText(QRect(j*perXValue,height-penWid*6,12,12),Qt::AlignCenter,QString::number(j));
    }

    QVector<QLineF> mPoints;
    mPoints.clear();
    QLineF tmpPointF;
    QPointF f1;
    QPointF f2;

    //设置属性动画
    cnt = cnt * mGrowthFactor;
    //拼装多线段进行绘制
    for(int i=0;i<cnt;i++){
        if(i==0){
            f1=QPointF(penWid+1,height-mData.at(i).toDouble()*perYValue);
            f2= f1;
            tmpPointF.setP1(f1);
            tmpPointF.setP2(f1);
        }else{
            f1=QPointF((i-1)*perXValue,height-mData.at(i-1).toDouble()*perYValue);
            f2=QPointF(i*perXValue,height-mData.at(i).toDouble()*perYValue);
            tmpPointF.setP1(f1);
            tmpPointF.setP2(f2);
        }
        if(mShow){
            pen.setColor(Qt::white);
            pen.setWidth(10);
            painter->setPen(pen);
            painter->drawPoint(f2);
        }
        mPoints.append(tmpPointF);
    }
    //    painter->setBrush(Qt::NoBrush);
    pen.setColor(mlineColor);
    pen.setWidth(3);
    painter->setPen(pen);
    painter->drawLines(mPoints);
}


///
/// \brief DDBrokenLine::resizeEvent
/// \param e
///重新计算x和y轴的单位像素
QRectF DDBrokenLine::boundingRect()const
{
    //    qDebug()<<" mRecf "<<mRectF.width();
    return QRectF(0,0,mRectF.width(),mRectF.height());
}

void DDBrokenLine::setQrBackground(QColor backgb)
{
    if(mbackground != backgb){
        mbackground = backgb;
        update();
    }
}

void DDBrokenLine::setPenWidth(int backgb)
{
    if(mPenWidth != backgb){
        mPenWidth = backgb;
        update();
    }
}

void DDBrokenLine::setColumns(int cols)
{
    if(col != cols){
        col = cols;
        totalNum = col;
        update();
    }
}

void DDBrokenLine::setDrows(int backgb)
{
    if(row != backgb){
        row = backgb;
        update();
    }
}

void DDBrokenLine::setLineColor(QColor backgb)
{
    if(mlineColor != backgb){
        mlineColor = backgb;
        update();
    }
}

void DDBrokenLine::setShowPoints(bool show)
{
    if(mShow != show){
        mShow = show;
        update();
        emit showPointsChanged(show);
    }
}

void DDBrokenLine::setXyColor(QColor xy)
{
    if(mxyColor != xy){
        mxyColor = xy;
        update();
        emit xyColorChanged(xy);
    }
}
