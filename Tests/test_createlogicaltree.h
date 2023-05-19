#ifndef TEST_CREATELOGICALTREE_H
#define TEST_CREATELOGICALTREE_H


#include "qobject.h"
#include "qtmetamacros.h"

#include "../DeMorganBracketsExpansion/demorganbracketsexpansion.h"

class test_createLogicalTree : public QObject
{
   Q_OBJECT
   public:
       explicit test_createLogicalTree(QObject *parent = 0);

   public slots:
    void compareErrors(QList<error> expectedErrors, QList<error> actualErrors);
    void compareTrees(node *expectedTree, node *tree);

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
