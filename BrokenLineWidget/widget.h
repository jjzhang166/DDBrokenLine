#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QPropertyAnimation>


class Widget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal growthFactor READ growthFactor WRITE setGrowthFactor)
public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void initData();
    void addData();
    bool isFull();

    Q_INVOKABLE qreal growthFactor(){ return mGrowthFactor; }
    Q_INVOKABLE void  setGrowthFactor(qreal factor);

    void showAnimation();
public slots:
    void slotUpdatePieView();
protected:
    void paintEvent(QPaintEvent* );
    void resizeEvent(QResizeEvent *);
private:
    QList<QString> mData;
    int totalNum;
    double perXValue;
    double perYValue;

    QPropertyAnimation*       mAnimGrowth;
    qreal                     mGrowthFactor;
};

#endif // WIDGET_H
