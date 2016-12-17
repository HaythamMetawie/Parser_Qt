#include "scanner.h"
scanner *scanner::s_inst = 0;
scanner::scanner()
{
    qDebug()<< "scanner is created." << endl;
}

bool scanner::isSymbol(QChar c) { return (c == '+' || '-' || '*' || '/' || '=' || '<' || '(' || ')' || ';' || ':='); }

scanner *scanner::get_inst()
{
    if(s_inst == NULL) { s_inst = new scanner();}
    return s_inst;
}

void scanner::getToken(QString l)
{
    bool res_words = 0;
    int i = 0;
    while (state != DONE) {
        switch (state) {
        case START:
            if (l[i].isSpace()) {
                i++;
                if (i == l.length()) state = DONE;
                else state = START;
            }
            else if (l[i].isDigit()) {
                state = INNUM;
            }
            else if (l[i].isLetter()) {
                state = INID;
            }
            else if (l[i] == ':') {
                state = INASSIGN;
            }
            else if (l[i] == '{') {
                i++;
                state = INCOMMENT;
            }
            else if (isSymbol(l[i])) {
                if (l[i] == ';') {
                    tokens.push_back(";"); values.push_back("semicolon");
                }
                else
                {	QString foo (1,l[i]);
                    tokens.push_back(foo); values.push_back(foo);
                }

                i++;
                if (i == l.length()) state = DONE;
                else state = START;
            }
            else state = DONE;
            break;

        case INCOMMENT:
            if (state == INCOMMENT) {
                while (l[i] != '}') {
                    i++;
                }
                i++;
                if (i == l.length()) state = DONE;
                else state = START;
            }
            break;

        case INNUM:
            while (l[i].isDigit()) {
                mytoken += l[i];
                i++;
            }
            tokens.push_back(mytoken);
            values.push_back("number");
            mytoken = "";
            if (i == l.length()) state = DONE;
            else state = START;
            break;

        case INID:
            while (l[i].isLetter()) {
                mytoken += l[i];
                i++;
            }
            for (int i = 0; i < 8; i++)
            {
                if (RES_WORDS[i] == mytoken) res_words = 1;
            }
            if (res_words){
                tokens.push_back(mytoken);
                values.push_back(mytoken);
            }
            else{
                tokens.push_back(mytoken);
                values.push_back("identifier");
            }
            mytoken = "";
            res_words = 0;
            if (i == l.length()) state = DONE;
            else state = START;
            break;

        case INASSIGN:
            if (l[i] == ':') {
                i += 2;
                tokens.push_back(":=");
                values.push_back("assign");
                state = START;
            }
            else {
                if (i == l.length()) state = DONE;
                else state = START;
            }
            break;
        case DONE:
            break;
        }
    }
}
