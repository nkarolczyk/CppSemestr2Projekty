#include "my_widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QDebug>

MyWidget::MyWidget(QWidget* parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setFocus();
}

void MyWidget::paintEvent(QPaintEvent* event)
{
    // Obsługuje zdarzenia systemowe "odrysuj zawartość tego widżetu/okienka"
    QPainter painter(this); // painter to obiekt odpowiedzialny za opisanie i rysowanie piórem, malowanie pędzlem itp.

    painter.setRenderHint(QPainter::Antialiasing);                   // bajer. Rysunki w tym trybie wyglądają nieco lepiej.
    painter.setBrush(QBrush(QColor(Qt::GlobalColor::darkMagenta)));  // pędzel (brush) maluje duże powierzchnie
    auto r = this->rect();                                           // rect() zwraca prostokąt obszaru roboczy bieżącego okienka
    painter.drawRect(r);                                             // malujemy cały obszar roboczy kolorem darkMagenta

    painter.setBrush(QBrush(QColor(Qt::GlobalColor::darkYellow)));  // zmieniamy kolor farby na pędzlu
    for (const auto& circ : circles)                                // malujemy wszystkie "wyklikane" kółka
    {
        QPointF point(circ.center.x() * r.width(), circ.center.y() * r.height());
        painter.drawEllipse(point, circ.radius, circ.radius);  // koło jest przypadkiem szczególnym elipsy
    }
}

void MyWidget::mousePressEvent(QMouseEvent* event)
{
    // Obsługuje zdarzenia systemowe wygenerowane przyciśnięciem (któregokolwiek) klawisza myszy
    auto pos = event->localPos();           // współrzędne położenia myszy we współrzędnych obszaru roboczego bieżącego okna
    auto rec = rect();                      // prostokąt obszaru roboczego bieżącego okna
    Circle c;                               // kolejne kółko
    c.radius = DEFAULT_RADIUS;              // w tej wersji programu wszystkie kółka mają ten sam promień
    c.center.setX(pos.x() / rec.width());   // składowa "x" środka kółka
    c.center.setY(pos.y() / rec.height());  // składowa "y" środka kółka
    circles.push_back(c);                   // dodanie kółka na koniec wektora `circles`
    repaint();                              // wymuszamy odświeżenie okna bieżącego obiektu (pośrednio uruchomi MyWidget::paintEvent)
}

void MyWidget::keyPressEvent(QKeyEvent* event)
{
    // Obsługuje zdarzenia klawiatury
    if (event->modifiers() == Qt::ControlModifier && event->key() == Qt::Key_Z)
    {
        if (!circles.empty())
        {
            circles.pop_back();
            repaint();
        }
        else
        {
            qDebug() << "Brak kółek do usunięcia!";
        }
    }
    else
    {
        QWidget::keyPressEvent(event);
    }
}

void MyWidget::wheelEvent(QWheelEvent* event)
{
    if (!circles.empty())
    {
        int delta = event->angleDelta().y();
        if (delta > 0)
        {
            circles.back().radius += 5;
        }
        else if (delta < 0)
        {
            circles.back().radius -= 5;
            if (circles.back().radius < 5)
            {
                circles.back().radius = 5;
            }
        }
        repaint();
    }
}
