#include "demorganbracketsexpansion.h"

int main(int argc, char *argv[])
{   
    //Поддержка русского языка в консоли
    setlocale(LC_ALL, "");

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

