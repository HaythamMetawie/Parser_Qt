#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "node.h"
#include "parser.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
    double x = 25 ;
    double y = 25 ;
//    resizeEvent(QResizeEvent *event);
private:
    Ui::Form *ui;
    draw( treeNode * node);
    QGraphicsScene * canvas;
};

#endif // FORM_H
