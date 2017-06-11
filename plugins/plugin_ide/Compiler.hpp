/* 
 * File:   Compiler.hpp
 * Author: Koncord <koncord at rwa.su>
 *
 * Created on 20 Февраль 2015 г., 18:40
 */

#ifndef COMPILER_HPP
#define	COMPILER_HPP

#include <QStringList>
#include <QVector>

struct _label
{
    QString name;
    int sourceLine;
    int pos;
};
typedef _label Label;
typedef QVector<Label> Labels;
typedef QVector <uint8_t> Code;

class Compiler
{

private:
    Labels labels;
    QStringList source;
public:

    Compiler(QStringList *src);
    Code exec();
};

#endif	/* COMPILER_HPP */

