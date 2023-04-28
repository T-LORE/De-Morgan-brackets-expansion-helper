#include "test_createlogicaltree.h"
#include "qtestcase.h"
#include <QtTest>
#include <QList>


test_createLogicalTree::test_createLogicalTree(QObject *parent) : QObject(parent)
{
}

void test_createLogicalTree::compareErrors(errors expectedErrors, errors errors)
{
    QVERIFY(expectedErrors.list.size() == errors.list.size());
    for (int i = 0; i < expectedErrors.list.size(); i++) {
        QVERIFY(expectedErrors.list[i].error == errors.list[i].error);
        QVERIFY(expectedErrors.list[i].position == errors.list[i].position);
        QVERIFY(expectedErrors.list[i].symbol == errors.list[i].symbol);
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

    compareTrees(expectedTree->left, tree->left);
    compareTrees(expectedTree->right, tree->right);


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
    expectedErrorsQList.append({
                                   NOT_ENOUGH_ARGUMENTS,
                                   0,
                                   '!'
                               });
    errors expectedError = {
        expectedErrorsQList
    };

    try {
        root = createLogicalTree(str);
    } catch (errors e) {
        compareErrors(expectedError, e);
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
    expectedErrorsQList.append({
        NOT_ENOUGH_OPERATORS,
        0,
        'A'
    });
    errors expectedError = {
        expectedErrorsQList

    };


    try {
        root = createLogicalTree(str);
    } catch (errors e) {
        compareErrors(expectedError, e);
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
    expectedTree->left = new node;
    expectedTree->left->type = OR;
    expectedTree->left->left = new node;
    expectedTree->left->left->type = VARIABLE;
    expectedTree->left->left->data = "A";
    expectedTree->left->right = new node;
    expectedTree->left->right->type = VARIABLE;
    expectedTree->left->right->data = "B";
    expectedTree->right = NULL;

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
        2,
        'B'
    });
    expectedErrorsQList.append({
        NOT_ENOUGH_OPERATORS,
        4,
        'C'
    });
    errors expectedError = {
        expectedErrorsQList
    };

    try {
        root = createLogicalTree(str);
    } catch (errors e) {
        compareErrors(expectedError, e);
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
    expectedErrorsQList.append({
        NOT_ENOUGH_ARGUMENTS,
        0,
        '+'
    });
    expectedErrorsQList.append({
        NOT_ENOUGH_ARGUMENTS,
        2,
        '!'
    });
    errors expectedError = {
        expectedErrorsQList
    };


    try {
        root = createLogicalTree(str);
    } catch (errors e) {
        compareErrors(expectedError, e);
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
    expectedErrorsQList.append({
        UNKNOWN_SYMBOL,
        0,
        '/'
    });
    errors expectedError = {
        expectedErrorsQList
    };

    try {
        root = createLogicalTree(str);
    } catch (errors e) {
        compareErrors(expectedError, e);
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
    expectedErrorsQList.append({
        UNKNOWN_SYMBOL,
        8,
        '/'
    });
    errors expectedError = {
        expectedErrorsQList
    };

    try {
        root = createLogicalTree(str);
    } catch (errors e) {
        compareErrors(expectedError, e);
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
    expectedErrorsQList.append({
        NOT_ENOUGH_ARGUMENTS,
        2,
        '+'
    });
    expectedErrorsQList.append({
        UNKNOWN_SYMBOL,
        3,
        '<'
    });
    expectedErrorsQList.append({
        UNKNOWN_SYMBOL,
        11,
        '/'
    });
    expectedErrorsQList.append({
        NOT_ENOUGH_OPERATORS,
        13,
        'C'
    });
    errors expectedError = {
        expectedErrorsQList
    };

    try {
        root = createLogicalTree(str);
    } catch (errors e) {
        compareErrors(expectedError, e);
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
    expectedTree->left = new node;
    expectedTree->left->type = VARIABLE;
    expectedTree->left->data = "A";
    expectedTree->right = NULL;

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
    expectedTree->left = new node;
    expectedTree->left->type = VARIABLE;
    expectedTree->left->data = "A";
    expectedTree->right = new node;
    expectedTree->right->type = VARIABLE;
    expectedTree->right->data = "B";

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
    expectedTree->left = new node;
    expectedTree->left->type = VARIABLE;
    expectedTree->left->data = "A";
    expectedTree->right = new node;
    expectedTree->right->type = VARIABLE;
    expectedTree->right->data = "B";

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
    expectedTree->left = new node;
    expectedTree->left->type = VARIABLE;
    expectedTree->left->data = "A";
    expectedTree->right = new node;
    expectedTree->right->type = VARIABLE;
    expectedTree->right->data = "B";

    createLogicalTree(str);

    compareTrees(expectedTree, root);


}

void test_createLogicalTree::nand()
{

    QString str = "A B *!";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = NOT;
    expectedTree->left = new node;
    expectedTree->left->type = AND;
    expectedTree->left->left = new node;
    expectedTree->left->left->type = VARIABLE;
    expectedTree->left->left->data = "A";
    expectedTree->left->right = new node;
    expectedTree->left->right->type = VARIABLE;
    expectedTree->left->right->data = "B";
    expectedTree->right = NULL;

    createLogicalTree(str);

    compareTrees(expectedTree, root);


}


void test_createLogicalTree::nor()
{

    QString str = "A B +!";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = NOT;
    expectedTree->left = new node;
    expectedTree->left->type = OR;
    expectedTree->left->left = new node;
    expectedTree->left->left->type = VARIABLE;
    expectedTree->left->left->data = "A";
    expectedTree->left->right = new node;
    expectedTree->left->right->type = VARIABLE;
    expectedTree->left->right->data = "B";
    expectedTree->right = NULL;

    createLogicalTree(str);

    compareTrees(expectedTree, root);




}

void test_createLogicalTree::complexTest1()
{

    QString str = "A B C * + D ! -";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = XOR;
    expectedTree->left = new node;
    expectedTree->left->type = OR;
    expectedTree->left->left = new node;
    expectedTree->left->left->type = AND;
    expectedTree->left->left->left = new node;
    expectedTree->left->left->left->type = VARIABLE;
    expectedTree->left->left->left->data = "C";
    expectedTree->left->left->right = new node;
    expectedTree->left->left->right->type = VARIABLE;
    expectedTree->left->left->right->data = "B";
    expectedTree->left->right = new node;
    expectedTree->left->right->type = VARIABLE;
    expectedTree->left->right->data = "A";
    expectedTree->right = new node;
    expectedTree->right->type = NOT;
    expectedTree->right->left = new node;
    expectedTree->right->left->type = VARIABLE;
    expectedTree->right->left->data = "D";

    createLogicalTree(str);

    compareTrees(expectedTree, root);


}

void test_createLogicalTree::complexTest2()
{

    QString str = "A B C D * + * E ! -";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = XOR;
    expectedTree->left = new node;
    expectedTree->left->type = OR;
    expectedTree->left->left = new node;
    expectedTree->left->left->type = AND;
    expectedTree->left->left->left = new node;
    expectedTree->left->left->left->type = VARIABLE;
    expectedTree->left->left->left->data = "D";
    expectedTree->left->left->right = new node;
    expectedTree->left->left->right->type = VARIABLE;
    expectedTree->left->left->right->data = "C";
    expectedTree->left->right = new node;
    expectedTree->left->right->type = AND;
    expectedTree->left->right->left = new node;
    expectedTree->left->right->left->type = VARIABLE;
    expectedTree->left->right->left->data = "B";
    expectedTree->left->right->right = new node;
    expectedTree->left->right->right->type = VARIABLE;
    expectedTree->left->right->right->data = "A";
    expectedTree->right = new node;
    expectedTree->right->type = NOT;
    expectedTree->right->left = new node;
    expectedTree->right->left->type = VARIABLE;
    expectedTree->right->left->data = "E";

    createLogicalTree(str);

    compareTrees(expectedTree, root);


}

void test_createLogicalTree::complexTest3()
{
    QString str = "A B + ! C D + - F -";
    node *root = NULL;

    node *expectedTree = new node;
    expectedTree->type = XOR;
    expectedTree->left = new node;
    expectedTree->left->type = OR;
    expectedTree->left->left = new node;
    expectedTree->left->left->type = NOT;
    expectedTree->left->left->left = new node;
    expectedTree->left->left->left->type = OR;
    expectedTree->left->left->left->left = new node;
    expectedTree->left->left->left->left->type = VARIABLE;
    expectedTree->left->left->left->left->data = "B";
    expectedTree->left->left->left->right = new node;
    expectedTree->left->left->left->right->type = VARIABLE;
    expectedTree->left->left->left->right->data = "A";
    expectedTree->left->right = new node;
    expectedTree->left->right->type = OR;
    expectedTree->left->right->left = new node;
    expectedTree->left->right->left->type = VARIABLE;
    expectedTree->left->right->left->data = "D";
    expectedTree->left->right->right = new node;
    expectedTree->left->right->right->type = VARIABLE;
    expectedTree->left->right->right->data = "C";
    expectedTree->right = new node;
    expectedTree->right->type = NOT;
    expectedTree->right->left = new node;
    expectedTree->right->left->type = VARIABLE;
    expectedTree->right->left->data = "F";

    createLogicalTree(str);

    compareTrees(expectedTree, root);




}

void test_createLogicalTree::cleanupTestCase()
{

}

