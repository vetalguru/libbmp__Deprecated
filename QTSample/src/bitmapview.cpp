#include "bitmapview.h"

#include <QPainter>
#include <QBrush>
#include <QPen>

BitmapView::BitmapView(QWidget *parent)
    : QWidget(parent)
{
}

BitmapView::~BitmapView()
{
}

void BitmapView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QRect curRect = geometry();

    painter.drawLine(curRect.topLeft(), curRect.bottomRight());
    painter.drawLine(curRect.topRight(), curRect.bottomLeft());
    painter.drawRect(curRect);
}
