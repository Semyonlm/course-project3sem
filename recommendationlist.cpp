#include "recommendationlist.hpp"

#include "book.hpp"

#include <iostream>

namespace bookstore
{

    RecommendationList::RecommendationList()
    {
        m_books = new Book * [MAX_SIZE];
        m_capacity = MAX_SIZE;

        std::cout << "Рекомендательный список создан (владелец: " << m_ownerName << ")" << std::endl;
    }

    RecommendationList::RecommendationList(std::string_view ownerName)
        : m_ownerName{ ownerName }
    {
        m_books = new Book * [MAX_SIZE];
        m_capacity = MAX_SIZE;

        std::cout << "Рекомендательный список создан (владелец: " << m_ownerName << ")" << std::endl;
    }

    RecommendationList::~RecommendationList()
    {
        delete[] m_books;
        m_books = nullptr;

        std::cout << "Рекомендательный список уничтожен (владелец: " << m_ownerName << ")" << std::endl;
    }

    bool RecommendationList::AddBook(Book* book)
    {
        if (book == nullptr)
        {
            std::cout << "Ошибка: нельзя добавить пустую книгу в рекомендации." << std::endl;
            return false;
        }

        if (m_size >= m_capacity)
        {
            std::cout << "Ошибка: рекомендательный список заполнен (максимум "
                << MAX_SIZE << " книг)." << std::endl;
            return false;
        }

        if (Contains(book))
        {
            std::cout << "Ошибка: книга \"" << book->GetTitle()
                << "\" уже есть в рекомендациях." << std::endl;
            return false;
        }

        if (!book->IsAvailable())
        {
            std::cout << "Ошибка: книга \"" << book->GetTitle()
                << "\" снята с продажи и не может быть рекомендована." << std::endl;
            return false;
        }

        m_books[m_size++] = book;
        return true;
    }

    void RecommendationList::Clear()
    {
        m_size = 0;
    }

    std::size_t RecommendationList::GetSize() const
    {
        return m_size;
    }

    bool RecommendationList::Contains(const Book* book) const
    {
        for (std::size_t i = 0; i < m_size; ++i)
        {
            if (m_books[i] == book)
            {
                return true;
            }
        }

        return false;
    }

    void RecommendationList::Print() const
    {
        if (m_size == 0)
        {
            std::cout << "  (рекомендаций нет)" << std::endl;
            return;
        }

        for (std::size_t i = 0; i < m_size; ++i)
        {
            const Book* book = m_books[i];
            std::cout << "  - " << book->GetTitle()
                << " (" << book->GetGenre() << ")" << std::endl;
        }
    }

} // namespace bookstore