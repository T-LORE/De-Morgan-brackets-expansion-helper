#ifndef TEST_DEMORGANTRANSFORM_H
#define TEST_DEMORGANTRANSFORM_H


#include "qobject.h"
#include "qtmetamacros.h"
#include "../DeMorganBracketsExpansion/demorganbracketsexpansion.h"

class test_deMorganTransform: public QObject
{
   Q_OBJECT
   public:
       explicit test_deMorganTransform(QObject *parent = 0);

   public slots:
    void compareNodes(const node *expectedNode, const node *actualNode);
    void compareTrees(node *expectedTree, node *tree);
   
   private slots:
    void initTestCase();
    void conjunctionOfTwoVariables();
    void disjunctionOfTwoVariables();
    void conjunctionOfThreeVariables();
    void disjunctionOfThreeVariables();
    void transformationInTheMiddleOfTheExpression();
    void transformationAtTheEndOfTheExpression();
    void moreBracketsAfterFirstTransformation();
    void threeTransformationsInARow();
    void emptyTree();
    void noTransformationsRequired();
    void nand();
    void nor();
    void negatiatedNand();
    void negatiatedNor();
    void negatiatedNandAndNor();
    void doubleNegatiatedNand();
    void doubleNegatiatedNor();
    void doubleNegatiatedNandAndNor();
    void complexTest1();
    void cleanupTestCase();

};

#endif // TEST_DEMORGANTRANSFORM_H
