#ifndef TEST_DELETEDOUBLENEGATION_H
#define TEST_DELETEDOUBLENEGATION_H


#include "qobject.h"
#include "qtmetamacros.h"
#include "../DeMorganBracketsExpansion/demorganbracketsexpansion.h"

class test_deleteDoubleNegation: public QObject
{
   Q_OBJECT
   public:
       explicit test_deleteDoubleNegation(QObject *parent = 0);

public slots:
    void compareNodes(const node *expectedNode, const node *actualNode);
    void compareTrees(node *expectedTree, node *tree);

private slots:
    void initTestCase();
    void noTransformations();
    void oneNegation();
    void evenNumberOfNegations();
    void oddNumberOfNegations();
    void doubleNegationInTheMiddle();
    void doubleNegationInTheEnd();
    void fourTransformationsInDifferentPlaces();
    void twoTransformationsInARow();
    void cleanupTestCase();
};

#endif // TEST_DELETEDOUBLENEGATION_H
