#include "BaseProduct.hpp"
#include "PaperBook.hpp"
#include "EBook.hpp"
#include "book.hpp"
#include "reader.hpp"
#include <iostream>
#include <memory>
#include <windows.h> 

using namespace bookstore;

void DemoInheritance() {
    std::cout << "\nЛР 4: Наследование\n";

    auto author = std::make_shared<Author>("Дж. Роулинг");

    std::cout << "\nСоздание объектов\n";
    PaperBook paperBook("Гарри Поттер и философский камень", author, 5);
    EBook eBook("Гарри Поттер (электронная)", author, 2.5);

    std::cout << "\nПолиморфизм\n";
    std::unique_ptr<BaseProduct> item1 = std::make_unique<PaperBook>("Ведьмак", author, 10);
    std::unique_ptr<BaseProduct> item2 = std::make_unique<EBook>("Ведьмак (аудио)", author, 150.0);

    std::cout << item1->Describe() << "\n";
    std::cout << item2->Describe() << "\n";

    std::cout << "\nКопирование\n";
    std::cout << "До копирования: " << author->name << "\n";
    PaperBook original("Мастер и Маргарита", std::make_shared<Author>("Булгаков"), 3);

    PaperBook copy = original;
    std::cout << "После глубокого копирования: \n";
    std::cout << "Original: " << original.Describe() << "\n";
    std::cout << "Copy:     " << copy.Describe() << "\n";

    std::cout << "\nКлонирование через Clone()\n";
    std::unique_ptr<BaseProduct> cloned = item2->Clone();
    std::cout << "Клон: " << cloned->Describe() << "\n";

    std::cout << "\nРабота со строками\n";
    std::string title = "Мастер и Маргарита";
    std::size_t pos = title.find("Маргарита");
    if (pos != std::string::npos) {
        std::cout << "Найдено слово: " << title.substr(pos, 9) << "\n";
    }

    std::cout << "\nВыход из функции\n";
}
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
    DemoInheritance();
    std::cout << "\nКонец программы\n";
    return 0;
}