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

    if (stack.size() == 0)
    {
        // Пустое дерево
        errorList.append({EMPTY_TREE, 0, ""});
    }

    if (stack.size() > 1)
    {
        // После обработки выражения в стеке остались необработанные операторы (древо не сходится к единому корню)
        while (stack.size() > 0)
        {
            stackElement stackNode = stack.takeFirst();
            errorList.append({NOT_ENOUGH_OPERATORS, stackNode.position, stackNode.element->data});
        }
    }



    // Если во время обработки выражения возникли ошибки, то выбросить их
    if (errorList.size() > 0)
    {
        throw errorList;
    }

    // Вернуть корень дерева
    return stack.takeLast().element;
}

void copyNode(node *root, node *copy )
{
    copy->type = root->type;
    copy->data = root->data;
    copy->childrens = root->childrens;
}

void deMorganTransform(node *root)
{
    if (root->type == NOT || root->type == NAND || root->type == NOR) {
        //Считаем количество отрицаний подряд
        int negationsInARow = nodeInARow(root, NOT).size();

        //следующий узел не являющийся отрицанием
        QList<node*> negationsRow = nodeInARow(root, NOT); 
        node *child = negationsRow.isEmpty() ? root : negationsRow.last()->childrens.first();

        // Учитываем отрицания в NAND и NOR
        negationsInARow += child->type == NAND || child->type == NOR ? 1 : 0;
        if (child->type == AND || child->type == OR || child->type == NAND || child->type == NOR && negationsInARow != 0){
            switch (child->type)
            {
            case AND:
                child->type = negationsInARow % 2 == 0 ? AND : OR;
                break;
            case OR:
                child->type = negationsInARow % 2 == 0 ? OR : AND;
                break;
            case NAND:
                child->type = negationsInARow % 2 == 0 ? AND : OR;
                break;
            case NOR:
                child->type = negationsInARow % 2 == 0 ? OR : AND;
                break;
            }
            //child->data = getIntrpretationOfOperator(child->type);
            node *negationNode = new node();
            negationNode->type = NOT;
            //negationNode->data = getIntrpretationOfOperator(NOT);
            // Добавить то количество отрицаний перед детьми оператора, которое содержится в стеке 
            insertBetween(child, 0, negationNode, negationsInARow);
            insertBetween(child, 1, negationNode, negationsInARow);
            
            //Удалить отрицания если они есть
            if (child != root){
                copyNode(child, root);
                delete child;
                foreach (node* nodeToDelete, negationsRow) {
                if (nodeToDelete != root)
                    delete nodeToDelete;
                } 
            }
            
            
        }
    }
    
    //Рекурсивно вызвать функцию для всех детей
    foreach (node* child, root->childrens) {
        deMorganTransform(child);
    }

}

QList<node*> nodeInARow(node *root, int type)
{
    QList<node*> stackOfNodesInARow;
    node *currentNode = root;
    while (currentNode->type == type) {
            stackOfNodesInARow.append(currentNode);
            currentNode = currentNode->childrens.first();
        }
    return stackOfNodesInARow;    
}

void insertBetween(node *parent, int childId, node *nodeToInsert, int n)
{
    node *currentChild = parent->childrens[childId];
    
    for (int i = 0; i < n; i++)
    {
        node *insertNode = new node();
        copyNode(nodeToInsert, insertNode);
        insertNode->childrens.append(currentChild);
        parent->childrens[childId] = insertNode;
        currentChild = parent->childrens[childId];
    }
}

void deleteDoubleNegation(node *root)
{   
    if (root->type == NOT) {
        //Собираем в стек все отрицания идущие подряд
        QList<node*> stackOfNegationsInARow = nodeInARow(root, NOT);
        //следующий после отрицаний узел
        node *child = stackOfNegationsInARow.last()->childrens.first();
        
        if(child->type == NAND || child->type == NOR) {
            //Если следующий после отрицаний оператор - NAND или NOR
            if (stackOfNegationsInARow.size() + 1 % 2 == 0) {
            // Если отрицания в стеке не уничтожают друг друга, то уничтожить их за счет преобразования NAND и NOR в AND и OR соответственно
                child->type = (child->type == NAND ? AND : OR);
            }
        } else {
            //Если следующий после отрицаний оператор не NAND или NOR
            if (!(stackOfNegationsInARow.size() % 2 == 0)) {
                // Если отрицания в стеке не уничтожают друг друга, то достать из стека последнее отрицание
                child = stackOfNegationsInARow.takeLast();
            } 
        }

        //Если в стеке осталось больше одного отрицания, то уничтожить их
        if (stackOfNegationsInARow.size() > 1){
            copyNode(child, root);
            delete child;
            //Очистить память от всех узлов содержащихся в стеке
            foreach (node* nodeToDelete, stackOfNegationsInARow) {
                if (nodeToDelete != root)
                    delete nodeToDelete;
            }
        }   
    }
    
    //Рекурсивно вызвать функцию для всех детей
    foreach (node* child, root->childrens) {
        deleteDoubleNegation(child);
    }

}

void treeToString(node *root, QString &str)
{
    QList<error> errorList;
    QList<node*> stack;
    QList<QString> outputStack;

    if (root == nullptr) {
        str = "";
        return;
    }
    
    stack.append(root);
    while (!stack.isEmpty()) {
        node* current = stack.takeLast();
        switch (current->type)
        {
        case VARIABLE:
            if (variableValidation(current->data).isEmpty())
                outputStack.append(current->data);
            else {
                for (error exeption : variableValidation(current->data))
                {
                    errorList.append(exeption);
                }
            }
            break;
        
        case NULL_ELEMENT:
            errorList.append({EMPTY_TREE, 0, ""});
            break;
        
        default:
            for (int i = current->childrens.size() - 1; i >= 0; --i) {
                stack.append(current->childrens[i]);
            }
            outputStack.append(getIntrpretationOfOperator(current->type));
            break;
        }
        
    }

    if (errorList.size() > 0)
    {
        throw errorList;
    }
   
    str = "";
    while (!outputStack.isEmpty()) {
        str += outputStack.takeLast();
        if (!outputStack.isEmpty())
            str += " ";
    } 

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

QString getIntrpretationOfOperator(operandType type){
    if (type == VARIABLE){
        return "VARIABLE";
    }
    for (auto iterator=operatorsMap.begin(); iterator!=operatorsMap.end(); iterator++) {
        if (iterator.value().type == type) {
            return iterator.key();
        }
    }
}

void exeptionHandler(QList<error> errors){
    for (error exeption : errors)
    {
        switch (exeption.type)
        {
        case PATH_NOT_FOUND:
            qDebug() << "Путь к файлу пустой";
            break;
        case FILE_NOT_FOUND:
            qDebug() << "Файл по пути не найден";
            break;
        case FILE_NOT_OPENED:
            qDebug() << "Нет доступа к файлу";
            break;
        case MORE_THAN_ONE_STRING:
            qDebug() << "В файле содержится больше одной строки";
            break;
        case UNKNOWN_SYMBOL:
            qDebug() << "Неизвестный символ в названии переменной " << exeption.data << " на позиции " << exeption.position;
            break;
        case NOT_ENOUGH_OPERATORS:
            qDebug() << "Недостаточно операторов у " << exeption.data << " на позиции " << exeption.position;
            break;
        case NOT_ENOUGH_ARGUMENTS:
            qDebug() << "Недостаточно аргументов у " << exeption.data << " на позиции " << exeption.position;
            break;
        case TO_MANY_SPACES:
            qDebug() << "Неожиданный пробел на позиции " << exeption.position << " Ожидался операнд ";
            break;
        case EMPTY_TREE:
            qDebug() << "Пустое дерево";
            break;
        case NO_ACCESS_TO_FILE:
            qDebug() << "Нет доступа к файлу";
            break;
        case VARIABLE_STARTS_WITH_DIGIT:
            qDebug() << "Переменная начинается с цифры " << exeption.data << " на позиции " << exeption.position;
            break;
        case EMPTY_LEXEME:
            qDebug() << "Пустая лексема";
            break;
        default:
            break;
        }    
    }
}
