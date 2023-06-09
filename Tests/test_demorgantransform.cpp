#include "test_demorgantransform.h"
#include <QtTest>


void test_deMorganTransform::compareNodes(const node *expectedNode, const node *actualNode) {
    QCOMPARE(expectedNode->data, actualNode->data);
    QCOMPARE(expectedNode->type, actualNode->type);

    if (expectedNode->childrens.size() != actualNode->childrens.size()) {
        QCOMPARE(expectedNode->childrens.size(), actualNode->childrens.size());
        return;
    }

    for (int i = 0; i < expectedNode->childrens.size(); ++i) {
        compareNodes(expectedNode->childrens.at(i), actualNode->childrens.at(i));
    }
}

void test_deMorganTransform::compareTrees(node *expectedTree, node *actualTree) {
    if (expectedTree == nullptr && actualTree == nullptr)
        return;

    if (expectedTree == nullptr && actualTree != nullptr)
        QFAIL("expectedTree - null, actualTree не null");
    if (expectedTree != nullptr && actualTree == nullptr)
        QFAIL("expectedTree не null, but actualTree - null");


    compareNodes(expectedTree, actualTree);
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
    tree->childrens.append(new node);
    tree->childrens[0]->type = AND;
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->data = "A";
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[1]->data = "B";

    node *expectedTree = new node;
    expectedTree->type = OR;
    
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->data = "A";
    
    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->data = "B";

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);
}

void test_deMorganTransform::disjunctionOfTwoVariables()
{// B A + !
    node *tree = new node;
    tree->type = NOT;
    tree->childrens.append(new node);
    tree->childrens[0]->type = OR;
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->data = "A";
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[1]->data = "B";

    node *expectedTree = new node;
    expectedTree->type = AND;
    
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->data = "A";
    
    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->data = "B";

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);
}

void test_deMorganTransform::conjunctionOfThreeVariables()
{// C B * A * !
    node *tree = new node;
    tree->type = NOT;

    tree->childrens.append(new node);
    tree->childrens[0]->type = AND;
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = AND;
    tree->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->childrens[0]->data = "C";
    tree->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->childrens[1]->data = "B";

    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[1]->data = "A";

    node *expectedTree = new node;
    expectedTree->type = OR;
    
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = OR;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->childrens[0]->data = "C";
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->type = NOT;
    expectedTree->childrens[0]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[1]->childrens[0]->data = "B";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->data = "A";


    deMorganTransform(tree);
    compareTrees(expectedTree, tree);

}

void test_deMorganTransform::disjunctionOfThreeVariables()
{
    node *tree = new node;
    tree->type = NOT;
    tree->childrens.append(new node);
    tree->childrens[0]->type = OR;
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = OR;
    tree->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->childrens[0]->data = "C";
    tree->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->childrens[1]->data = "B";
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[1]->data = "A";

    node *expectedTree = new node;
    expectedTree->type = AND;
    

    
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = AND;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->childrens[0]->data = "C";
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->type = NOT;
    expectedTree->childrens[0]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[1]->childrens[0]->data = "B";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->data = "A";

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);

}

void test_deMorganTransform::transformationInTheMiddleOfTheExpression()
{// A ! B C - + ! D *
    node *tree = new node;
    tree->type = AND;
    tree->childrens.append(new node);
    tree->childrens[0]->type = VARIABLE;
    tree->childrens[0]->data = "D";
    tree->childrens.append(new node);
    tree->childrens[1]->type = NOT;
    tree->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->type = OR;
    tree->childrens[1]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[0]->type = XOR;
    tree->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->data = "C";
    tree->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[1]->data = "B";
    tree->childrens[1]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[1]->type = NOT;
    tree->childrens[1]->childrens[0]->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[1]->childrens[0]->type = VARIABLE;
    tree->childrens[1]->childrens[0]->childrens[1]->childrens[0]->data = "A";

    node *expectedTree = new node;
    expectedTree->type = AND;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->data = "D";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = AND;

    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->type = XOR;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->data = "C";
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[1]->data = "B";

    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->type = NOT;

    expectedTree->childrens[1]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->type = NOT;

    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->data = "A";

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);


}

void test_deMorganTransform::transformationAtTheEndOfTheExpression()
{   // A ! B C + ! + D *
    node *tree = new node;
    tree->type = AND;
    tree->childrens.append(new node);
    tree->childrens[0]->type = VARIABLE;
    tree->childrens[0]->data = "D";
    
    tree->childrens.append(new node);
    tree->childrens[1]->type = OR;

    tree->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->type = NOT;


    tree->childrens[1]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[0]->type = OR;
    tree->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->data = "C";
    tree->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[1]->data = "B";

    tree->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->type = NOT;
    tree->childrens[1]->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->childrens[0]->type = VARIABLE;
    tree->childrens[1]->childrens[1]->childrens[0]->data = "A";

    node *expectedTree = new node;
    expectedTree->type = AND;

    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->data = "D";
    
    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = OR;

    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = AND;

    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->data = "C";

    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens[0]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[1]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[1]->childrens[0]->data = "B";


    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->data = "A";

    

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);

}

void test_deMorganTransform::moreBracketsAfterFirstTransformation()
{//!(!(A + B) * !(D * U)) ->  !((!A * !B) * (!D + !U)) -> !(!A * !B) + !(!D + !U) -> (!!A + !!B) + (!!D * !!U)
//A B + ! D U * ! * !
    node *tree = new node;
    tree->type = NOT;
    tree->childrens.append(new node);
    tree->childrens[0]->type = AND;
    
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = NOT;
    tree->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->type = OR;

    tree->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->data = "B";

    tree->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[1]->data = "A";

    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->type = NOT;
    tree->childrens[0]->childrens[1]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->childrens[0]->type = AND;

    tree->childrens[0]->childrens[1]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[1]->childrens[0]->childrens[0]->data = "D";

    tree->childrens[0]->childrens[1]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[1]->childrens[0]->childrens[1]->data = "U";

    node *expectedTree = new node;
    expectedTree->type = OR;

    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = OR;

    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->data = "B";

    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->type = NOT;
    expectedTree->childrens[0]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[1]->childrens[0]->childrens[0]->data = "A";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = AND;

    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->data = "D";

    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->data = "U";
}

void test_deMorganTransform::threeTransformationsInARow()
{
    //A B + ! ! !
    node *tree = new node;
    tree->type = NOT;
    tree->childrens.append(new node);
    tree->childrens[0]->type = NOT;
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = NOT;
    tree->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->type = OR;
    tree->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->data = "B";
    tree->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[1]->data = "A";

}

void test_deMorganTransform::emptyTree()
{
    node *tree = new node;
    tree->type = NULL_ELEMENT;

    node *expectedTree = new node;
    expectedTree->type = NULL_ELEMENT;

    deMorganTransform(tree);
    compareTrees(tree, expectedTree);
    
}

void test_deMorganTransform::noTransformationsRequired()
{ // D C - B A + *
    node *tree = new node;
    tree->type = AND;
    tree->childrens.append(new node);
    tree->childrens[0]->type = OR;
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->data = "A";
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[1]->data = "B";
    tree->childrens.append(new node);
    tree->childrens[1]->type = XOR;
    tree->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->type = VARIABLE;
    tree->childrens[1]->childrens[0]->data = "C";
    tree->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->type = VARIABLE;
    tree->childrens[1]->childrens[1]->data = "D";

    node *expectedTree = new node;
    expectedTree->type = AND;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = OR;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->data = "A";
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[1]->data = "B";
    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = XOR;
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->data = "C";
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[1]->data = "D";

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);

}

void test_deMorganTransform::nand()
{ // A B *!
    node *tree = new node;
    tree->type = NAND;

    tree->childrens.append(new node);
    tree->childrens[0]->type = VARIABLE;
    tree->childrens[0]->data = "A";
    tree->childrens.append(new node);
    tree->childrens[1]->type = VARIABLE;
    tree->childrens[1]->data = "B";

    node *expectedTree = new node;
    expectedTree->type = OR;

    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->data = "A";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->data = "B";

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);
}

void test_deMorganTransform::nor()
{ // A B +!
    node *tree = new node;
    tree->type = NOR;

    tree->childrens.append(new node);
    tree->childrens[0]->type = VARIABLE;
    tree->childrens[0]->data = "A";
    tree->childrens.append(new node);
    tree->childrens[1]->type = VARIABLE;
    tree->childrens[1]->data = "B";

    node *expectedTree = new node;
    expectedTree->type = AND;

    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->data = "A";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->data = "B";

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);
}

void test_deMorganTransform::negatiatedNand()
{ // A B *! !
    node *tree = new node;
    tree->type = NOT;
    tree->childrens.append(new node);
    tree->childrens[0]->type = NAND;
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->data = "A";
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[1]->data = "B";
    
    node *expectedTree = new node;
    expectedTree->type = AND;

    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->childrens[0]->data = "A";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->data = "B";

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);
}

void test_deMorganTransform::negatiatedNor()
{// A B +! !
    node *tree = new node;
    tree->type = NOT;
    tree->childrens.append(new node);
    tree->childrens[0]->type = NOR;
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->data = "A";
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[1]->data = "B";
    
    node *expectedTree = new node;
    expectedTree->type = OR;

    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->childrens[0]->data = "A";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->data = "B";

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);

}

void test_deMorganTransform::negatiatedNandAndNor()
{
    // C D *! A B +! * !
    //node *tree = createLogicalTree("C A B *! +! !");
    node *tree = new node;
    tree->type = NOT;
    tree->childrens.append(new node);
    tree->childrens[0]->type = NOR;
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->data = "C";

    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->type = NAND;
    tree->childrens[0]->childrens[1]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[1]->childrens[0]->data = "A";
    tree->childrens[0]->childrens[1]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[1]->childrens[1]->data = "B";

    //node *expectedTree = createLogicalTree("C ! ! A ! ! ! B ! ! ! + +");
    node *expectedTree = new node;
    expectedTree->type = OR;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->childrens[0]->data = "C";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = OR;
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->data = "A";

    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[0]->data = "B";

    

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);
}

void test_deMorganTransform::doubleNegatiatedNand()
{
    // A B *! ! !
    //node *tree = createLogicalTree("A B *! !");
    node * tree = new node;
    tree->type = NOT;
    tree->childrens.append(new node);
    tree->childrens[0]->type = NAND;
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->data = "B";

    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[1]->data = "A";

    //node *expectedTree = createLogicalTree("A ! ! B ! ! *");
    node *expectedTree = new node;
    expectedTree->type = AND;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->childrens[0]->data = "B";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->data = "A";

    deMorganTransform(tree);
    compareTrees(expectedTree, tree);
}

void test_deMorganTransform::doubleNegatiatedNor()
{
    // A B +! ! !
    //node *tree = createLogicalTree("A B +! !");
    node * tree = new node;
    tree->type = NOT;
    tree->childrens.append(new node);
    tree->childrens[0]->type = NOR;
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->data = "B";

    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[1]->data = "A";

    //node *expectedTree = createLogicalTree("A ! ! B ! ! +");
    node *expectedTree = new node;
    expectedTree->type = OR;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->childrens[0]->data = "B";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->data = "A";
    deMorganTransform(tree);
    compareTrees(expectedTree, tree);
}

void test_deMorganTransform::doubleNegatiatedNandAndNor()
{
    // C D *! A B +! * ! !
    node *tree = new node;
    tree->type = NOT;
    tree->childrens.append(new node);
    tree->childrens[0]->type = NOT;
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = NOR;
    tree->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->childrens[0]->data = "C";
    tree->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[1]->type = NAND;
    tree->childrens[0]->childrens[0]->childrens[1]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[1]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->childrens[1]->childrens[0]->data = "A";
    tree->childrens[0]->childrens[0]->childrens[1]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[1]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->childrens[1]->childrens[1]->data = "B";

    //node *expectedTree = createLogicalTree("C ! ! ! A ! ! ! ! B ! ! ! ! * *");
    node *expectedTree = new node;
    expectedTree->type = AND;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->data = "C";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = AND;
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->data = "A";

    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->data = "B";
    
    deMorganTransform(tree);
    compareTrees(expectedTree, tree);
}

void test_deMorganTransform::complexTest1()
{
    //V F + U * ! C * J Q + ! ! ! *
    node *tree = new node;
    tree->type = AND;

    tree->childrens.append(new node);
    tree->childrens[0]->type = AND;
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = NOT;
    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[1]->data = "C";

    tree->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->type = NOT;
    tree->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->type = AND;
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->data = "U";
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->childrens[1]->type = OR;
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->childrens[1]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->childrens[1]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->childrens[1]->childrens[0]->data = "V";
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->childrens[1]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->childrens[1]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->childrens[1]->childrens[1]->data = "F";

    tree->childrens.append(new node);
    tree->childrens[1]->type = NOT;
    tree->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->type = NOT;
    tree->childrens[1]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[0]->type = NOT;
    tree->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->type = OR;
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens[0]->data = "J";
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens[1]->type = VARIABLE;
    tree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->childrens[1]->data = "Q";


}

void test_deMorganTransform::cleanupTestCase()
{

}
