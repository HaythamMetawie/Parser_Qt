#include "parser.h"

parser *parser::p_inst = 0;
parser::parser()
{
    i = 0;
    sr = scanner::get_inst();
    qDebug() << "parser is created." << endl << "Wait until creating syntax tree!";
}

void parser::match(QString s)
{
    if (s == sr->values.at(i) && i != sr->values.size()) i++;
    if (i == sr->values.size()) i = 0;

}

treeNode *parser::stmt_seq()
{
    treeNode *seq_Node = new treeNode() ;
    seq_Node =stmt() ;
    while (sr->tokens.at(i) == ";")
    {
        match("semicolon");
        //seq_Node->set_next(stmt());
       // next_seq.push_back(seq_Node->get_next(stmt())); //set next node
        seq_Node->n.push_back(stmt());
    }
    return seq_Node;
}

treeNode *parser::stmt()
{
    treeNode *stmtNode = new treeNode();
    if (sr->values.at(i) == "if")
    {
        stmtNode = if_stmt();
        stmtNode->set_type(0);
    }
    else if  (sr->values.at(i) == "repeat")
    {
        stmtNode = repeat_stmt();
        stmtNode->set_type(0);
    }
    else if (sr->values.at(i) == "write")
    {
        stmtNode = write_stmt();
        stmtNode->set_type(0);
    }
    else if (sr->values.at(i) == "read")
    {
        stmtNode = read_stmt();
        stmtNode->set_type(0);
    }
    else if (sr->values.at(i) == "identifier")
    {
        stmtNode = assign_stmt();
        stmtNode->set_type(0);
    }
    return stmtNode;
}

treeNode *parser::if_stmt()
{
    match("if");
    treeNode *ifNode = new treeNode("if");
    ifNode->set_left(exp());
    match("then");
    ifNode->set_mid(stmt_seq());
    if (sr->values.at(i) == "else")
    {
        match("else");
        ifNode->set_right(stmt_seq());
    }
    match("end");
    return ifNode;
}

treeNode *parser::repeat_stmt()
{
    match("repeat");
    treeNode *repeatNode = new treeNode("repeat");
    repeatNode->set_left(stmt_seq());
    match("until");
    repeatNode->set_right(exp());
    return repeatNode;
}

treeNode *parser::assign_stmt()
{
    match("identifier");
    match("assign");
    treeNode *assignNode = new treeNode("assign (" + sr->tokens.at(i-2) + ")");
    assignNode->set_mid(exp());
    return assignNode;
}

treeNode *parser::read_stmt()
{
    treeNode *readNode = new treeNode();
    match("read");
    match("identifier");
    readNode->set_value("read (" + sr->tokens.at(i-1) + ")");
    return readNode;
}

treeNode *parser::write_stmt()
{
    match("write");
    treeNode *writeNode = new treeNode("write");
    writeNode->set_mid(exp());
    return writeNode;
}

treeNode *parser::exp()
{
    treeNode *expNode = new treeNode();
    expNode = simple_exp();
    while (sr->tokens.at(i) == "<" || sr->tokens.at(i) == "=")
    {
        match(sr->values.at(i));
        treeNode *temp = expNode;
        expNode = new treeNode("op (" + sr-> tokens.at(i-1) + ")");
        expNode->set_left(temp);
        expNode->set_right(simple_exp());
    }
    return expNode;
}

treeNode *parser::simple_exp()
{
    treeNode *sExpNode = new treeNode();
    sExpNode = term();
    while (sr->tokens.at(i) == "+" || sr->tokens.at(i) == "-")
    {
        match(sr->values.at(i));
        treeNode *temp = sExpNode;
        sExpNode= new treeNode("op ("+ sr->tokens.at(i-1) + ")");
        sExpNode->set_left(temp);
        sExpNode->set_right(term());
    }
    return sExpNode;
}

treeNode *parser::term()
{
    treeNode *termNode = new treeNode();
    termNode = factor();
    while (sr->tokens.at(i) == "*" || sr->tokens.at(i) == "/")
    {
        match(sr->values.at(i));
        treeNode *temp = termNode;
        termNode = new treeNode("op ("+ sr->tokens.at(i-1) + ")");
        termNode->set_left(temp);
        termNode->set_right(factor());
    }
    return termNode;
}

treeNode *parser::factor()
{
    treeNode *factorNode = new treeNode();
    if(sr->tokens.at(i) == "(")
    {
        match("(");
        treeNode *left = new treeNode("(");
        factorNode->set_left(left);
        factorNode->set_mid(exp());
        match(")");
        treeNode *right = new treeNode(")");
        factorNode->set_right(right);
    }
    else if (sr->values.at(i) == "number")
    {
        match("number");
        factorNode->set_value("const (" + sr->tokens.at(i-1) + ")");
    }
    else if (sr->values.at(i) == "identifier")
    {
        match("identifier");
        factorNode->set_value("id (" + sr->tokens.at(i-1) + ")");
    }
    return factorNode;
}

parser *parser::get_inst()
{
    if(p_inst == NULL) { p_inst = new parser();}
    return p_inst;
}

void parser::program(QString s)
{
    sr->getToken(s);
    root = stmt_seq();
}

treeNode *parser::getRoot()
{
    return root;

}
