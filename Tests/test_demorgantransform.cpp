#include "test_demorgantransform.h"
#include <QtTest>


void test_deMorganTransform::compareTrees(node *expectedTree, node *tree)
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

test_deMorganTransform::test_deMorganTransform(QObject *parent) : QObject(parent)
{
}

void test_deMorganTransform::initTestCase()
{

}

void test_deMorganTransform::conjunctionOfTwoVariables()
{ // B A * !
    node *tree = new node;
    tree->type = NOT;
    tree->left = new node;
    tree->left->type = AND;
    tree->left->left = new node;
    tree->left->left->type = VARIABLE;
    tree->left->left->data = "A";
    tree->left->right = new node;
    tree->left->right->type = VARIABLE;
    tree->left->right->data = "B";

    node *expectedTree = new node;
    expectedTree->type = OR;
    
    expectedTree->left = new node;
    expectedTree->left->type = NOT;
    expectedTree->left->left = new node;
    expectedTree->left->left->type = VARIABLE;
    expectedTree->left->left->data = "A";
    
    expectedTree->right = new node;
    expectedTree->right->type = NOT;
    expectedTree->right->left = new node;
    expectedTree->right->left->type = VARIABLE;
    expectedTree->right->left->data = "B";

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);
}

void test_deMorganTransform::disjunctionOfTwoVariables()
{// B A + !
    node *tree = new node;
    tree->type = NOT;
    tree->left = new node;
    tree->left->type = OR;
    tree->left->left = new node;
    tree->left->left->type = VARIABLE;
    tree->left->left->data = "A";
    tree->left->right = new node;
    tree->left->right->type = VARIABLE;
    tree->left->right->data = "B";

    node *expectedTree = new node;
    expectedTree->type = AND;
    
    expectedTree->left = new node;
    expectedTree->left->type = NOT;
    expectedTree->left->left = new node;
    expectedTree->left->left->type = VARIABLE;
    expectedTree->left->left->data = "A";
    
    expectedTree->right = new node;
    expectedTree->right->type = NOT;
    expectedTree->right->left = new node;
    expectedTree->right->left->type = VARIABLE;
    expectedTree->right->left->data = "B";

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);
}

void test_deMorganTransform::conjunctionOfThreeVariables()
{// C B * A * !
    node *tree = new node;
    tree->type = NOT;
    tree->left = new node;
    tree->left->type = AND;
    tree->left->left = new node;
    tree->left->left->type = AND;
    tree->left->left->left = new node;
    tree->left->left->left->type = VARIABLE;
    tree->left->left->left->data = "C";
    tree->left->left->right = new node;
    tree->left->left->right->type = VARIABLE;
    tree->left->left->right->data = "B";
    tree->left->right = new node;
    tree->left->right->type = VARIABLE;
    tree->left->right->data = "A";

    node *expectedTree = new node;
    expectedTree->type = OR;
    
    expectedTree->right = new node;
    expectedTree->right->type = NOT;
    expectedTree->right->left = new node;
    expectedTree->right->left->type = VARIABLE;
    expectedTree->right->left->data = "A";
    
    expectedTree->left = new node;
    expectedTree->left->type = OR;
    expectedTree->left->left = new node;
    expectedTree->left->left->type = NOT;
    expectedTree->left->left->left = new node;
    expectedTree->left->left->left->type = VARIABLE;
    expectedTree->left->left->left->data = "C";
    expectedTree->left->right = new node;
    expectedTree->left->right->type = NOT;
    expectedTree->left->right->left = new node;
    expectedTree->left->right->left->type = VARIABLE;
    expectedTree->left->right->left->data = "B";

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);

}

void test_deMorganTransform::disjunctionOfThreeVariables()
{
    node *tree = new node;
    tree->type = NOT;
    tree->left = new node;
    tree->left->type = OR;
    tree->left->left = new node;
    tree->left->left->type = OR;
    tree->left->left->left = new node;
    tree->left->left->left->type = VARIABLE;
    tree->left->left->left->data = "C";
    tree->left->left->right = new node;
    tree->left->left->right->type = VARIABLE;
    tree->left->left->right->data = "B";
    tree->left->right = new node;
    tree->left->right->type = VARIABLE;
    tree->left->right->data = "A";

    node *expectedTree = new node;
    expectedTree->type = AND;
    
    expectedTree->right = new node;
    expectedTree->right->type = NOT;
    expectedTree->right->left = new node;
    expectedTree->right->left->type = VARIABLE;
    expectedTree->right->left->data = "A";
    
    expectedTree->left = new node;
    expectedTree->left->type = AND;
    expectedTree->left->left = new node;
    expectedTree->left->left->type = NOT;
    expectedTree->left->left->left = new node;
    expectedTree->left->left->left->type = VARIABLE;
    expectedTree->left->left->left->data = "C";
    expectedTree->left->right = new node;
    expectedTree->left->right->type = NOT;
    expectedTree->left->right->left = new node;
    expectedTree->left->right->left->type = VARIABLE;
    expectedTree->left->right->left->data = "B";

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);

}

void test_deMorganTransform::transformationInTheMiddleOfTheExpression()
{// A ! B C - + ! D *
    node *tree = new node;
    tree->type = AND;
    tree->left = new node;
    tree->left->type = VARIABLE;
    tree->left->data = "D";
    tree->right = new node;
    tree->right->type = NOT;
    tree->right->left = new node;
    tree->right->left->type = OR;
    tree->right->left->left = new node;
    tree->right->left->left->type = XOR;
    tree->right->left->left->left = new node;
    tree->right->left->left->left->type = VARIABLE;
    tree->right->left->left->left->data = "C";
    tree->right->left->left->right = new node;
    tree->right->left->left->right->type = VARIABLE;
    tree->right->left->left->right->data = "B";
    tree->right->left->right = new node;
    tree->right->left->right->type = NOT;
    tree->right->left->right->left = new node;
    tree->right->left->right->left->type = VARIABLE;
    tree->right->left->right->left->data = "A";

    node *expectedTree = new node;
    expectedTree->type = AND;
    expectedTree->left = new node;
    expectedTree->left->type = VARIABLE;
    expectedTree->left->data = "D";

    expectedTree->right = new node;
    expectedTree->right->type = AND;
    expectedTree->right->left = new node;
    expectedTree->right->left->type = NOT;
    expectedTree->right->left->left = new node;
    expectedTree->right->left->left->type = XOR;
    expectedTree->right->left->left->left = new node;
    expectedTree->right->left->left->left->type = VARIABLE;
    expectedTree->right->left->left->left->data = "C";
    expectedTree->right->left->left->right = new node;
    expectedTree->right->left->left->right->type = VARIABLE;
    expectedTree->right->left->left->right->data = "B";
    expectedTree->right->left->right = new node;
    expectedTree->right->left->right->type = NOT;
    expectedTree->right->left->right->left = new node;
    expectedTree->right->left->right->left->type = VARIABLE;
    expectedTree->right->left->right->left->data = "A";

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);


}

void test_deMorganTransform::transformationAtTheEndOfTheExpression()
{   // A ! B C * ! + D *
    node *tree = new node;
    tree->type = AND;
    tree->left = new node;
    tree->left->type = VARIABLE;
    tree->left->data = "D";
    
    tree->right = new node;
    tree->right->type = OR;

    tree->right->left = new node;
    tree->right->left->type = NOT;


    tree->right->left->left = new node;
    tree->right->left->left->type = OR;
    tree->right->left->left->left = new node;
    tree->right->left->left->left->type = VARIABLE;
    tree->right->left->left->left->data = "C";
    tree->right->left->left->right = new node;
    tree->right->left->left->right->type = VARIABLE;
    tree->right->left->left->right->data = "B";

    tree->right->right = new node;
    tree->right->right->type = NOT;
    tree->right->right->left = new node;
    tree->right->right->left->type = VARIABLE;
    tree->right->right->left->data = "A";

    node *expectedTree = new node;
    expectedTree->type = AND;
    expectedTree->left = new node;
    expectedTree->left->type = VARIABLE;
    expectedTree->left->data = "D";
    
    expectedTree->right = new node;
    expectedTree->right->type = OR;

    expectedTree->right->left = new node;
    expectedTree->right->left->type = OR;

    expectedTree->right->left->left = new node;
    expectedTree->right->left->left->type = NOT;
    expectedTree->right->left->left->left = new node;
    expectedTree->right->left->left->left->type = VARIABLE;
    expectedTree->right->left->left->left->data = "C";
    expectedTree->right->left->right = new node;
    expectedTree->right->left->right->type = NOT;

    expectedTree->right->left->left->right = new node;
    expectedTree->right->left->left->right->type = VARIABLE;
    expectedTree->right->left->left->right->data = "B";
    
    expectedTree->right->right = new node;
    expectedTree->right->right->type = NOT;
    expectedTree->right->right->left = new node;
    expectedTree->right->right->left->type = VARIABLE;
    expectedTree->right->right->left->data = "A";

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);

}

void test_deMorganTransform::moreBracketsAfterFirstTransformation()
{//!(!(A + B) * !(D * U))
    node *tree = new node;
    tree->type = NOT;
    tree->left = new node;
    tree->left->type = AND;
    
    tree->left->left = new node;
    tree->left->left->type = NOT;
    tree->left->left->left = new node;
    tree->left->left->left->type = OR;
    tree->left->left->left->left = new node;
    tree->left->left->left->left->type = VARIABLE;
    tree->left->left->left->left->data = "B";
    tree->left->left->left->right = new node;
    tree->left->left->left->right->type = VARIABLE;
    tree->left->left->left->right->data = "A";

    tree->left->right = new node;
    tree->left->right->type = NOT;
    
    tree->left->right->left = new node;
    tree->left->right->left->type = AND;
    tree->left->right->left->left = new node;
    tree->left->right->left->left->type = VARIABLE;
    tree->left->right->left->left->data = "D";
    tree->left->right->left->right = new node;
    tree->left->right->left->right->type = VARIABLE;
    tree->left->right->left->right->data = "U";

    node *expectedTree = new node;
    expectedTree->type = AND;


    
    expectedTree->left = new node;
    expectedTree->left->type = OR;

    expectedTree->left->left = new node;
    expectedTree->left->left->type = NOT;

    expectedTree->left->left->left = new node;
    expectedTree->left->left->left->type = NOT;
    expectedTree->left->left->left->left = new node;
    expectedTree->left->left->left->left->type = VARIABLE;
    expectedTree->left->left->left->left->data = "B";

    expectedTree->left->right = new node;
    expectedTree->left->right->type = NOT;
    expectedTree->left->right->left = new node;
    expectedTree->left->right->left->type = NOT;
    
    expectedTree->left->right->left->right = new node;
    expectedTree->left->right->left->right->type = VARIABLE;
    expectedTree->left->right->left->right->data = "A";

    expectedTree->right = new node;
    expectedTree->right->type = AND;

    expectedTree->right->left = new node;
    expectedTree->right->left->type = NOT;
    expectedTree->right->left->left = new node;
    expectedTree->right->left->left->type = NOT;
    
    expectedTree->right->left->left->left = new node;
    expectedTree->right->left->left->left->type = VARIABLE;
    expectedTree->right->left->left->left->data = "D";

    expectedTree->right->right = new node;
    expectedTree->right->right->type = NOT;
    expectedTree->right->right->left = new node;
    expectedTree->right->right->left->type = NOT;
    
    expectedTree->right->right->left->left = new node;
    expectedTree->right->right->left->left->type = VARIABLE;
    expectedTree->right->right->left->left->data = "U";
}

void test_deMorganTransform::threeTransformationsInARow()
{
    //A B + ! ! !
    node *tree = new node;
    tree->type = NOT;
    tree->left = new node;
    tree->left->type = NOT;
    tree->left->left = new node;
    tree->left->left->type = NOT;
    tree->left->left->left = new node;
    tree->left->left->left->type = OR;
    tree->left->left->left->left = new node;
    tree->left->left->left->left->type = VARIABLE;
    tree->left->left->left->left->data = "B";
    tree->left->left->left->right = new node;
    tree->left->left->left->right->type = VARIABLE;
    tree->left->left->left->right->data = "A";

}

void test_deMorganTransform::emptyTree()
{
    node *tree = new node;
    tree->type = NULL_ELEMENT;

    try {
        deMorganTransform(tree);
        QVERIFY(false);
    } catch (error &e) {
        QVERIFY(e.error = EMPTY_TREE);
    }
    
}

void test_deMorganTransform::noTransformationsRequired()
{ // D C - B A + *
    node *tree = new node;
    tree->type = AND;
    tree->left = new node;
    tree->left->type = OR;
    tree->left->left = new node;
    tree->left->left->type = VARIABLE;
    tree->left->left->data = "A";
    tree->left->right = new node;
    tree->left->right->type = VARIABLE;
    tree->left->right->data = "B";
    tree->right = new node;
    tree->right->type = XOR;
    tree->right->left = new node;
    tree->right->left->type = VARIABLE;
    tree->right->left->data = "C";
    tree->right->right = new node;
    tree->right->right->type = VARIABLE;
    tree->right->right->data = "D";

    node *expectedTree = new node;
    expectedTree->type = AND;
    expectedTree->left = new node;
    expectedTree->left->type = OR;
    expectedTree->left->left = new node;
    expectedTree->left->left->type = VARIABLE;
    expectedTree->left->left->data = "A";
    expectedTree->left->right = new node;
    expectedTree->left->right->type = VARIABLE;
    expectedTree->left->right->data = "B";
    expectedTree->right = new node;
    expectedTree->right->type = XOR;
    expectedTree->right->left = new node;
    expectedTree->right->left->type = VARIABLE;
    expectedTree->right->left->data = "C";
    expectedTree->right->right = new node;
    expectedTree->right->right->type = VARIABLE;
    expectedTree->right->right->data = "D";

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);

}

void test_deMorganTransform::complexTest1()
{
    //V F + U * ! C * J Q + ! ! ! *
    node *tree = new node;
    tree->type = AND;

    tree->left = new node;
    tree->left->type = AND;
    tree->left->left = new node;
    tree->left->left->type = NOT;
    tree->left->right = new node;
    tree->left->right->type = VARIABLE;
    tree->left->right->data = "C";

    tree->left->left->left = new node;
    tree->left->left->left->type = NOT;
    tree->left->left->left->left = new node;
    tree->left->left->left->left->type = AND;
    tree->left->left->left->left->left = new node;
    tree->left->left->left->left->left->type = VARIABLE;
    tree->left->left->left->left->left->data = "U";
    tree->left->left->left->left->right = new node;
    tree->left->left->left->left->right->type = OR;
    tree->left->left->left->left->right->left = new node;
    tree->left->left->left->left->right->left->type = VARIABLE;
    tree->left->left->left->left->right->left->data = "V";
    tree->left->left->left->left->right->right = new node;
    tree->left->left->left->left->right->right->type = VARIABLE;
    tree->left->left->left->left->right->right->data = "F";

    tree->right = new node;
    tree->right->type = NOT;
    tree->right->left = new node;
    tree->right->left->type = NOT;
    tree->right->left->left = new node;
    tree->right->left->left->type = NOT;
    tree->right->left->left->left = new node;
    tree->right->left->left->left->type = OR;
    tree->right->left->left->left->left = new node;
    tree->right->left->left->left->left->type = VARIABLE;
    tree->right->left->left->left->left->data = "J";
    tree->right->left->left->left->right = new node;
    tree->right->left->left->left->right->type = VARIABLE;
    tree->right->left->left->left->right->data = "Q";


}

void test_deMorganTransform::complexTest2()
{

}

void test_deMorganTransform::cleanupTestCase()
{

}
