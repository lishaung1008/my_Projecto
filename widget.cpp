#include "widget.h"
#include "ui_widget.h"

#include<QDebug>
#include<QTimer>
#include<QMessageBox>

int a = 0,num = 160,ai = 0,t = 1;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->tableWidget->hide();

    connect(ui->button_start,&QPushButton::clicked,[=](){        
        kaishi();
        a = 0;num = 160;
        this->shaixianxia1_time_end(t*100);
        t++;
    });

    connect(ui->button_end,&QPushButton::clicked,[=](){
        ui->tableWidget->close();
        ui->label_aaaa->show();
        ui->button_ai->show();
        ui->button_renren->show();
    });

    connect(ui->button_B,&QPushButton::clicked,[=](){
        a = 1; num =160;
        kaishi();
        this->shaixianxia1_time_end(t*100);
        t++;
    });

    connect(ui->button_ai,&QPushButton::clicked,[=](){
        ai = 1;
        ui->label_aaaa->hide();
        ui->button_ai->hide();
        ui->button_renren->hide();
        ui->tableWidget->show();
    });
    connect(ui->button_renren,&QPushButton::clicked,[=](){
        ai = 0;
        ui->label_aaaa->hide();
        ui->button_ai->hide();
        ui->button_renren->hide();
        ui->tableWidget->show();
    });
}

void Widget::shaixianxia1_time_end(int T)
{
    QTimer *time = new QTimer(this);
    time->start(T);
    connect(time, &QTimer::timeout, [=](){

        //打印棋子和计时时间
        int tongji = ui->tableWidget->qizitongji();
        int tongji1 = ui->tableWidget->qizitongji_B();
        ui->lineEdit_h->setText(QString::number(tongji));
        ui->lineEdit_b->setText(QString::number(tongji1));
        ui->lineEdit->setText(QString::number(num/10));
        int a1 = ui->tableWidget->sheixianxia2(2,ai);

        //判断输赢
        if(tongji+tongji1==64 || tongji1 == 0 ||tongji == 0)
        {
            if (tongji1 > tongji||tongji == 0) {QMessageBox::information(this, "正确", "白棋胜");}
            else if(tongji > tongji1||tongji1 == 0){QMessageBox::information(this, "正确", "黑棋胜");}
            time->stop();
        }

        if (a != a1)
        {
            num = 160;a = a1;
        }
        if(a == 0)
        {
            ui->lineEdit_2->setText("黑棋下");
        }
        else ui->lineEdit_2->setText("白棋下");
        if(num == 0)
        {
            if (a == 0)
            {
                a = 1;
                ui->tableWidget->sheixianxia2(a,ai);
            }
            else if (a == 1)
            {
                a = 0;
                ui->tableWidget->sheixianxia2(a,ai);
            }
            num = 160;
        }

//人机
        if (ai == 1 && a == 1 && num == 155)
        {
            ui->tableWidget->my_zhineng_g();
            a = 0;
            ui->tableWidget->sheixianxia2(a,ai);
            num = 160;
        }
        num--;
    });
}

void Widget::kaishi()
{
    ui->tableWidget->qingpan();

    ui->tableWidget->show();
    ui->tableWidget->my_white(3,3);
    ui->tableWidget->my_white(4,4);
    ui->tableWidget->my_black(4,3);
    ui->tableWidget->my_black(3,4);
    ui->tableWidget->sheixianxia2(a,ai);
}

Widget::~Widget()
{
    delete ui;
}
