#include "test_treetostring.h"
#include <QtTest>

void test_treeToString::compareErrors(QList<error> expectedErrors, QList<error> actualErrors)
{
    QCOMPARE(expectedErrors.size(), actualErrors.size());
    for (int i = 0; i < expectedErrors.size(); i++)
    {
        QCOMPARE(expectedErrors[i].error, actualErrors[i].error);
        QCOMPARE(expectedErrors[i].position, actualErrors[i].position);
        QCOMPARE(expectedErrors[i].data, actualErrors[i].data);
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
    tree->childrens[0] = 0;
    tree->childrens[1] = 0;

    QString str = "data To Delete";
    QString expectedStr = "A";
    
    treeToString(tree, str);
    
    QCOMPARE(str, expectedStr);


}

void test_treeToString::oneNodeOper()
{
    node *tree = new node;
    tree->type = NOT;
    tree->childrens[0] = 0;
    tree->childrens[1] = 0;

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
    tree->childrens.append(new node);
    tree->childrens[0]->type = VARIABLE;
    tree->childrens[0]->data = "A";

    tree->childrens[1] = 0;

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
    tree->childrens.append(new node);
    tree->childrens[0]->type = VARIABLE;
    tree->childrens[0]->data = "B";

    tree->childrens.append(new node);
    tree->childrens[1]->type = VARIABLE;
    tree->childrens[1]->data = "A";

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
    tree->childrens.append(new node);
    tree->childrens[0]->type = VARIABLE;
    tree->childrens[0]->data = "C";

    tree->childrens.append(new node);
    tree->childrens[1]->type = AND;
    tree->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->type = VARIABLE;
    tree->childrens[1]->childrens[0]->data = "B";

    tree->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->type = VARIABLE;
    tree->childrens[1]->childrens[1]->data = "A";

    QString str = "data To Delete";
    QString expectedStr = "A B * C *";

    treeToString(tree, str);

    QCOMPARE(str, expectedStr);

}

void test_treeToString::emptyVariable()
{
    node *tree = new node;
    tree->type = AND;
    tree->childrens.append(new node);
    tree->childrens[0]->type = VARIABLE;
    tree->childrens[0]->data = "";

    tree->childrens.append(new node);
    tree->childrens[1]->type = VARIABLE;
    tree->childrens[1]->data = "A";

    QString str = "data To Delete";

    QList<error> expectedErrors;
    
    error expectedError{
        INCORRECT_VARIABLE,
        0,
        ""
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

    tree->childrens.append(new node);
    tree->childrens[0]->type = VARIABLE;
    tree->childrens[0]->data = "D";

    tree->childrens.append(new node);
    tree->childrens[1]->type = AND;

    tree->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[0]->type = VARIABLE;
    tree->childrens[1]->childrens[0]->data = "C";
    
    tree->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->type = OR;

    tree->childrens[1]->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->childrens[0]->type = VARIABLE;
    tree->childrens[1]->childrens[1]->childrens[0]->data = "B";

    tree->childrens[1]->childrens[1]->childrens.append(new node);
    tree->childrens[1]->childrens[1]->childrens[1]->type = VARIABLE;
    tree->childrens[1]->childrens[1]->childrens[1]->data = "A";

    QString str = "data To Delete";
    QString expectedStr = "A B + C * D -";

    treeToString(tree, str);
    

}

void test_treeToString::complexTest2()
{
    // A B + C * D - E + !
    node *tree = new node;
    tree->type = NOT;

    tree->childrens.append(new node);
    tree->childrens[0]->type = OR;

    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[0]->data = "E";

    tree->childrens[0]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->type = XOR;

    tree->childrens[0]->childrens[1]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[1]->childrens[0]->data = "D";

    tree->childrens[0]->childrens[1]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->childrens[1]->type = AND;

    tree->childrens[0]->childrens[1]->childrens[1]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->childrens[1]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[1]->childrens[1]->childrens[0]->data = "C";

    tree->childrens[0]->childrens[1]->childrens[1]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->childrens[1]->childrens[1]->type = OR;

    tree->childrens[0]->childrens[1]->childrens[1]->childrens[1]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->childrens[1]->childrens[1]->childrens[0]->type = VARIABLE;
    tree->childrens[0]->childrens[1]->childrens[1]->childrens[1]->childrens[0]->data = "B";

    tree->childrens[0]->childrens[1]->childrens[1]->childrens[1]->childrens.append(new node);
    tree->childrens[0]->childrens[1]->childrens[1]->childrens[1]->childrens[1]->type = VARIABLE;
    tree->childrens[0]->childrens[1]->childrens[1]->childrens[1]->childrens[1]->data = "A";

    QString str = "data To Delete";
    QString expectedStr = "A B + C * D - E + !";

    treeToString(tree, str);

}

void test_treeToString::cleanupTestCase()
{

}
