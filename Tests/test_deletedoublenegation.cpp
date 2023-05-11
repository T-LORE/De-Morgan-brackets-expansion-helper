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

    compareTrees(expectedTree->left, tree->left);
    compareTrees(expectedTree->right, tree->right);


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
    tree->left = new node;
    tree->left->type = VARIABLE;
    tree->left->data = "A";
    
    node *expectedTree = new node;
    expectedTree->type = NOT;
    expectedTree->left = new node;
    expectedTree->left->type = VARIABLE;
    expectedTree->left->data = "A";

    deleteDoubleNegation(tree);

    compareTrees(expectedTree, tree);

    

}

void test_deleteDoubleNegation::evenNumberOfNegations()
{
    node *tree = new node;
    tree->type = NOT;
    tree->left = new node;
    tree->left->type = NOT;
    tree->left->left = new node;
    tree->left->left->type = VARIABLE;
    tree->left->left->data = "A";

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
    tree->left = new node;
    tree->left->type = NOT;
    tree->left->left = new node;
    tree->left->left->type = NOT;
    tree->left->left->left = new node;
    tree->left->left->left->type = VARIABLE;
    tree->left->left->left->data = "A";

    node *expectedTree = new node;
    expectedTree->type = NOT;
    expectedTree->left = new node;
    expectedTree->left->type = VARIABLE;
    expectedTree->left->data = "A";

    deleteDoubleNegation(tree);

    compareTrees(expectedTree, tree);

}

void test_deleteDoubleNegation::doubleNegationInTheMiddle()
{
    //Выражение в обратной польской нотации A B ! ! + C D - + D -
    node *tree = new node;
    tree->type = XOR;

    tree->left = new node;
    tree->left->type = VARIABLE;
    tree->left->data = "D";
    tree->right = new node;
    tree->right->type = OR;

    tree->right->left = new node;
    tree->right->left->type = XOR;
    tree->right->left->left = new node;
    tree->right->left->left->type = VARIABLE;
    tree->right->left->left->data = "D";
    tree->right->left->right = new node;
    tree->right->left->right->type = VARIABLE;
    tree->right->left->right->data = "C";

    tree->right->right = new node;
    tree->right->right->type = NOT;
    tree->right->right->left = new node;
    tree->right->right->left->type = NOT;
    
    tree->right->right->left->left = new node;
    tree->right->right->left->left->type = OR;
    tree->right->right->left->left->left = new node;
    tree->right->right->left->left->left->type = VARIABLE;
    tree->right->right->left->left->left->data = "B";
    tree->right->right->left->left->right = new node;
    tree->right->right->left->left->right->type = VARIABLE;
    tree->right->right->left->left->right->data = "A";




    
        node *expectedTree = new node;
    expectedTree->type = XOR;

    expectedTree->left = new node;
    expectedTree->left->type = VARIABLE;
    expectedTree->left->data = "D";
    expectedTree->right = new node;
    expectedTree->right->type = OR;

    expectedTree->right->left = new node;
    expectedTree->right->left->type = XOR;
    expectedTree->right->left->left = new node;
    expectedTree->right->left->left->type = VARIABLE;
    expectedTree->right->left->left->data = "D";
    expectedTree->right->left->right = new node;
    expectedTree->right->left->right->type = VARIABLE;
    expectedTree->right->left->right->data = "C";

    expectedTree->right->right = new node;
    expectedTree->right->right->type = NOT;
    expectedTree->right->right->left = new node;
    expectedTree->right->right->left->type = NOT;
    
    expectedTree->right->right->left->left = new node;
    expectedTree->right->right->left->left->type = OR;
    expectedTree->right->right->left->left->left = new node;
    expectedTree->right->right->left->left->left->type = VARIABLE;
    expectedTree->right->right->left->left->left->data = "B";
    expectedTree->right->right->left->left->right = new node;
    expectedTree->right->right->left->left->right->type = VARIABLE;
    expectedTree->right->right->left->left->right->data = "A";

    deleteDoubleNegation(tree);

    compareTrees(expectedTree, tree);

}

void test_deleteDoubleNegation::doubleNegationInTheEnd()
{
    node *tree = new node;
    tree->type = XOR;

    tree->left = new node;
    tree->left->type = VARIABLE;
    tree->left->data = "D";
    tree->right = new node;
    tree->right->type = OR;

    tree->right->left = new node;
    tree->right->left->type = XOR;
    tree->right->left->left = new node;
    tree->right->left->left->type = VARIABLE;
    tree->right->left->left->data = "D";
    tree->right->left->right = new node;
    tree->right->left->right->type = VARIABLE;
    tree->right->left->right->data = "C";

   
    
    tree->right->right = new node;
    tree->right->right->type = OR;
    tree->right->right->left = new node;
    tree->right->right->left->type = VARIABLE;
    tree->right->right->left->left->left->data = "B";

    tree->right->right->right = new node;
    tree->right->right->right->type = NOT;
    tree->right->right->right->left = new node;
    tree->right->right->right->left->type = NOT;
    tree->right->right->right->left->left = new node;
    tree->right->right->right->left->left->type = VARIABLE;
    tree->right->right->right->left->left->data = "A";




    
    node *expectedTree = new node;
    expectedTree->type = XOR;

    expectedTree->left = new node;
    expectedTree->left->type = VARIABLE;
    expectedTree->left->data = "D";
    expectedTree->right = new node;
    expectedTree->right->type = OR;

    expectedTree->right->left = new node;
    expectedTree->right->left->type = XOR;
    expectedTree->right->left->left = new node;
    expectedTree->right->left->left->type = VARIABLE;
    expectedTree->right->left->left->data = "D";
    expectedTree->right->left->right = new node;
    expectedTree->right->left->right->type = VARIABLE;
    expectedTree->right->left->right->data = "C";

    expectedTree->right->right = new node;
    expectedTree->right->right->type = NOT;
    expectedTree->right->right->left = new node;
    expectedTree->right->right->left->type = NOT;
    
    expectedTree->right->right->left->left = new node;
    expectedTree->right->right->left->left->type = OR;
    expectedTree->right->right->left->left->left = new node;
    expectedTree->right->right->left->left->left->type = VARIABLE;
    expectedTree->right->right->left->left->left->data = "B";
    expectedTree->right->right->left->left->right = new node;
    expectedTree->right->right->left->left->right->type = VARIABLE;
    expectedTree->right->right->left->left->right->data = "A";

    deleteDoubleNegation(tree);

    compareTrees(expectedTree, tree);

}

void test_deleteDoubleNegation::fourTransformationsInDifferentPlaces()
{ // A ! ! B ! ! + C D - ! ! + D ! ! -
    node *tree = new node;
    tree->type = XOR;

    tree->left = new node;
    tree->left->type = NOT;
    tree->left->left = new node;
    tree->left->left->type = NOT;
    tree->left->left->left = new node;
    tree->left->left->left->type = VARIABLE;
    tree->left->left->left->data = "D";

    tree->right = new node;
    tree->right->type = OR;

    tree->right->left = new node;
    tree->right->left->type = NOT;
    tree->right->left->left = new node;
    tree->right->left->left->type = NOT;

    tree->right->left->left->left = new node;
    tree->right->left->left->left->type = XOR;
    tree->right->left->left->left->left = new node;
    tree->right->left->left->left->left->type = VARIABLE;
    tree->right->left->left->left->left->data = "D";
    tree->right->left->left->left->right = new node;
    tree->right->left->left->left->right->type = VARIABLE;
    tree->right->left->left->left->right->data = "C";

   
    
    tree->right->right = new node;
    tree->right->right->type = OR;
    tree->right->right->left = new node;
    tree->right->right->left->type = NOT;
    tree->right->right->left->left = new node;
    tree->right->right->left->left->type = NOT;

    tree->right->right->left->left->left = new node;
    tree->right->right->left->left->left->type = VARIABLE;
    tree->right->right->left->left->left->left->left->data = "B";

    tree->right->right->right = new node;
    tree->right->right->right->type = NOT;
    tree->right->right->right->left = new node;
    tree->right->right->right->left->type = NOT;
    tree->right->right->right->left->left = new node;
    tree->right->right->right->left->left->type = VARIABLE;
    tree->right->right->right->left->left->data = "A";




    
    node *expectedTree = new node;
    expectedTree->type = XOR;

    expectedTree->left = new node;
    expectedTree->left->type = VARIABLE;
    expectedTree->left->data = "D";
    expectedTree->right = new node;
    expectedTree->right->type = OR;

    expectedTree->right->left = new node;
    expectedTree->right->left->type = XOR;
    expectedTree->right->left->left = new node;
    expectedTree->right->left->left->type = VARIABLE;
    expectedTree->right->left->left->data = "D";
    expectedTree->right->left->right = new node;
    expectedTree->right->left->right->type = VARIABLE;
    expectedTree->right->left->right->data = "C";

    expectedTree->right->right = new node;
    expectedTree->right->right->type = NOT;
    expectedTree->right->right->left = new node;
    expectedTree->right->right->left->type = NOT;
    
    expectedTree->right->right->left->left = new node;
    expectedTree->right->right->left->left->type = OR;
    expectedTree->right->right->left->left->left = new node;
    expectedTree->right->right->left->left->left->type = VARIABLE;
    expectedTree->right->right->left->left->left->data = "B";
    expectedTree->right->right->left->left->right = new node;
    expectedTree->right->right->left->left->right->type = VARIABLE;
    expectedTree->right->right->left->left->right->data = "A";

    deleteDoubleNegation(tree);

    compareTrees(expectedTree, tree);
}

void test_deleteDoubleNegation::twoTransformationsInARow()
{
    //A ! ! ! ! B +
    node *tree = new node;
    tree->type = OR;
    tree->left = new node;
    tree->left->type = NOT;
    tree->left->left = new node;
    tree->left->left->type = NOT;
    tree->left->left->left = new node;
    tree->left->left->left->type = NOT;
    tree->left->left->left->left = new node;
    tree->left->left->left->left->type = NOT;
    tree->left->left->left->left->left = new node;
    tree->left->left->left->left->left->type = VARIABLE;
    tree->left->left->left->left->left->data = "A";

    tree->right = new node;
    tree->right->type = VARIABLE;
    tree->right->data = "B";

    node *expectedTree = new node;
    expectedTree->type = OR;
    expectedTree->left = new node;
    expectedTree->left->type = VARIABLE;
    expectedTree->left->data = "A";

    
    expectedTree->right->type = VARIABLE;
    expectedTree->right->data = "B";

}

void test_deleteDoubleNegation::cleanupTestCase()
{

}
