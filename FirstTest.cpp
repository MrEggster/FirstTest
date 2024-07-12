//Постановка задачи:
    // В excel файле есть два столбца:
    // Key-"Имя посетителя"           Value-"Название фирмы/отдела"

    // Мэддисон Илья Сергеевич                 twitch.com
    // Соболев Николай Юрьевич               Парк Горького
    //       ....                                   ....
    //  Скуфов Алексей Антонович                Москва Петушки

    //Сохраняем excel как txt с табуляциями
    //Используем multimap для хранения повторяющихся ключей, не разбивая на задачи
    //когда о посетителе может быть известна только одна информация(организация или отдел)

    //Информация о новых посетителях вносится в таблицу Excel и сохраняется в txt

#include <map>
#include<string>
#include <iostream>
//#include <xlnt/xlnt.hpp> //Первоначально планировалось подключить библиотеки xlnt/OpenXLSX, но они не воспринимают кириллицу для ввода/вывода :(
#include <fstream>
using namespace std;

void save(fstream& file, multimap<string, string>& Visitors)//Табуляции в txt позволяют отделить key and Value
{
    while (!file.eof())
    {
        string line;
        string key;
        string value;
        int i;
        getline(file, line);
        if (line.empty())//Если случайно навели курсором на пустые строки
        {
            cout << "Проверьте пустые строки в конце файла" << endl;
            break;
        }
        for (i = 0; line[i] != '\t';i++);
        for (int j = 0; j < i; j++)
        {
            key.push_back(line[j]);
        }
        for (auto it = line.begin() + i + 1; it != line.end();++it)
        {
            value.push_back(*it);
        }

        Visitors.emplace(key, value);

    }

}


int main()
{
    setlocale(LC_ALL, "Rus");
    system("chcp 1251");//Для корректного ввода кириллицы в консоль 
    cout << '\n';

    fstream file("Names_Orgs.txt");

    multimap<string, string> Visitors;

    save(file, Visitors);

    cout << "Ожидайте загрузки данных" << endl;


    while (true)
    {
        string name;
        cout << '\n';
        cout << "Введите ФИО посетителя: " << endl;
        getline(cin, name);
        auto it = Visitors.find(name);
        if (it != Visitors.end())
        {
            cout << "Отдел или организация:" << " " << it->second << endl;
            cout << "Доступ разрешен!" << endl;
        }
        else
        {
            cout << "Такого посетителя нет" << endl;
        }

    }


}
