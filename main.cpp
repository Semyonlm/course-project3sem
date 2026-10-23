#include "book.hpp"
#include "reader.hpp"
#include <locale.h>
#include <iostream>

using bookstore::Book;
using bookstore::Reader;

int main()
{
    system("chcp 1251 > nul");
    setlocale(LC_ALL, "Rus");
    std::cout << "1. Статические объекты (стек)" << std::endl;
    Book stackBook("Мастер и Маргарита", "М. Булгаков", "Роман", 3);
    stackBook.Print();

    std::cout << "Оценка 5: ";
    stackBook.SetRating(5);
    std::cout << "Рейтинг = " << stackBook.GetRating() << std::endl;

    std::cout << "\n2. Динамические объекты (new/delete)" << std::endl;
    Book* dynamicBook = new Book("1984", "Дж. Оруэлл", "Антиутопия", 2);
    dynamicBook->Print();

    std::cout << "\n3. Работа по ссылке и указателю" << std::endl;
    Book& refBook = stackBook;  
    refBook.SetRating(4);
    std::cout << "Рейтинг через ссылку: " << stackBook.GetRating() << std::endl;

    Book* ptrBook = dynamicBook;
    ptrBook->WithdrawFromSale();
    std::cout << "Доступность через указатель: "
        << (ptrBook->IsAvailable() ? "да" : "нет") << std::endl;

    std::cout << "\n4. Динамический массив объектов" << std::endl;
    Book* shelf = new Book[2];
    shelf[0].SetTitle("Преступление и наказание");
    shelf[0].SetAuthor("Ф. Достоевский");
    shelf[0].SetGenre("Роман");
    shelf[0].SetStock(4);

    shelf[1].SetTitle("Идиот");
    shelf[1].SetAuthor("Ф. Достоевский");
    shelf[1].SetGenre("Роман");
    shelf[1].SetStock(2);

    shelf[0].Print();
    shelf[1].Print();

    std::cout << "\n5. Массив динамических объектов" << std::endl;
    Book** dynShelf = new Book * [2];
    dynShelf[0] = new Book("Гарри Поттер", "Дж. Роулинг", "Фэнтези", 5);
    dynShelf[1] = new Book("Хоббит", "Дж. Толкин", "Фэнтези", 4);

    dynShelf[0]->Print();
    dynShelf[1]->Print();

    delete dynShelf[0];
    delete dynShelf[1];
    delete[] dynShelf;

    std::cout << "\n6. Агрегация: книги созданы вне читателя" << std::endl;
    Book* witcher = new Book("Ведьмак", "А. Сапковский", "Фэнтези", 2);
    Book* dune = new Book("Дюна", "Ф. Герберт", "Фантастика", 1);
    Book* thedarktower = new Book("Тёмная башня", "С. Кинг", "Фэнтези", 0);

    thedarktower->WithdrawFromSale();

    Book* candidates[] = { witcher, dune, thedarktower };

    {
        std::cout << "\n7. Композиция: читатель и его рекомендательный список" << std::endl;
        Reader reader("Иван");
        reader.PrintStatus();

        std::cout << "\nПроверка правила: оценка вне диапазона 1..5" << std::endl;
        reader.RateBook(*witcher, 6); 
        reader.RateBook(*witcher, 5); 

        std::cout << "\nПроверка правила: покупка снятой с продажи книги" << std::endl;
        reader.BuyBook(*thedarktower);
        reader.BuyBook(*witcher);   

        std::cout << "\nФормирование рекомендаций" << std::endl;
        reader.RequestRecommendations(candidates, 3);
        reader.PrintStatus();

        std::cout << "\nВыход из блока: уничтожение читателя" << std::endl;
    }

    std::cout << "\n8. Проверка агрегации: книги живы после уничтожения читателя" << std::endl;
    std::cout << "Книга существует: " << witcher->GetTitle() << std::endl;
    dune->Print();

    std::cout << "\n9. Демонстрация недостатка данных" << std::endl;
    {
        Reader newbie("Новый читатель");
        newbie.RequestRecommendations(candidates, 3);
    }

    delete witcher;
    delete dune;
    delete thedarktower;
    delete dynamicBook;
    delete[] shelf;

    return 0;
}