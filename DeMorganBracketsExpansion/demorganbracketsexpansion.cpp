#include "demorganbracketsexpansion.h"
#include <iostream>
#include <QFile>
#include <QList>
#include <QTextStream>

node *createLogicalTree(QString expression)
{
    // Если строка состоит только из белых разделителей выдать ошибку
    if (expression.trimmed().isEmpty())
    {
        QList<error> emptyTree;
        emptyTree.append({EMPTY_TREE, 0, ""});
        throw emptyTree;
    }
    QList<stackElement> stack;
    QList<error> errorList;

    const QStringList lexemes = expression.split(' ');

    QList<QString>::const_iterator lexemeIterator = lexemes.begin();
    int currentLexemePosition = 0;

    for (QString currentLexeme : lexemes)
    {
        switch (lexemeClassification(currentLexeme))
        {
        case EMPTY:{
            // Текущая лексема - пустая
            errorList.append({TO_MANY_SPACES, currentLexemePosition, currentLexeme}); // Лишний разделитель (пробел)
            break;
            }

        case OPERATOR:{
            // Текущая лексема - оператор
            node *operatorNode = new node();
            operatorNode->type = operatorsMap[currentLexeme].type;
            operatorNode->data = currentLexeme;

            if (stack.size() < operatorsMap[currentLexeme].amountOfOperands)
            {
                // Не хватает операндов в стеке для того чтобы заполнить оператор
                errorList.append({NOT_ENOUGH_ARGUMENTS, currentLexemePosition, currentLexeme});
            }
            else
            {
                // Добавить детей в новый узел
                for (int i = 0; i < operatorsMap[currentLexeme].amountOfOperands; i++)
                {
                    operatorNode->childrens.append(stack.takeLast().element);
                }
            }

            // Добавить новый узел в стек
            stack.append({operatorNode, currentLexemePosition});
            break;
            }

        case VAR:{
            // Текущая лексема - переменная
            node *variableNode = new node();
            variableNode->type = VARIABLE;
            variableNode->data = currentLexeme;

            // Добавить новый узел в стек
            stack.append({variableNode, currentLexemePosition});
            break;
            }

        case UNKNOWN_LEXEME:{
            // Ошибки в написании переменной
            // Добавить ошибки в общий список
            for (error exeption : variableValidation(currentLexeme))
            {
                exeption.position += currentLexemePosition; // Добавить позицию лексемы в строке
                errorList.append(exeption);
            }
            break;
            }
        }

        // Позиция считается как сумма длин всех предыдущих лексем + кол-во разделителей
        currentLexemePosition += currentLexeme.length() + 1;
    }

    if (stack.size() > 1)
    {
        // После обработки выражения в стеке остались необработанные операторы (древо не сходится к единому корню)
        while (stack.size() > 0)
        {
            stackElement stackNode = stack.takeLast();
            errorList.append({NOT_ENOUGH_OPERATORS, stackNode.position, stackNode.element->data});
        }
    }

    if (stack.size() == 0)
    {
        // Пустое дерево
        errorList.append({EMPTY_TREE, 0, ""});
    }

    // Если во время обработки выражения возникли ошибки, то выбросить их
    if (errorList.size() > 0)
    {
        throw errorList;
    }

    // Вернуть корень дерева
    return stack.takeLast().element;
}

void deMorganTransform(node *root)
{

}

void deleteDoubleNegation(node *root)
{

}

void treeToString(node *root, QString str)
{

}

QString getStringFromFile(QString path)

{   
    QList<error> errorList;

    if (path.isEmpty()) {
        // Путь к файлу пустой
        error pathError;
        pathError.type = PATH_NOT_FOUND;
        errorList.append(pathError);
        throw errorList;
    }

    QFile file(path);
    if (!file.exists()) {
        // Файл по пути не найден
        error fileError;
        fileError.type = FILE_NOT_FOUND;
        errorList.append(fileError);
        throw errorList;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Нет доступа к файлу
        error fileError;
        fileError.type = FILE_NOT_OPENED;
        errorList.append(fileError);
        throw errorList;
    }

    QTextStream in(&file);
    QString line = in.readLine();

    if (!line.isNull() && !in.atEnd()) {
        // В файле содержится больше одной строки
        error multipleStringsError;
        multipleStringsError.type = MORE_THAN_ONE_STRING;
        errorList.append(multipleStringsError);
        throw errorList;
    }

    return line;

}

void saveStringToFile(QString path, QString str)
{
    QList<error> errorList;

    // Проверка наличия пути к файлу
    if (path.isEmpty()) {
        // Путь к файлу пустой
        error pathError;
        pathError.type = PATH_NOT_FOUND;
        errorList.append(pathError);
        throw errorList;
    }

    // Открытие файла
    QFile file(path);

    // Проверка доступа к файлу
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Нет доступа к файлу
        error noAccessToFileError;
        noAccessToFileError.type = NO_ACCESS_TO_FILE;
        errorList.append(noAccessToFileError);
        throw errorList;
    }

    // поток записи в файл
    QTextStream out(&file); 
    out << str; 

    file.close();


}

QList<error> variableValidation(QString lexeme)
{
    QList<error> errorList;
    if (lexeme == "")
    {   
        error emptyLexemeError = {EMPTY_LEXEME, 0, ""};
        errorList.append(emptyLexemeError);
        return errorList;
    }

    if (lexeme[0].isDigit())
    {
        error digitError = {VARIABLE_STARTS_WITH_DIGIT, 0, lexeme[0]};
        errorList.append(digitError);
        
    }

    for (int i = 0; i < lexeme.length(); i++)
    {
        if (!lexeme[i].isDigit() && !lexeme[i].isLetter())
        {
            error incorrectSymbolError = {UNKNOWN_SYMBOL, i, lexeme[i]};
            errorList.append(incorrectSymbolError);
            
        }
    }

    return errorList;
}

lexemeType lexemeClassification(QString lexeme)
{
    if (lexeme == "")
    {
        return EMPTY;
    }
    if (operatorsMap.contains(lexeme))
    {
        return OPERATOR;
    }
    if (variableValidation(lexeme).isEmpty())
    {
        return VAR;
    }
    else
    {
        return UNKNOWN_LEXEME;
    }
}
