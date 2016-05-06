#include "bitmapview.h"

#include <QPainter>
#include <QBrush>
#include <QPen>

#include "libbmp.h"


BitmapView::BitmapView(QWidget *parent)
    : QWidget(parent)
    , m_image(NULL)
{
}

BitmapView::~BitmapView()
{
}

bool BitmapView::openFile(const QString& aFileName)
{
    if(aFileName.isEmpty())
        return false;

    if(m_image)
        return false;

    m_image = new BMPImage(aFileName.toStdString());
}

void BitmapView::paintEvent(QPaintEvent *)
{
    if(!m_image)
        return;

    QPainter painter(this);

    QPen pen;
    for(size_t h = 0; h < m_image->height(); ++h)
    {
        for(size_t w = 0; w < m_image->width(); ++w)
        {
            BMPImage::PixelColor curColor;
            m_image->pixelColor(w, h, curColor);

            pen.setColor(QColor(curColor.Red, curColor.Green, curColor.Blue, 255 - curColor.Alpha));
            painter.setPen(pen);
            painter.drawPoint(w, h);
        }
    }
}
