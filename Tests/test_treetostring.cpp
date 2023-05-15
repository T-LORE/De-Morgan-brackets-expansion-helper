#include "test_treetostring.h"
#include <QtTest>
#include "../DeMorganBracketsExpansion/demorganbracketsexpansion.h"

void test_treeToString::compareErrors(QList<error> expectedErrors, QList<error> actualErrors)
{
    QCOMPARE(expectedErrors.size(), actualErrors.size());
    for (int i = 0; i < expectedErrors.size(); i++)
    {
        QCOMPARE(expectedErrors[i].error, actualErrors[i].error);
        QCOMPARE(expectedErrors[i].position, actualErrors[i].position);
        QCOMPARE(expectedErrors[i].symbol, actualErrors[i].symbol);
    }
}

void test_treeToString::initTestCase()
{

}

void test_treeToString::emptyTree()
{
    node *tree = 0;
    QString str = "data To Delete";
    QString expectedStr = "";
    
    treeToString(tree, str);
    
    QCOMPARE(str, expectedStr);
}

void test_treeToString::oneNodeVar()
{
    node *tree = new node;
    tree->type = VARIABLE;
    tree->data = "A";
    tree->left = 0;
    tree->right = 0;

    QString str = "data To Delete";
    QString expectedStr = "A";
    
    treeToString(tree, str);
    
    QCOMPARE(str, expectedStr);


}

void test_treeToString::oneNodeOper()
{
    node *tree = new node;
    tree->type = NOT;
    tree->left = 0;
    tree->right = 0;

    QString str = "data To Delete";
    QString expectedStr = "!";
    
    treeToString(tree, str);
    
    QCOMPARE(str, expectedStr);

}

void test_treeToString::twoNodesVarOper()
{
    // A !
    node *tree = new node;
    tree->type = NOT;
    tree->left = new node;
    tree->left->type = VARIABLE;
    tree->left->data = "A";

    tree->right = 0;

    QString str = "data To Delete";
    QString expectedStr = "A !";
    
    treeToString(tree, str);

    QCOMPARE(str, expectedStr);


}

void test_treeToString::threeNodesVarVarOper()
{
    // B A +
    node *tree = new node;
    tree->type = OR;
    tree->left = new node;
    tree->left->type = VARIABLE;
    tree->left->data = "B";

    tree->right = new node;
    tree->right->type = VARIABLE;
    tree->right->data = "A";

    QString str = "data To Delete";
    QString expectedStr = "B A +";

    treeToString(tree, str);

    QCOMPARE(str, expectedStr);

}

void test_treeToString::fourNodesVarVarVarOperOper()
{
    // A B * C *
    node *tree = new node;
    tree->type = AND;
    tree->left = new node;
    tree->left->type = VARIABLE;
    tree->left->data = "C";

    tree->right = new node;
    tree->right->type = AND;
    tree->right->left = new node;
    tree->right->left->type = VARIABLE;
    tree->right->left->data = "B";

    tree->right->right = new node;
    tree->right->right->type = VARIABLE;
    tree->right->right->data = "A";

    QString str = "data To Delete";
    QString expectedStr = "A B * C *";

    treeToString(tree, str);

    QCOMPARE(str, expectedStr);

}

void test_treeToString::emptyVariable()
{
    node *tree = new node;
    tree->type = AND;
    tree->left = new node;
    tree->left->type = VARIABLE;
    tree->left->data = "";

    tree->right = new node;
    tree->right->type = VARIABLE;
    tree->right->data = "A";

    QString str = "data To Delete";

    QList<error> expectedErrors;
    error expectedError{
        INCORRECT_VARIABLE,
        1,
        1
    };
    expectedErrors.append(expectedError);

    try {
        treeToString(tree, str);
    } catch (QList<error> errors) {
        compareErrors(expectedErrors, errors);
    }

}

void test_treeToString::complexTest1()
{ 
    //A B + C * D -
    node *tree = new node;
    tree->type = XOR;

    tree->left = new node;
    tree->left->type = VARIABLE;
    tree->left->data = "D";

    tree->right = new node;
    tree->right->type = AND;

    tree->right->left = new node;
    tree->right->left->type = VARIABLE;
    tree->right->left->data = "C";
    
    tree->right->right = new node;
    tree->right->right->type = OR;

    tree->right->right->left = new node;
    tree->right->right->left->type = VARIABLE;
    tree->right->right->left->data = "B";

    tree->right->right->right = new node;
    tree->right->right->right->type = VARIABLE;
    tree->right->right->right->data = "A";

    QString str = "data To Delete";
    QString expectedStr = "A B + C * D -";

    treeToString(tree, str);
    

}

void test_treeToString::complexTest2()
{
    // A B + C * D - E + !
    node *tree = new node;
    tree->type = NOT;

    tree->left = new node;
    tree->left->type = OR;

    tree->left->left = new node;
    tree->left->left->type = VARIABLE;
    tree->left->left->data = "E";

    tree->left->right = new node;
    tree->left->right->type = XOR;

    tree->left->right->left = new node;
    tree->left->right->left->type = VARIABLE;
    tree->left->right->left->data = "D";

    tree->left->right->right = new node;
    tree->left->right->right->type = AND;

    tree->left->right->right->left = new node;
    tree->left->right->right->left->type = VARIABLE;
    tree->left->right->right->left->data = "C";

    tree->left->right->right->right = new node;
    tree->left->right->right->right->type = OR;

    tree->left->right->right->right->left = new node;
    tree->left->right->right->right->left->type = VARIABLE;
    tree->left->right->right->right->left->data = "B";

    tree->left->right->right->right->right = new node;
    tree->left->right->right->right->right->type = VARIABLE;
    tree->left->right->right->right->right->data = "A";

    QString str = "data To Delete";
    QString expectedStr = "A B + C * D - E + !";

    treeToString(tree, str);

}

void test_treeToString::cleanupTestCase()
{

}
