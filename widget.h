#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Animation;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    Animation *m_animation;
};

#endif // WIDGET_H
