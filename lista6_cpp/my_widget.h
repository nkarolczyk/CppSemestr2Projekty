#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <vector>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    constexpr static double DEFAULT_RADIUS = 75.0;  // Promień kółek, w pikselach

    explicit MyWidget(QWidget *parent = nullptr);       // Konstruktor
    void paintEvent(QPaintEvent *event) override;       // Obsługuje zdarzenie repaint(), czyli "odmaluj swój wygląd"
    void mousePressEvent(QMouseEvent *event) override;  // Obsługuje zdarzenia myszy
    void wheelEvent(QWheelEvent *event) override;       // Obsługuje zdarzenia ruchu kółka myszy

    struct Circle
    {
        QPointF center;  // QPointF to punkt o współrzędnych zmiennopozycyjnych, stąd `F` na końcu nazwy
        double radius;
    };

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    std::vector<Circle> circles;
};

#endif  // MYWIDGET_H
