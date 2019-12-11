#include "qipan.h"

#include<QLabel>

#include <QDebug>
#include <QMouseEvent>
#include<QTableWidgetItem>
#include<QTimer>

int H_q = 0,B_q = 0,B_q1 = 0;
int a_s[8][8] = {0};
int am = 0,Ai = 0;
int a_m[8] = {1, 1,1,-1,-1,-1,0,0};
int a_n[8] = {1,-1,0,-1, 1, 0,1,-1};
int prio[8][8] =
{
    {80,0,68,66,66,68,0,80},
    {0 ,0,0 ,0 ,0 ,0 ,0,0 },
    {68,0,63,65,65,0 ,0,68},
    {66,0,65,0 ,0 ,65,0,66},
    {66,0,65,0 ,0 ,65,0,66},
    {68,0,63,65,65,0 ,0,68},
    {0 ,0,0 ,0 ,0 ,0 ,0,0 },
    {80,0,68,66,66,68,0,80},
};

qipan::qipan(QWidget *parent) : QTableWidget(parent)
{

}

void qipan::mousePressEvent(QMouseEvent *e)
{
    QPoint point = e->pos();
    QModelIndex index = this->indexAt(point);
    int n = index.column();
    int m = index.row();

    if(e->button() == Qt::LeftButton)
    {
        if(a_s[m][n] == 0)
        {
//            wuqikexia();
            if (Ai==0)
            {
                my_xiaqi(m, n, am , 1);
            }
            else if(Ai == 1){
                if (am == 0){my_xiaqi(m, n, am, 1);}
            }
        }
    }
}

//  黑棋
void qipan::my_black(int m,int n/*,int i*/)
{
        QLabel *label = new QLabel(this);
        label->resize(80,80);
        label->setPixmap(QPixmap(":/black.png"));
        this->setCellWidget (m,n,label);
        a_s[m][n] = 1;
}

//  白棋
void qipan::my_white(int m, int n/*,int i*/)
{
        QLabel *label = new QLabel(this);
        label->resize(80,80);
        label->setPixmap(QPixmap(":/white.png"));
        this->setCellWidget (m,n,label);
        a_s[m][n] = 2;
}

//Renren下棋
int qipan::my_xiaqi(int m, int n, int a, int c)
{
    int m1 = m,m2 = m,n1 = n,n2 = n,d = 0,qi,xqi;

    if (a == 0) //黑棋下
    {
        qi = 1,xqi = 2;
    }
    else if (a == 1)    //白棋下
    {
        qi = 2;xqi = 1;
    }

    for(int ii = 0; ii<8;ii++)
    {
        n1 = n2 = n,m1 = m2 = m;
        while(m1+2*a_m[ii] <8 && m1+2*a_m[ii]>=0 &&  n1+2*a_n[ii] < 8 && n1+2*a_n[ii] >=0)
        {
            n1+=a_n[ii],m1+=a_m[ii];
            int s = 0;
            if(a_s[m1][n1] == xqi)
            {
                if(a_s[m1+a_m[ii]][n1+a_n[ii]] == qi)
                {
                    qDebug()<<"mn2"<<m<<m1<<n<<n1<<c<<qi;
                    if (a == 0)
                    {
                        while(n1+a_n[ii] != n2 || m1+a_m[ii] != m2)
                        {
                            qDebug()<<"H——"<<m1<<m2<<":"<<n1<<n2<<c;
                            if (c == 1)
                            {
                                my_black(m2,n2);
                                s=1;d = 1;
                            }
                            if(c == 0)
                            {
                                d = 3;
                                H_q++;
                            }
                            m2+=a_m[ii];n2+=a_n[ii];
                        }
                    }
                    if(a == 1)
                    {
                        while(n1+a_n[ii] != n2 || m1+a_m[ii] != m2)
                        {
                            qDebug()<<"B——"<<m1<<m2<<":"<<n1<<n2<<c;
                            if (c == 1)
                            {
                                my_white(m2,n2);
                                s=1;d = 2;
                            }
                            if(c == 0)
                            {
                                d = 3;
                                if(prio[m][n] != 0)
                                {
                                    B_q = prio[m][n];
                                    return d;
                                }
                                else{B_q++;}
                            }
                            m2+=a_m[ii];n2+=a_n[ii];
                        }
                    }

                    if (s == 1 ) {break;}
                }
            }
            else {break;}
        }
    }

    if (d == 1)
    {
        am = 1;
    }
    else if(d == 2)
    {
        am = 0;
    }
    return d ;
}


//判断是否可继续
void qipan::wuqikexia()
{
    int i,j,a = 0;
    for(i = 0;i<8;i++)
    {
        for(j = 0;j <8;j++)
        {
            if (a_s[i][j] == 0)
            {
                a = my_xiaqi(i,j,am,0);
                if (a==3)
                {
                    return ;
                }
            }
        }
    }
    if (a!=3)
    {
        if (am == 0)
        {
            am = 1;
        }
        else if (am == 1)
        {
            am = 0;
        }
    }
}

void qipan::qingpan()
{
    for(int i = 0;i<8;i++)
    {
        for (int j = 0;j < 8;j++)
        {
            this->setCellWidget (i,j,NULL);
            a_s[i][j] = 0;
        }
    }
}

//统计棋子
int qipan::qizitongji()
{
    int i,j,H = 0,B = 0;
    for(i = 0;i<8;i++)
    {
        for (j = 0;j<8;j++)
        {
            if (a_s[i][j] == 1)
            {
                H++;
            }
            if (a_s[i][j] == 2)
            {
                B++;
            }
        }
    }
    B_q1 = B;
    return H;
}
int qipan::qizitongji_B()
{
    return B_q1;
}

void qipan::my_zhineng_g()
{
    int i,j,q_q[8][8] = {0};;
    for(i = 0;i<8;i++)
    {
        for(j = 0;j <8;j++)
        {
            if (a_s[i][j] == 0)
            {
                my_xiaqi(i,j,1,0);  //白棋
                q_q[i][j] = B_q;
                B_q = 0;
            }
        }
    }
    int max = q_q[0][0];
    int row = 0, column = 0;
    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            if(max < q_q[i][j])
            {
                max = q_q[i][j];
                row = i;
                column = j;
            }
        }
    }
    if (max !=0){
    my_xiaqi(row,column,1,1);}
}
//renren
int qipan::sheixianxia2(int a,int ai1)
{
    if (a != 2)
    {
        am = a;
    }
    Ai = ai1;
    return am;
}
