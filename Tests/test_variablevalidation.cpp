#include "test_variablevalidation.h"
#include <QtTest>

void test_variableValidation::compareErrors(QList<error> expectedErrors, QList<error> actualErrors)
{
    QCOMPARE(actualErrors.size(), expectedErrors.size());
    for (int i = 0; i < expectedErrors.size(); i++)
    {
        QCOMPARE(actualErrors[i].type, expectedErrors[i].type);
        QCOMPARE(actualErrors[i].position, expectedErrors[i].position);
        QCOMPARE(actualErrors[i].data, expectedErrors[i].data);
    }
}

void test_variableValidation::variableCorrect_data(){
    QTest::addColumn<QString>("lexeme");
    QTest::addColumn<QList<error>>("expectedErrors");

    QTest::newRow("empty") << "" << (QList<error>() << error(EMPTY_LEXEME, 0, ""));
    QTest::newRow("onlyOneDigit") << "1" << (QList<error>() << error(VARIABLE_STARTS_WITH_DIGIT, 0, "1"));
    QTest::newRow("digitFirst") << "1variable" << (QList<error>() << error(VARIABLE_STARTS_WITH_DIGIT, 0, "1"));
    QTest::newRow("digitCenter") << "variable1variable" << QList<error>();
    QTest::newRow("digitLast") << "variable1" << QList<error>();
    QTest::newRow("manyDigits") << "var1i2ab3le" << QList<error>();
    QTest::newRow("unknownSymbolFirst") << "!variable" << (QList<error>() << error(UNKNOWN_SYMBOL, 0, "!"));
    QTest::newRow("unknownSymbolCenter") << "vari?able" << (QList<error>() << error(UNKNOWN_SYMBOL, 4, "?"));
    QTest::newRow("unknownSymbolLast") << "variable." << (QList<error>() << error(UNKNOWN_SYMBOL, 8, "."));
    QTest::newRow("manyUnknownSymbols") << "var?i!ab!le." << (QList<error>() << error(UNKNOWN_SYMBOL, 3, "?") << error(UNKNOWN_SYMBOL, 5, "!") << error(UNKNOWN_SYMBOL, 8, "!") << error(UNKNOWN_SYMBOL, 11, "."));

    QTest::newRow("fullAlphabet") << "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtU1234567890" << QList<error>();

    QTest::newRow("digitAtStartAndManyUnknownSymbols") << "1var?i!ab!le." << (QList<error>() << error(VARIABLE_STARTS_WITH_DIGIT, 0, "1") << error(UNKNOWN_SYMBOL, 4, "?") << error(UNKNOWN_SYMBOL, 6, "!") << error(UNKNOWN_SYMBOL, 9, "!") << error(UNKNOWN_SYMBOL, 12, "."));



}

void test_variableValidation::variableCorrect(){

    QFETCH(QString, lexeme);
    QFETCH(QList<error>, expectedErrors);

    QList<error> actualErrors = variableValidation(lexeme);
    compareErrors(expectedErrors, actualErrors);
}

