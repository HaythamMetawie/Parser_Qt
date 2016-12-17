#ifndef SCANNER_H
#define SCANNER_H
#include <QDebug>
#include <QString>
#include <QVector>
#include <Qchar>

class scanner {
private:

        QString RES_WORDS[8] = { "if","then","else","end","repeat","until","read","write" };
        enum states { START, INCOMMENT, INNUM, INID, INASSIGN, DONE };
        QString mytoken;
        scanner();
        static scanner *s_inst;

public:
        bool isSymbol(QChar c);

        QVector <QString> tokens;
        QVector <QString> values;
        static scanner* get_inst();

        states state = START; //initial state

        void getToken(QString l);

};


#endif // SCANNER_H
