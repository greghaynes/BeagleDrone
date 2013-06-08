#include "gimbalwidget.h"

#include <QPainter>
#include <QString>

#include <QDebug>

struct GimbalWidgetPrivate
{
    GimbalWidgetPrivate(GimbalWidget *q) : q_ptr(q) { }
    GimbalWidget *q_ptr;

    float pitch_marker_padding;
    int pitch_marker_cnt;
    int pitch_marker_width;
    int pitch_marker_deg;
};

GimbalWidget::GimbalWidget(QWidget *parent) :
    QWidget(parent),
    d_ptr(new GimbalWidgetPrivate(this))
{
    setWindowTitle("Gimbal");
    setConstants();
}

GimbalWidget::~GimbalWidget()
{
    delete d_ptr;
}

void GimbalWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    drawHorizon(painter);
    drawPitchMarkers(painter);
}

void GimbalWidget::setConstants()
{
    GimbalWidgetPrivate *d = d_ptr;
    d->pitch_marker_padding = .1;
    d->pitch_marker_cnt = 4;
    d->pitch_marker_width = 10;
    d->pitch_marker_deg = 10;
}

void GimbalWidget::drawPitchMarkers(QPainter &painter)
{
    int scene_offset = height() * d_ptr->pitch_marker_padding;
    int start_px = scene_offset;
    int end_px = height() - scene_offset;
    int pitch_height = end_px - start_px;
    float marker_distance = (float)pitch_height / ((d_ptr->pitch_marker_cnt * 2) + 1);
    painter.setPen(Qt::white);

    int i;
    int mid = width() / 2;
    int x_start = mid - d_ptr->pitch_marker_width / 2;
    int x_end = mid + d_ptr->pitch_marker_width / 2;
    int cur_deg = -(d_ptr->pitch_marker_cnt * d_ptr->pitch_marker_deg);
    for(i = 0;i < (d_ptr->pitch_marker_cnt * 2) + 1; ++i) {
        int y = start_px + (marker_distance * i) + (marker_distance / 2);
        if(cur_deg == 0)
            painter.setPen(Qt::red);
        painter.drawLine(x_start, y, x_end, y);
        painter.drawText(x_end + 2, y + 3, QString::number(cur_deg));
        if(cur_deg == 0)
            painter.setPen(Qt::white);
        cur_deg += d_ptr->pitch_marker_deg;
    }
}

void GimbalWidget::drawHorizon(QPainter &painter)
{
    painter.fillRect(0, height() / 2, width(), height(), Qt::darkGreen);
    painter.fillRect(0, 0, width(), height() / 2, Qt::darkBlue);
    painter.drawLine(0, height() / 2, width(), height() / 2);
}
