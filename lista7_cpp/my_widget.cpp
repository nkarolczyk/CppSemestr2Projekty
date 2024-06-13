#include "my_widget.h"
#include <QPainter>
#include <QRadialGradient>
#include <QBrush>
#include <QPen>

MyWidget::MyWidget(QWidget* parent)
    : QWidget(parent), timer(this)
{
    timer.start(timer_interval);
    connect(&timer, SIGNAL(timeout()), this, SLOT(on_timer()));
}

void MyWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QColor("#aeadac")));
    painter.drawRect(this->rect());

    painter.translate(rect().width() / 2.0, rect().height() / 2.0);
    auto side = std::min(rect().width(), rect().height());
    painter.scale(side / 200.0, side / 200.0);
    painter.setPen(Qt::NoPen);

    int promien = 10;
    int radius_of_rotation = 60;

    for (int i = 0; i < num_disks; i++)
    {
        if (i != hidden)
        {
            QPointF centrum(radius_of_rotation, 0);

            QRadialGradient radialGrad(centrum, promien);
            radialGrad.setColorAt(0, QColor(186, 85, 211, 255));
            radialGrad.setColorAt(0.7, QColor(186, 85, 211, 150));
            radialGrad.setColorAt(1, QColor(186, 85, 211, 0));

            painter.setBrush(QBrush(radialGrad));
            painter.drawEllipse(centrum.x() - promien, centrum.y() - promien, promien * 2, promien * 2);
        }
        painter.rotate(360.0 / num_disks);
    }

    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(Qt::black, 2));
    int crossSize = 8;
    painter.drawLine(-crossSize / 2, 0, crossSize / 2, 0);
    painter.drawLine(0, -crossSize / 2, 0, crossSize / 2);
}

void MyWidget::on_timer()
{
    hidden = (hidden + 1) % num_disks;
    update();
}

void MyWidget::toggle_animation()
{
    if (timer.isActive())
        timer.stop();
    else
        timer.start(timer_interval);
}
