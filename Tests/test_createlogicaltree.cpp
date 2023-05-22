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
    QCOMPARE(actualErrors.size(), expectedErrors.size());
    for (int i = 0; i < expectedErrors.size(); i++)
    {
        QCOMPARE(expectedErrors[i].type, actualErrors[i].type);
        QCOMPARE(expectedErrors[i].position, actualErrors[i].position);
        QCOMPARE(expectedErrors[i].data, actualErrors[i].data);
    }
}
void test_createLogicalTree::compareNodes(const node *expectedNode, const node *actualNode) {
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

void test_createLogicalTree::compareTrees(node *expectedTree, node *actualTree) {
    if (expectedTree == nullptr && actualTree == nullptr)
        return;

    if (expectedTree == nullptr && actualTree != nullptr)
        QFAIL("expectedTree - null, actualTree не null");
    if (expectedTree != nullptr && actualTree == nullptr)
        QFAIL("expectedTree не null, but actualTree - null");
    

    compareNodes(expectedTree, actualTree);
}
//void test_createLogicalTree::compareTrees(node *expectedTree, node *tree)
//{
//    if (expectedTree == NULL) {
//        QVERIFY(tree == NULL);
//        return;
//    }
//    if (tree == NULL){
//        QVERIFY(expectedTree == NULL);
//        return;
//    }
//    QVERIFY(expectedTree->type == tree->type);
//    QVERIFY(expectedTree->data == tree->data);

//    compareTrees(expectedTree->childrens[0], tree->childrens[0]);
//    compareTrees(expectedTree->childrens[1], tree->childrens[1]);


//}

void test_createLogicalTree::initTestCase()
{

}

void test_createLogicalTree::emptyLine()
{
    QString str = "";
    node *root = NULL;
    QList<error> expectedErrorsQList = (QList<error>() << error(EMPTY_TREE, 0, ""));
    try
    {
        node *root = createLogicalTree(str);
    }
    catch(QList<error> actualErrors)
    {
        compareErrors (expectedErrorsQList, actualErrors);
    }
    
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
    } catch (QList<error> actualError) {
        compareErrors(expectedErrorsQList, actualError);
    }
    QVERIFY(root == NULL);
}

void test_createLogicalTree::oneSymbolOperand()
{
    QString str = "A";
    node *root = NULL;

    node * expectedTree = new node;
    expectedTree->type = VARIABLE;
    expectedTree->data = "A";


    root = createLogicalTree(str);

    compareTrees(expectedTree, root);

}

void test_createLogicalTree::manySymbols()
{
    QString str = "A B + !";

    node *expectedTree = new node;
    expectedTree->type = NOT;
    expectedTree->data = "!";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = OR;
    expectedTree->childrens[0]->data = "+";

    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->data = "B";

    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[1]->data = "A";



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


    expectedErrorsQList.append({
        NOT_ENOUGH_OPERATORS,
        0,
        "A"
    });
    expectedErrorsQList.append({
        NOT_ENOUGH_OPERATORS,
        2,
        "B"
    });

    expectedErrorsQList.append({
        NOT_ENOUGH_OPERATORS,
        4,
        "C"
    });



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
    QList<error> expectedErrorsQList;
    error e = {
        NOT_ENOUGH_ARGUMENTS,
        0,
        "+"
    };

    expectedErrorsQList.append(e);

    try {
        root = createLogicalTree(str);
    } catch (QList<error> e) {
        compareErrors(expectedErrorsQList, e);

    }
    QVERIFY(root == NULL);



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
    QList<error> expectedErrorsQList;

    expectedErrorsQList.append({
        UNKNOWN_SYMBOL,
        2,
        "+"
    });

    expectedErrorsQList.append({
        UNKNOWN_SYMBOL,
        3,
        "<"
    });

    expectedErrorsQList.append({
        NOT_ENOUGH_OPERATORS,
        11,
        "/"
    });

    expectedErrorsQList.append({
        NOT_ENOUGH_OPERATORS,
        9,
        "!"
    });

    expectedErrorsQList.append({
        NOT_ENOUGH_OPERATORS,
        13,
        "C"
    });

    try {
        root = createLogicalTree(str);
    } catch (QList<error> e) {
        compareErrors(expectedErrorsQList, e);

    }
    QVERIFY(root == NULL);


}

void test_createLogicalTree::negation()
{
    //для строки A !
    QString str = "A !";
    node *root = NULL;
    
    node *expectedTree = new node;
    expectedTree->type = NOT;
    expectedTree->data = "!";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->data = "A";

    root = createLogicalTree(str);

    compareTrees(expectedTree, root);


}

void test_createLogicalTree::disjunction()
{
    //для строки A B +
    QString str = "A B +";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = OR;
    expectedTree->data = "+";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->data = "B";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->data = "A";

    root = createLogicalTree(str);

    compareTrees(expectedTree, root);


}

void test_createLogicalTree::conjunction()
{
    //для строки A B *
    QString str = "A B *";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = AND;
    expectedTree->data = "*";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->data = "B";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->data = "A";

    root = createLogicalTree(str);

    compareTrees(expectedTree, root);

}

void test_createLogicalTree::exclusiveOr()
{
    //для строки A B -
    QString str = "A B -";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = XOR;
    expectedTree->data = "-";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->data = "B";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->data = "A";

    root = createLogicalTree(str);

    compareTrees(expectedTree, root);


}

void test_createLogicalTree::nand()
{

    QString str = "A B *!";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = NAND;
    expectedTree->data = "*!";


    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->data = "B";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->data = "A";


    root = createLogicalTree(str);

    compareTrees(expectedTree, root);


}


void test_createLogicalTree::nor()
{

    QString str = "A B +!";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = NOT;
    expectedTree->data = "+!";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->data = "B";

    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->data = "A";
 

    root = createLogicalTree(str);

    compareTrees(expectedTree, root);




}

void test_createLogicalTree::complexTest1()
{

    QString str = "A B C * + D ! -";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = XOR;
    expectedTree->data = "-";
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = NOT;
    expectedTree->childrens[0]->data = "!";
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->data = "D";
    
    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = OR;
    expectedTree->childrens[1]->data = "+";
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = AND;
    expectedTree->childrens[1]->childrens[0]->data = "*";
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->data = "C";
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[1]->data = "B";
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[1]->data = "A";


    root = createLogicalTree(str);

    compareTrees(expectedTree, root);


}

void test_createLogicalTree::complexTest2()
{

    QString str = "A B * C D * + E ! -";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = XOR;
    expectedTree->data = "-";
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = NOT;
    expectedTree->childrens[0]->data = "!";

    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->data = "E";
    
    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = OR;
    expectedTree->childrens[1]->data = "+";
    
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = AND;
    expectedTree->childrens[1]->childrens[0]->data = "*";
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->data = "D";
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[1]->data = "C";

    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->type = AND;
    expectedTree->childrens[1]->childrens[1]->data = "*";
    expectedTree->childrens[1]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->data = "B";
    expectedTree->childrens[1]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[1]->childrens[1]->data = "A";

    root = createLogicalTree(str);

    compareTrees(expectedTree, root);


}

void test_createLogicalTree::complexTest3()
{
    QString str = "A B + ! C D + - F ! -";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = XOR;
    expectedTree->data = "-";
    expectedTree->childrens.append(new node);
    expectedTree->childrens[0]->type = NOT;
    expectedTree->childrens[0]->data = "!";
    expectedTree->childrens[0]->childrens.append(new node);
    expectedTree->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[0]->childrens[0]->data = "F";
    
    expectedTree->childrens.append(new node);
    expectedTree->childrens[1]->type = OR;
    expectedTree->childrens[1]->data = "+";
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->type = NOT;
    expectedTree->childrens[1]->childrens[0]->data = "!";
    expectedTree->childrens[1]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->type = OR;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->data = "+";
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[0]->data = "B";
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[0]->childrens[0]->childrens[1]->data = "A";
    
    expectedTree->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->type = OR;
    expectedTree->childrens[1]->childrens[1]->data = "+";
    expectedTree->childrens[1]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[0]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[1]->childrens[0]->data = "D";
    expectedTree->childrens[1]->childrens[1]->childrens.append(new node);
    expectedTree->childrens[1]->childrens[1]->childrens[1]->type = VARIABLE;
    expectedTree->childrens[1]->childrens[1]->childrens[1]->data = "C";


    root = createLogicalTree(str);

    compareTrees(expectedTree, root);




}

void test_createLogicalTree::cleanupTestCase()
{

}

