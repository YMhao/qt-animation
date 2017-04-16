# qt animation
qt 动画， 把链式图片做成动画

QPixmap 的透明度

```
//---画背景
    QPixmap pixmapBg(":bg.jpg");
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmapBg);

    QPixmap pixmapTop(":top.jpg");
    int alpha = 125;
//---前景图片透明度处理
    QPixmap temp(pixmapTop.size());
    temp.fill(Qt::transparent);
    QPainter p(&temp);
    p.setCompositionMode(QPainter::CompositionMode_Source);
    p.drawPixmap(0, 0, pixmapTop);
    p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
    p.fillRect(temp.rect(), QColor(0, 0, 0, alpha));
//--lable显示前景图片
    ui->label->setScaledContents(true);
    ui->label->setPixmap(temp);

```

位移
```
    QPropertyAnimation *anim=new QPropertyAnimation(ui->pushButton,"pos");
    anim->setDuration(2000);                                //动画时间
    anim->setKeyValueAt(0,QPoint(0,0));              //动画开始
    anim->setKeyValueAt(0.15,QPoint(0,200));     //第一个动画完毕并且开始第二个动画
    anim->setEndValue(QPoint(0,0));                    //第二个动画完毕
    anim->setEasingCurve(QEasingCurve::OutBounce);
    anim->start();        //执行动画
```

位移+缩放
```
//    QPropertyAnimation *anim=new QPropertyAnimation(ui->pushButton,"geometry");
//    anim->setDuration(2000);                                //动画时间
//    //anim->setStartValue(QRect(0,0,100,30));
//    anim->setKeyValueAt(0,QRect(0,0,100,30));             //动画开始
//    anim->setKeyValueAt(0.5,QRect(0,200,100,30));     //第一个动画完毕并且开始第二个动画
//    anim->setEndValue(QRect(0,0,200,30));                    //第二个动画完毕
//    anim->setEasingCurve(QEasingCurve::OutQuint);
//    anim->start();        //执行动画
```
