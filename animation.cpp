#include "animation.h"
#include <QDebug>
#include <QTimer>
#include <QPainter>

Animation::Animation(QWidget *parent)
    : QWidget(parent)
{
    m_is_loop=false;
}

Animation::~Animation()
{

}

/**
 * @brief Animation::setAnimation
 * @param pix 链式动画图标原图
 * @param count 图片帧数
 * @param msec 切换速度 （毫秒 1秒 = 1000毫秒）
 */
void Animation::setAnimation(const QPixmap &pix, const short count, const int msec) {
    m_count = count;
    m_current_index = 0;

    if (!m_pix_list.empty()) {
        m_pix_list.clear();
    }
    else {
        /*  顺时针动画关联  */
        m_clock_timer = new QTimer(this);
        m_clock_timer->setInterval(msec);
        connect(m_clock_timer, SIGNAL(timeout()), this, SLOT(updateClockwise()));

        /*  逆时针动画关联  */
        m_counterm_clock_timer = new QTimer(this);
        m_counterm_clock_timer->setInterval(msec);
        connect(m_counterm_clock_timer, SIGNAL(timeout()), this, SLOT(updateCounterclockwise()));
    }

    /*  链式动画图标分离  */
    for(short i=0; i != count; ++i) {
        m_pix_list.append(pix.copy(i * (pix.width() / count), 0,
                        pix.width() / count, pix.height()));
    }

    m_current_pix = m_pix_list.at(0);
    this->setGeometry(0,0,m_current_pix.width(),m_current_pix.height());

    update();

}

void Animation::startClockwise()
{
    m_current_index = 0;
    m_clock_timer->start();
}

void Animation::startCounterclockwise()
{
    m_current_index = m_count - 1;
    m_counterm_clock_timer->start();
}

void Animation::stop()
{

}

void Animation::updateClockwise(void) {
    do {
        if (m_current_index < m_count && m_current_index >= 0) {
            /*  更新帧  */
            m_current_pix = m_pix_list.at(m_current_index);
            update();

            /*  判断帧数  */
            if (m_current_index >= (m_count - 1)) {
                if(m_is_loop) {
                    m_current_index = 0;
                    return;
                }
                break;
            }

            /*  跳帧  */
            ++m_current_index;
            return;
        }
    #ifndef QT_NO_DEBUG
        else {
            qDebug() << __FUNCTION__ << "waring: 错误的下标" << m_current_index;
        }
    #endif
    } while(false);

    m_clock_timer->stop();
    m_current_index = 0;
    emit clockwiseFinished();
}

void Animation::updateCounterclockwise()
{
    do {
        if (m_current_index < m_count && m_current_index >= 0) {
            /*  更新帧  */
            m_current_pix = m_pix_list.at(m_current_index);
            update();

            /*  判断帧数  */
            if (m_current_index == 0) {
                if(m_is_loop) {
                    m_current_index = m_count -1;
                    return;
                }
                break;
            }

            /*  跳帧  */
            --m_current_index;
            return;
        }
    #ifndef QT_NO_DEBUG
        else {
            qDebug() << __FUNCTION__ << "waring: 错误的下标" << m_current_index;
        }
    #endif
    } while(false);

    m_clock_timer->stop();
    m_current_index = 0;
    emit counterclockwiseFinished();
}


void Animation::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(rect(), m_current_pix);
}
