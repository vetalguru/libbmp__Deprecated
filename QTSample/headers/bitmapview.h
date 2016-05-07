#ifndef BITMAPVIEW_H
#define BITMAPVIEW_H

#include <QWidget>

class BMPImage;

class BitmapView : public QWidget
{
    Q_OBJECT
public:
    explicit BitmapView(QWidget *parent = 0);
    ~BitmapView();

    bool openFile(const QString& aFileName);
    void closeFile();

private:
    void paintEvent(QPaintEvent*);

private:
    BMPImage *m_image;
};

#endif // BITMAPVIEW_H
