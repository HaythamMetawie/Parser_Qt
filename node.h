#ifndef NODE_H
#define NODE_H
#include <QString>
#include<QVector>

class treeNode{
private:
    treeNode *r, *m, *l;
    QString value;
    int type;

public:

    QVector<treeNode *> n;
    treeNode(QString v = "");
    ~treeNode();
    void set_value(QString v);
    void set_right(treeNode *right);
    void set_mid(treeNode *mid);
    void set_left(treeNode *left);
    //void set_next(treeNode *next);
    void set_type (int t);
    QString get_value();
    treeNode *get_right();
    treeNode *get_mid();
    treeNode *get_left();
    //treeNode *get_next();
    int get_type();
};
#endif // NODE_H
