#ifndef DDBROKENLINE_H
#define DDBROKENLINE_H

#include <QDeclarativeItem>
#include <QPainter>
#include <QPaintEvent>
#include <QTimer>
#include <QPropertyAnimation>

class DDBrokenLine : public QDeclarativeItem
{
    Q_OBJECT
    Q_PROPERTY(qreal growthFactor READ growthFactor WRITE setGrowthFactor)
    Q_PROPERTY(QColor lineColor READ ddLineColor WRITE setLineColor)
    Q_PROPERTY(int penWidth READ qrDDpenWidth WRITE setPenWidth)
    Q_PROPERTY(int columns READ ddColumns WRITE setColumns)
    Q_PROPERTY(int drows READ drows WRITE setDrows NOTIFY drowsChanged)
    Q_PROPERTY(QColor qrBackground READ qrDDBackground WRITE setQrBackground NOTIFY qrBackgroundChanged)

    Q_PROPERTY(bool showPoints READ showPoints WRITE setShowPoints NOTIFY showPointsChanged)
    Q_PROPERTY(QColor xyColor READ xyColor WRITE setXyColor NOTIFY xyColorChanged)

    Q_DISABLE_COPY(DDBrokenLine)

public:
    DDBrokenLine(QDeclarativeItem *parent = 0);
    ~DDBrokenLine();

    void initData();
    void addData();
    bool isFull();

    Q_INVOKABLE qreal growthFactor(){ return mGrowthFactor; }
    Q_INVOKABLE void  setGrowthFactor(qreal factor);

    Q_INVOKABLE void showAnimation();

    Q_INVOKABLE void append(double value);

    QColor qrDDBackground(){return mbackground;}
    Q_INVOKABLE void setQrBackground(QColor backgb);

    int qrDDpenWidth(){return mPenWidth;}
    Q_INVOKABLE void setPenWidth(int backgb);

    int ddColumns(){return col;}
    Q_INVOKABLE void setColumns(int col);

    int drows(){return row;}
    Q_INVOKABLE void setDrows(int backgb);

    QColor ddLineColor(){return mlineColor;}
    Q_INVOKABLE void setLineColor(QColor backgb);

    bool showPoints(){return mShow;}
    Q_INVOKABLE void setShowPoints(bool show);


    QColor xyColor(){return mxyColor;}
    Q_INVOKABLE void setXyColor(QColor xy);

signals:
    void qrBackgroundChanged(const QColor& qrbg);
    void drowsChanged(int rows);
    void showPointsChanged(bool show);
    void xyColorChanged(QColor color);
public slots:
//    void slotUpdatePieView();
protected:
    void paint( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
    QRectF boundingRect()const;
    QRectF       mRectF;
private:
    QList<QString> mData;
    int totalNum;
    double perXValue;
    double perYValue;

    QPropertyAnimation*       mAnimGrowth;
    qreal                     mGrowthFactor;

    int mPenWidth;
    int col;
    int row;
    QColor mbackground;
    QColor mlineColor;
    QColor mxyColor;
    bool mShow;
};

QML_DECLARE_TYPE(DDBrokenLine)

#endif // DDBROKENLINE_H

