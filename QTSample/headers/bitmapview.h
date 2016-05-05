#ifndef BITMAPVIEW_H
#define BITMAPVIEW_H

#include <QWidget>

class BitmapView : public QWidget
{
    Q_OBJECT
public:
    explicit BitmapView(QWidget *parent = 0);
    ~BitmapView();

private:
    void paintEvent(QPaintEvent*);

};

#endif // BITMAPVIEW_H
