#ifndef TEST_CREATELOGICALTREE_H
#define TEST_CREATELOGICALTREE_H


#include "qobject.h"
#include "qtmetamacros.h"

class test_createLogicalTree : public QObject
{
   Q_OBJECT
   public:
       explicit test_createLogicalTree(QObject *parent = 0);

   private slots:
    void initTestCase();
    void emptyLine();
    void oneSymbolOperator();
    void oneSymbolOperand();
    void manySymbols();
    void onlyVariables();
    void onlyOperators();
    void errorAtTheBeginning();
    void errorAtTheEnd();
    void differentErrors();
    void negation();
    void disjunction();
    void conjunction();
    void exclusiveOr();
    void nand();
    void nor();
    void complexTest1();
    void complexTest2();
    void complexTest3();
    void cleanupTestCase();
};

#endif // TEST_CREATELOGICALTREE_H
