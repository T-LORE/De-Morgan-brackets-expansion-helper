#include <QCoreApplication>
#include <QTest>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "test_createlogicaltree.h"
#include "test_deletedoublenegation.h"
#include "test_demorgantransform.h"
#include "test_treetostring.h"


int main(int argc, char *argv[])
{
    //freopen("testing.log", "w", stdout);
    //QCoreApplication a(argc, argv);

    QTest::qExec(new test_createLogicalTree, argc, argv);
    QTest::qExec(new test_deMorganTransform, argc, argv);
    QTest::qExec(new test_deleteDoubleNegation, argc, argv);
    QTest::qExec(new test_treeToString, argc, argv);
    return 0;
}
