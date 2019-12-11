#ifndef QIPAN_H
#define QIPAN_H

#include <QTableWidget>

class qipan : public QTableWidget
{
    Q_OBJECT
public:
    explicit qipan(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *e);

    void my_black(int m,int n/*,int i*/);   //黑棋子
    void my_white(int m,int n/*,int i*/);   //白棋子
    int my_xiaqi(int m,int n,int a,int c);   //人人
    void my_time ();

    void wuqikexia();          //判断是否还可以继续
    void qingpan();


    int qizitongji();
    int qizitongji_B();

    void my_zhineng();
    void my_zhineng_g();

    int sheixianxia2(int a,int ai1);

signals:
    void sheixianxia(void);

public slots:
};

#endif // QIPAN_H
