#ifndef PARSER_H
#define PARSER_H
#include <node.h>
#include <QString>
#include "scanner.h"

class parser{
private:
        treeNode *root;
        parser();
        static parser *p_inst;
        scanner *sr;
        int i;

        void match (QString s);


        treeNode *stmt_seq();


        treeNode *stmt();

        treeNode *if_stmt();

        treeNode *repeat_stmt();

        treeNode *assign_stmt();

        treeNode *read_stmt();

        treeNode *write_stmt();

        treeNode *exp();

        treeNode *simple_exp();

        treeNode *term();

        treeNode *factor();


public:

        static parser* get_inst();

        void program(QString s);
        treeNode * getRoot();
};


#endif // PARSER_H
