#include "demorganbracketsexpansion.h"
#include <iostream>
#include <QFile>
#include <QList>
#include <QTextStream>

node *createLogicalTree(QString expression)
{
    return 0;
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

bool isVariableCorrect(QString lexeme)
{
    if (lexeme.isEmpty())
    {
        return false;
    }

    if (lexeme[0].isDigit())
    {
        return false;
    }

    for (int i = 0; i < lexeme.length(); i++)
    {
        if (!lexeme[i].isDigit() && !lexeme[i].isLetter())
        {
            return false;
        }
    }

    return true;
}
