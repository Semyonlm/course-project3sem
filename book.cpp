#include "book.hpp"

#include <iostream>
#include <string>

namespace bookstore
{

    Book::Book()
    {
        std::cout << "Книга создана (по умолчанию): " << m_title << std::endl;
    }

    Book::Book(std::string_view title, std::string_view author, std::string_view genre, int stock, bool available)
        : m_title{ title }
        , m_author{ author }
        , m_genre{ genre }
        , m_stock{ stock }
        , m_available{ available }
    {
        if (m_stock < 0)
        {
            std::cout << "Ошибка: количество экземпляров не может быть отрицательным. Установлено 0." << std::endl;
            m_stock = 0;
        }

        std::cout << "Книга создана: " << m_title << std::endl;
    }

    Book::~Book()
    {
        std::cout << "Книга уничтожена: " << m_title << std::endl;
    }

    std::string_view Book::GetTitle() const
    {
        return std::string_view(m_title);
    }

    std::string_view Book::GetAuthor() const
    {
        return std::string_view(m_author);
    }

    std::string_view Book::GetGenre() const
    {
        return std::string_view(m_genre);
    }

    int Book::GetRating() const
    {
        return m_rating;
    }

    int Book::GetStock() const
    {
        return m_stock;
    }

    bool Book::IsAvailable() const
    {
        return m_available;
    }

    void Book::SetTitle(std::string_view title)
    {
        m_title = std::string(title);
    }

    void Book::SetAuthor(std::string_view author)
    {
        m_author = std::string(author);
    }

    void Book::SetGenre(std::string_view genre)
    {
        m_genre = std::string(genre);
    }

    void Book::SetStock(int stock)
    {
        if (stock < 0)
        {
            std::cout << "Ошибка: наличие не может быть отрицательным." << std::endl;
            return;
        }
        m_stock = stock;
    }

    bool Book::SetRating(int rating)
    {
        if (rating < 1 || rating > 5)
        {
            std::cout << "Ошибка: оценка книги \"" << m_title
                << "\" должна быть целым числом от 1 до 5. Получено: " << rating << std::endl;
            return false;
        }

        m_rating = rating;
        return true;
    }

    void Book::WithdrawFromSale()
    {
        m_available = false;
        std::cout << "Книга \"" << m_title << "\" снята с продажи." << std::endl;
    }

    void Book::Print() const
    {
        const std::string ratingStr = (m_rating == 0) ? std::string("нет") : std::to_string(m_rating);

        std::cout << "Книга: \"" << m_title << "\""
            << " | Автор: " << m_author
            << " | Жанр: " << m_genre
            << " | Рейтинг: " << ratingStr
            << " | Наличие: " << m_stock
            << " | Доступна: " << (m_available ? "да" : "нет")
            << std::endl;
    }

} // namespace bookstore