#ifndef ANIMATION_H
#define ANIMATION_H

#include <QWidget>

class QTimer;

/**
 * @brief The Animation class 当前类是把链式图标做成动画的
 *    链式图片默认为10帧，默认0.1秒播放一帧
 *    可以根据自己需要进行设置与更改
 *    进行自动切割，循环播放每一帧
 *
 * example 例子:
 *   类内声明 Animation* m_animation；
 *
 *   m_animation = new Animation(this);
 *   m_animation->setAnimation(QPixmap(":/image/num.png"),10,500);
 *   m_animation->setGeometry(100,100,41,41);
 *   m_animation->show();
 *   m_animation->setLoop(true);
 *   m_animation->startClockwise(); // 顺时针播放每帧
 */
class Animation : public QWidget
{
    Q_OBJECT
public:
    explicit Animation(QWidget *parent = 0);
    ~Animation();

    /**
     * @brief Animation::setAnimation
     * @param pix 链式动画图标原图
     * @param count 图片帧数
     * @param msec 切换速度 （毫秒 1秒 = 1000毫秒）
     */
    void setAnimation(const QPixmap& _pix, const short count = 8, const int msec = 100);

    /*  开始动画(顺时针)  */
    void startClockwise(void);
    /*  开始动画(逆时针)  */
    void startCounterclockwise(void);
    /*  停止动画  */
    void stop(void);
    /*  设置动画无限循环  */
    void setLoop(const bool is_loop = false) { m_is_loop = is_loop; }

signals:

    /*  顺时针动画结束  */
    void clockwiseFinished(void);
    /*  逆时针动画结束  */
    void counterclockwiseFinished(void);

private slots:

    /*  顺时针动画槽  */
    void updateClockwise(void);
    /*  逆时针动画槽  */
    void updateCounterclockwise(void);

protected:

    void paintEvent(QPaintEvent *);

private:

    /*  动画(是否无限循环)  */
    bool m_is_loop;
    /*  图标列表数量  */
    short m_count;
    /*  当前展示的图标下标  */
    short m_current_index;
    /*  顺时针播放的定时器  */
    QTimer *m_clock_timer;
    /*  逆时针播放的定时器  */
    QTimer *m_counterm_clock_timer;
    /*  当前展示的图标  */
    QPixmap m_current_pix;
    /*  图标列表  */
    QList<QPixmap> m_pix_list;

};


#endif // ANIMATION_H
