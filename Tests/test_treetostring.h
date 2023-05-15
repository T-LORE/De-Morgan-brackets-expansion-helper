#ifndef TEST_TREETOSTRING_H
#define TEST_TREETOSTRING_H


#include "qobject.h"
#include "qtmetamacros.h"

#include "../DeMorganBracketsExpansion/demorganbracketsexpansion.h"

class test_treeToString: public QObject
{
   Q_OBJECT
   public:
       void compareErrors(QList<error> expectedErrors, QList<error> errors);

   private slots:
    void initTestCase();
    void emptyTree();
    void oneNodeVar();
    void oneNodeOper();
    void twoNodesVarOper();
    void threeNodesVarVarOper();
    void fourNodesVarVarVarOperOper();
    void emptyVariable();
    void complexTest1();
    void complexTest2();
    void cleanupTestCase();
};

#endif // TEST_TREETOSTRING_H
