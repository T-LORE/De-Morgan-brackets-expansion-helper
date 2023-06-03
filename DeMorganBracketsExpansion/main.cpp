/*!
*\file
*\brief Данный файл содержит главную управляющую функцию программы
*\mainpage Документация для программы "De Morgan Brackets Expansion"
Программа предназначена раскрытия скобок в логическом выражении по правилам де Моргана и удаления двойных отрицаний.
Для функционирования программы необходима операционная система Windows 10 или выше.
Программа разработана на языке С++ с использованием библиотеки QT в IDE QT creator.
Стандарт языка ISO C++17 (/std:c++17).
Программа должна получать два параметра командной строки: путь входного файла с записанной в обратной польской записи логическим выражением и путь для выходного файла.

Пример команды запуска программы:
*\code
deMorganBracketsExpansion.exe.exe C:\\Documents\input.txt C:\\Documents\output.txt
*\endcode
*\author Зверьков Максим
*\date Май 2023 года
*\version 1.0
*/
#include "demorganbracketsexpansion.h"

int main(int argc, char *argv[])
{   
    //Поддержка русского языка в консоли
    setlocale(LC_ALL, "");

    if (argc > 3){
        exeptionHandler(QList<error>() << error(TO_MANY_ARGUMENTS, 0, ""));
        return 0;
    }

    //Получить строку из файла
    QString equasion;
    try {
        equasion = getStringFromFile(argv[1]);
    } catch (QList<error> exeptions) {
        exeptionHandler(exeptions);
        return 0;
    }

    //Создать логическое дерево
    node *root; 
    try{
        root = createLogicalTree(equasion);
    } catch (QList<error> exeptions) {
        exeptionHandler(exeptions);
        return 0;
    }

    //Преобразовать логическое дерево по законам де Моргана
    deMorganTransform(root);

    //Удалить двойные отрицания
    deleteDoubleNegation(root);

    //Преобразовать логическое дерево в строку
    QString outputEquasion;
    treeToString(root, outputEquasion);

    //Записать строку в файл
    try{
        saveStringToFile(argv[2], outputEquasion);
    } catch (QList<error> exeptions) {
        exeptionHandler(exeptions);
        return 0;
    }
    
    return 1;
}

