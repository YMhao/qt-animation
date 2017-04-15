#include "widget.h"
#include "ui_widget.h"
#include "animation.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    m_animation = new Animation(this);
    m_animation->setAnimation(QPixmap(":/image/num.png"),10,200);
    m_animation->setGeometry(100,100,41,41);
    m_animation->show();
    m_animation->setLoop(true); // 循环播放
    m_animation->setLoop(true); // 只播放一次
    m_animation->startClockwise();// 顺时针播放每帧
    //m_animation->startCounterclockwise();// 逆时针播放每帧
}

Widget::~Widget()
{
    delete ui;
}
