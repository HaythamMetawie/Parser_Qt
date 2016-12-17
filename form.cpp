#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    canvas = new QGraphicsScene();
    ui->graphicsView->setSceneRect(0,0,2000,2000);
    ui->graphicsView->setScene(canvas);
    ui->graphicsView->show();
    parser * pr = parser::get_inst();
    treeNode * root = pr->getRoot();
    draw(root);
}
//Form::resizeEvent(QResizeEvent *event)
//{
//    setWidth(event->size().width());
//    setHeight(event->size().height());

//    fitInView(QRectF(0,0,width(),height()),Qt::KeepAspectRatioByExpanding);
//    arrangeNodes();

//    canvas->setSceneRect(0,0,width(),height());
//    this->setSceneRect(0,0,width(),height());

//    update();
//}

Form::~Form()
{
    delete ui;
}

Form::draw(treeNode *node)
{
    bool l = false, m = false, r = false;
    int level = 0;
    qDebug() << node->get_value();
    if(node->get_type() == 0)
    {
        canvas->addRect(x, y, 100, 50);
        QGraphicsTextItem *text = canvas->addText(node->get_value());
        text->setPos(x+25, y+10);

    }
    else
    {
        canvas->addEllipse(x, y, 100, 50);
        QGraphicsTextItem *text = canvas->addText(node->get_value());
        text->setPos(x+25, y+10);

    }

    if(node->get_left() != nullptr)
    {
        double x1 = x + 50;
        double x2 = x - 125;
        double y1 = y + 50;
        double y2 = y1 + 30;
        canvas->addLine(x1,y1,x2,y2);
        double tempx = x;
        double tempy = y;
        x-=175;
        y=y2;
        draw(node->get_left());
        l = true;
        x = tempx;
        y= tempy;
    }
    if(node->get_mid() != nullptr)
    {
        if (l = false)
        {
            double x1 = x + 50;
            double x2 = x1;//+225;
            double y1 = y + 50;
            double y2 = y1 + 30;
            canvas->addLine(x1,y1,x2,y2);
            double tempx = x;
            double tempy = y;
            y=y2;
            draw( node->get_mid());
            m = true;
            x = tempx;
            y= tempy;
        }
        if (l = true)
        {
            x = x + 70;
            double x1 = x;
            double x2 = x1 + 25;//+225;
            double y1 = y + 50;
            double y2 = y1 + 30;
            canvas->addLine(x1,y1,x2,y2);
            //x+=175;
            double tempx = x;
            double tempy = y;
            y=y2;
            draw(node->get_mid());
            m = true;
            x = tempx;
            y= tempy;
        }

    }
    if(node->get_right() != nullptr)
    {
        double x1 = x + 50;
        double x2 = x + 225 ;
        double y1 = y + 50;
        double y2 = y1 + 30;
        canvas->addLine(x1,y1,x2,y2);
        double tempx = x;
        double tempy = y;
        x += 175 ;
        y=y2;
        draw( node->get_right());
        x = tempx;
        y= tempy;
    }

    if(!node->n.empty())
    {

            for(QVector<treeNode*>::iterator it = node->n.begin();it!=node->n.end();++it)
            {
                    double x1 = x + 100;
                    double x2 = x1 + 350;
                    double y1 = y + 25 ;
                    double y2 = y1;
                    canvas->addLine(x1,y1,x2,y2);
                    x=x2;
                    draw( *it);
            }

    }

}
