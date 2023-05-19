#include "test_deletedoublenegation.h"
#include <QtTest>



void test_deleteDoubleNegation::compareTrees(node *expectedTree, node *tree)
{
    if (expectedTree == NULL) {
        QVERIFY(tree == NULL);
        return;
    }
    if (tree == NULL){
        QVERIFY(tree != NULL);
        return;
    }
    QVERIFY(expectedTree->type == tree->type);
    QVERIFY(expectedTree->data == tree->data);

    compareTrees(expectedTree->childrens[0], tree->childrens[0]);
    compareTrees(expectedTree->childrens[1], tree->childrens[1]);


}

test_deleteDoubleNegation::test_deleteDoubleNegation(QObject *parent) : QObject(parent)
{
}

void test_deleteDoubleNegation::initTestCase()
{

}

void test_deleteDoubleNegation::noTransformations()
{
    node *tree = new node;
    tree->type = VARIABLE;
    tree->data = "A";

    node *expectedTree = new node;
    expectedTree->type = VARIABLE;
    expectedTree->data = "A";

    deleteDoubleNegation(tree);

    compareTrees(expectedTree, tree);

}

void test_deleteDoubleNegation::oneNegation()
{// A !

    node *tree = new node;
    tree->type = NOT;
    tree->childrens.append(new node);
    tree->childrens[0]->type = VARIABLE;
    tree->childrens[0]->data = "A";
    
    node *expectedTree = new node;
    expectedTree->type = NOT;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->data = "A";

    deleteDoubleNegation(tree);

    compareTrees(expectedTree, tree);

    

}

void test_deleteDoubleNegation::evenNumberOfNegations()
{
    node *tree = new node;
    tree->type = NOT;
    tree->childrens.append(new node);
    tree->childrens[0]->type = NOT;
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->data = "A";

    node *expectedTree = new node;
    expectedTree->type = VARIABLE;
    expectedTree->data = "A";

    deleteDoubleNegation(tree);

    compareTrees(expectedTree, tree);

}

void test_deleteDoubleNegation::oddNumberOfNegations()
{
    node *tree = new node;
    tree->type = NOT;
    tree->childrens.append(new node);
    tree->childrens[0]->type = NOT;
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = NOT;
    tree->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->childrens[0]->data = "A";

    node *expectedTree = new node;
    expectedTree->type = NOT;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->data = "A";

    deleteDoubleNegation(tree);

    compareTrees(expectedTree, tree);

}

void test_deleteDoubleNegation::doubleNegationInTheMiddle()
{
    //Выражение в обратной польской нотации A B ! ! + C D - + D -
    node *tree = new node;
    tree->type = XOR;

    tree->childrens.append(new node);
    tree->childrens[0]->type = VARIABLE;
    tree->childrens[0]->data = "D";
    tree->childrens.append(new node);
    tree->childrens[1]->type = OR;

    tree->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->type = XOR;
    tree->childrens[1]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[1]->childrens[0]->childrens[0]->data = "D";
    tree->childrens[1]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[1]->childrens[0]->childrens[1]->data = "C";

    tree->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->type = NOT;
    tree->childrens[1]->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->childrens[0]->type = NOT;
    
    tree->childrens[1]->childrens[1]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->type = OR;
    tree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[0]->data = "B";
    tree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[1]->data = "A";




    
        node *expectedTree = new node;
    expectedTree->type = XOR;

    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->data = "D";
    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = OR;

    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = XOR;
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->data = "D";
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[1]->data = "C";

    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->type = NOT;
    
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->type = OR;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[0]->data = "B";
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[1]->data = "A";

    deleteDoubleNegation(tree);

    compareTrees(expectedTree, tree);

}

void test_deleteDoubleNegation::doubleNegationInTheEnd()
{
    node *tree = new node;
    tree->type = XOR;

    tree->childrens.append(new node);
    tree->childrens[0]->type = VARIABLE;
    tree->childrens[0]->data = "D";
    tree->childrens.append(new node);
    tree->childrens[1]->type = OR;

    tree->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->type = XOR;
    tree->childrens[1]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[1]->childrens[0]->childrens[0]->data = "D";
    tree->childrens[1]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[1]->childrens[0]->childrens[1]->data = "C";

   
    
    tree->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->type = OR;
    tree->childrens[1]->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->childrens[0]->type = VARIABLE;
    tree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[0]->data = "B";

    tree->childrens[1]->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->childrens[1]->type = NOT;
    tree->childrens[1]->childrens[1]->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->childrens[1]->childrens[0]->type = NOT;
    tree->childrens[1]->childrens[1]->childrens[1]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->childrens[1]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[1]->childrens[1]->childrens[1]->childrens[0]->childrens[0]->data = "A";




    
    node *expectedTree = new node;
    expectedTree->type = XOR;

    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->data = "D";
    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = OR;

    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = XOR;
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->data = "D";
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[1]->data = "C";

    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->type = NOT;
    
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->type = OR;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[0]->data = "B";
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[1]->data = "A";

    deleteDoubleNegation(tree);

    compareTrees(expectedTree, tree);

}

void test_deleteDoubleNegation::fourTransformationsInDifferentPlaces()
{ // A ! ! B ! ! + C D - ! ! + D ! ! -
    node *tree = new node;
    tree->type = XOR;

    tree->childrens.append(new node);
    tree->childrens[0]->type = NOT;
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = NOT;
    tree->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->childrens[0]->data = "D";

    tree->childrens.append(new node);
    tree->childrens[1]->type = OR;

    tree->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->type = NOT;
    tree->childrens[1]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[0]->type = NOT;

    tree->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->type = XOR;
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->data = "D";
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens[1]->data = "C";

   
    
    tree->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->type = OR;
    tree->childrens[1]->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->childrens[0]->type = NOT;
    tree->childrens[1]->childrens[1]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->type = NOT;

    tree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->data = "B";

    tree->childrens[1]->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->childrens[1]->type = NOT;
    tree->childrens[1]->childrens[1]->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->childrens[1]->childrens[0]->type = NOT;
    tree->childrens[1]->childrens[1]->childrens[1]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->childrens[1]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[1]->childrens[1]->childrens[1]->childrens[0]->childrens[0]->data = "A";




    
    node *expectedTree = new node;
    expectedTree->type = XOR;

    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->data = "D";
    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = OR;

    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = XOR;
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->data = "D";
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[1]->data = "C";

    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->type = NOT;
    
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->type = OR;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[0]->data = "B";
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[1]->data = "A";

    deleteDoubleNegation(tree);

    compareTrees(expectedTree, tree);
}

void test_deleteDoubleNegation::twoTransformationsInARow()
{
    //A ! ! ! ! B +
    node *tree = new node;
    tree->type = OR;
    tree->childrens.append(new node);
    tree->childrens[0]->type = NOT;
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = NOT;
    tree->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->type = NOT;
    tree->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->type = NOT;
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->data = "A";

    tree->childrens.append(new node);
    tree->childrens[1]->type = VARIABLE;
    tree->childrens[1]->data = "B";

    node *expectedTree = new node;
    expectedTree->type = OR;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->data = "A";

    
    expectedTree->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->data = "B";

}

void test_deleteDoubleNegation::cleanupTestCase()
{

}
