#include "node.h"

treeNode::treeNode(QString v)
{
    r = nullptr;
    m = nullptr;
    l = nullptr;
    //n.clear();
    value = v;
    type = 1;
}

void treeNode::set_value(QString v)
{
    value =v;
}

void treeNode::set_right(treeNode *right)
{
    r = right;
}

void treeNode::set_mid(treeNode *mid)
{
    m = mid;
}

void treeNode::set_left(treeNode *left)
{
    l = left;
}

/*void treeNode::set_next(treeNode *next)
{
    n.push_back(next);
}*/

void treeNode::set_type(int t)
{
    type = t;
}

QString treeNode::get_value()
{
    return value;
}

treeNode *treeNode::get_right()
{
    return r;
}

treeNode *treeNode::get_mid()
{
    return m;
}

treeNode *treeNode::get_left()
{
    return l;
}

/*treeNode *treeNode::get_next()
{
    //treeNode * beg = new treeNode();
    //beg = n[0];
    //n.pop_front();
    return NULL;
}*/

int treeNode::get_type()
{
    return type;
}


