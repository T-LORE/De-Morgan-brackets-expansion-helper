#include "test_createlogicaltree.h"
#include "qtestcase.h"
#include <QtTest>
#include <QList>
#include <QMap>
#include <QString>

test_createLogicalTree::test_createLogicalTree(QObject *parent) : QObject(parent)
{
}

void test_createLogicalTree::compareErrors(QList<error> expectedErrors, QList<error> actualErrors)
{
    QCOMPARE(expectedErrors.size(), actualErrors.size());
    for (int i = 0; i < expectedErrors.size(); i++)
    {
        QCOMPARE(expectedErrors[i].type, actualErrors[i].type);
        QCOMPARE(expectedErrors[i].position, actualErrors[i].position);
        QCOMPARE(expectedErrors[i].data, actualErrors[i].data);
    }
}

void test_createLogicalTree::compareTrees(node *expectedTree, node *tree)
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

void test_createLogicalTree::initTestCase()
{

}

void test_createLogicalTree::emptyLine()
{
    QString str = "";
    node *root = createLogicalTree(str);
    QVERIFY(root == NULL);
}

void test_createLogicalTree::oneSymbolOperator()
{
    QString str = "!";
    node *root = NULL;
    bool isThrowErrors = false;
    QList<error> expectedErrorsQList;
    error e = {
        NOT_ENOUGH_ARGUMENTS,
        0,
        "!"
    };
    expectedErrorsQList.append(e);
    

    try {
        root = createLogicalTree(str);
    } catch (QList<error> e) {
        compareErrors(expectedErrorsQList, e);
        isThrowErrors = true;
    }
    QVERIFY(root == NULL);
    QVERIFY(isThrowErrors == true);
}

void test_createLogicalTree::oneSymbolOperand()
{
    QString str = "A";
    node *root = NULL;
    bool isThrowErrors = false;
    QList<error> expectedErrorsQList;
    error e = {
        NOT_ENOUGH_OPERATORS,
        0,
        "A"
    };
    expectedErrorsQList.append(e);

    try {
        root = createLogicalTree(str);
    } catch (QList<error> e) {
        compareErrors(expectedErrorsQList, e);
        isThrowErrors = true;
    }
    QVERIFY(root == NULL);
    QVERIFY(isThrowErrors == true);
}

void test_createLogicalTree::manySymbols()
{
    QString str = "A B + !";

    node *expectedTree = new node;
    expectedTree->type = NOT;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = OR;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->data = "A";
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[1]->data = "B";
    expectedTree->childrens[1] = NULL;

    node *root = NULL;


    root = createLogicalTree(str);

    compareTrees(expectedTree, root);


}

void test_createLogicalTree::onlyVariables()
{
    QString str = "A B C";
    node *root = NULL;
    bool isThrowErrors = false;
    QList<error> expectedErrorsQList;
    error e = {
        NOT_ENOUGH_OPERATORS,
        0,
        "A"
    };
    expectedErrorsQList.append(e);
    error e1 = {
        NOT_ENOUGH_OPERATORS,
        2,
        "C"
    };
    expectedErrorsQList.append(e1);

    try {
        root = createLogicalTree(str);
    } catch (QList<error> e) {
        compareErrors(expectedErrorsQList, e);
        isThrowErrors = true;
    }
    QVERIFY(root == NULL);
    QVERIFY(isThrowErrors == true);


}

void test_createLogicalTree::onlyOperators()
{
    QString str = "+ !";
    node *root = NULL;
    bool isThrowErrors = false;
    QList<error> expectedErrorsQList;
    error e = {
        NOT_ENOUGH_ARGUMENTS,
        0,
        "+"
    };
    expectedErrorsQList.append(e);
    error e1 = {
        NOT_ENOUGH_ARGUMENTS,
        2,
        "!"
    };
    expectedErrorsQList.append(e1);

    try {
        root = createLogicalTree(str);
    } catch (QList<error> e) {
        compareErrors(expectedErrorsQList, e);
        isThrowErrors = true;
    }
    QVERIFY(root == NULL);
    QVERIFY(isThrowErrors == true);


}

void test_createLogicalTree::errorAtTheBeginning()
{
    QString str = "/ A B + !";
    node *root = NULL;
    bool isThrowErrors = false;
    QList<error> expectedErrorsQList;
    error e = {
        UNKNOWN_SYMBOL,
        0,
        "/"
    };
    expectedErrorsQList.append(e);

    try {
        root = createLogicalTree(str);
    } catch (QList<error> e) {
        compareErrors(expectedErrorsQList, e);
        isThrowErrors = true;
    }
    QVERIFY(root == NULL);
    QVERIFY(isThrowErrors == true);


}

void test_createLogicalTree::errorAtTheEnd()
{
    QString str = "A B + ! /";
    node *root = NULL;
    bool isThrowErrors = false;
    QList<error> expectedErrorsQList;
    error e = {
        UNKNOWN_SYMBOL,
        8,
        "/"
    };
    expectedErrorsQList.append(e);

    try {
        root = createLogicalTree(str);
    } catch (QList<error> e) {
        compareErrors(expectedErrorsQList, e);
        isThrowErrors = true;
    }
    QVERIFY(root == NULL);
    QVERIFY(isThrowErrors == true);

}

void test_createLogicalTree::differentErrors()
{
    QString str = "A +< B + ! / С";
    node *root = NULL;
    bool isThrowErrors = false;
    QList<error> expectedErrorsQList;
    error e = {
        NOT_ENOUGH_ARGUMENTS,
        2,
        "+"
    };
    expectedErrorsQList.append(e);
    error e1 = {
        UNKNOWN_SYMBOL,
        3,
        "<"
    };
    expectedErrorsQList.append(e);

    error e2 = {
        UNKNOWN_SYMBOL,
        11,
        "/"
    };
    expectedErrorsQList.append(e2);
    error e3 = {
        NOT_ENOUGH_OPERATORS,
        13,
        "C"
    };
    expectedErrorsQList.append(e3);

    try {
        root = createLogicalTree(str);
    } catch (QList<error> e) {
        compareErrors(expectedErrorsQList, e);
        isThrowErrors = true;
    }
    QVERIFY(root == NULL);
    QVERIFY(isThrowErrors == true);

}

void test_createLogicalTree::negation()
{
    //для строки A !
    QString str = "A !";
    node *root = NULL;
    
    node *expectedTree = new node;
    expectedTree->type = NOT;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->data = "A";
    expectedTree->childrens[1] = NULL;

    createLogicalTree(str);

    compareTrees(expectedTree, root);


}

void test_createLogicalTree::disjunction()
{
    //для строки A B +
    QString str = "A B +";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = OR;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->data = "A";
    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->data = "B";

    createLogicalTree(str);

    compareTrees(expectedTree, root);


}

void test_createLogicalTree::conjunction()
{
    //для строки A B *
    QString str = "A B *";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = AND;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->data = "A";
    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->data = "B";

    createLogicalTree(str);

    compareTrees(expectedTree, root);

}

void test_createLogicalTree::exclusiveOr()
{
    //для строки A B -
    QString str = "A B -";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = XOR;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->data = "A";
    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->data = "B";

    createLogicalTree(str);

    compareTrees(expectedTree, root);


}

void test_createLogicalTree::nand()
{

    QString str = "A B *!";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = NOT;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = AND;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->data = "A";
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[1]->data = "B";
    expectedTree->childrens[1] = NULL;

    createLogicalTree(str);

    compareTrees(expectedTree, root);


}


void test_createLogicalTree::nor()
{

    QString str = "A B +!";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = NOT;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = OR;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->data = "A";
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[1]->data = "B";
    expectedTree->childrens[1] = NULL;

    createLogicalTree(str);

    compareTrees(expectedTree, root);




}

void test_createLogicalTree::complexTest1()
{

    QString str = "A B C * + D ! -";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = XOR;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = OR;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = AND;
    expectedTree->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->childrens[0]->data = "C";
    expectedTree->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->childrens[1]->data = "B";
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[1]->data = "A";
    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->data = "D";

    createLogicalTree(str);

    compareTrees(expectedTree, root);


}

void test_createLogicalTree::complexTest2()
{

    QString str = "A B C D * + * E ! -";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = XOR;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = OR;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = AND;
    expectedTree->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->childrens[0]->data = "D";
    expectedTree->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->childrens[1]->data = "C";
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->type = AND;
    expectedTree->childrens[0]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[1]->childrens[0]->data = "B";
    expectedTree->childrens[0]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[1]->childrens[1]->data = "A";
    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->data = "E";

    createLogicalTree(str);

    compareTrees(expectedTree, root);


}

void test_createLogicalTree::complexTest3()
{
    QString str = "A B + ! C D + - F -";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = XOR;
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = OR;
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = NOT;
    expectedTree->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->childrens[0]->type = OR;
    expectedTree->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->childrens[0]->childrens[0]->data = "B";
    expectedTree->childrens[0]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->childrens[0]->childrens[1]->data = "A";
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->type = OR;
    expectedTree->childrens[0]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[1]->childrens[0]->data = "D";
    expectedTree->childrens[0]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[1]->childrens[1]->data = "C";
    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = NOT;
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->data = "F";

    createLogicalTree(str);

    compareTrees(expectedTree, root);




}

void test_createLogicalTree::cleanupTestCase()
{

}

