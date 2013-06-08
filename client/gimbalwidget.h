#ifndef GIMBAL_WIDGET_H
#define GIMBAL_WIDGET_H

#include <QWidget>

struct GimbalWidgetPrivate;

class QPainter;
class QPaintEvent;

class GimbalWidget : public QWidget
{

    public:
        GimbalWidget(QWidget *parent = 0);
        ~GimbalWidget();

    protected:
        void paintEvent(QPaintEvent *event);

    private:
        void setConstants();
        void drawPitchMarkers(QPainter &painter);
        void drawHorizon(QPainter &painter);

        GimbalWidgetPrivate *d_ptr;
};

#endif

