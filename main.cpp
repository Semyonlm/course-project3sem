#include "book.hpp"
#include "reader.hpp"
#include <iostream>
#include <memory>
#include <windows.h> 

using namespace bookstore;

void RunScenario()
{
    std::cout << "\nСценарий магазина\n";

    auto witcher = std::make_shared<Book>("Ведьмак", "Сапковский", "Фэнтези", 2);
    auto dune = std::make_shared<Book>("Дюна", "Герберт", "Фантастика", 1);

    std::cout << "\nСоздание читателя\n";
    {
        Reader reader("Иван");

        std::cout << "\nПроверка правил\n";
        reader.RateBook(*witcher, 6);
        reader.RateBook(*witcher, 4);

        std::cout << "\nПокупка книг\n";
        reader.BuyBook(witcher);
        reader.BuyBook(witcher);

        std::cout << "\nФормирование рекомендаций\n";
        auto candidates = std::make_unique<std::shared_ptr<Book>[]>(2);
        candidates[0] = witcher;
        candidates[1] = dune;

        reader.RequestRecommendations(candidates.get(), 2);
        reader.PrintStatus();

        std::cout << "\nПроверка weak_ptr (Книга удаляется) \n";
        std::cout << "Удаляем книгу 'Дюна' из памяти (dune.reset)...\n";
        dune.reset(); 

        reader.PrintStatus();

    } 

    std::cout << "\nЧитатель уничтожен. Но книга 'Ведьмак' жива (Агрегация)\n";
    std::cout << "Книга жива: " << witcher->GetTitle() << "\n";
}

void DemoMemory()
{
    std::cout << "\nДемонстрация памяти (Умные указатели)\n";

    std::cout << "\nСтатическая инициализация\n";
    {
        Book stackBook("Мастер и Маргарита", "Булгаков", "Роман", 3);
        std::cout << "Книга на стеке: " << stackBook.GetTitle() << "\n";
    } 

    std::cout << "\nunique_ptr: один владелец и std::move\n";
    {
        auto owner1 = std::make_unique<Book>("Война и мир", "Толстой", "Роман", 1);
        std::cout << "Владелец 1: " << owner1->GetTitle() << "\n";

        auto owner2 = std::move(owner1); 
        if (!owner1) {
            std::cout << "owner1 пуст: владение успешно передано.\n";
        }
        std::cout << "Владелец 2: " << owner2->GetTitle() << "\n";
    } 

    std::cout << "\nshared_ptr: счетчик владельцев\n";
    {
        auto sharedBook = std::make_shared<Book>("1984", "Оруэлл", "Антиутопия", 2);
        std::cout << "Владельцев: " << sharedBook.use_count() << "\n";
        {
            auto bookCopy = sharedBook; 
            std::cout << "Владельцев после копии: " << sharedBook.use_count() << "\n"; 
        } 
        std::cout << "Владельцев после выхода из блока: " << sharedBook.use_count() << "\n"; 
    }

    std::cout << "\nДинамический массив объектов\n";
    {
        auto shelf = std::make_unique<Book[]>(2);
        shelf[0].SetTitle("Преступление и наказание");
        shelf[1].SetTitle("Идиот");
        std::cout << "Массив книг: " << shelf[0].GetTitle() << ", " << shelf[1].GetTitle() << "\n";
    } 
    std::cout << "\nМассив динамических объектов\n";
    {
        auto dynShelf = std::make_unique<std::shared_ptr<Book>[]>(2);
        dynShelf[0] = std::make_shared<Book>("Гарри Поттер", "Роулинг", "Фэнтези", 5);
        dynShelf[1] = std::make_shared<Book>("Хоббит", "Толкин", "Фэнтези", 3);
        std::cout << "Указатели на книги: " << dynShelf[0]->GetTitle() << ", " << dynShelf[1]->GetTitle() << "\n";
    } 
}

int main()
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL, "Russian");

    std::cout << "Лабораторная работа №3\n";
    std::cout << "Управляемая память и умные указатели\n";

    RunScenario();
    DemoMemory();

    std::cout << "\nКонец программы\n";
    return 0;
}