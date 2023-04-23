#ifndef TEST_TREETOSTRING_H
#define TEST_TREETOSTRING_H


#include "qobject.h"
#include "qtmetamacros.h"
class test_treeToString: public QObject
{
   Q_OBJECT
   public:
       explicit test_treeToString(QObject *parent = 0);

   private slots:
    void initTestCase();
    void emptyTree();
    void oneNodeVar();
    void oneNodeOper();
    void twoNodesVarOper();
    void threeNodesVarVarOper();
    void fourNodesVarVarVarOperOper();
    void invalidNode();
    void complexTest1();
    void complexTest2();
    void cleanupTestCase();
};

#endif // TEST_TREETOSTRING_H
