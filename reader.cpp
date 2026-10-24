#include "reader.hpp"

#include "book.hpp"

#include <iostream>
#include <string>

namespace bookstore
{

    Reader::Reader()
        : Reader("Без имени")
    {
    }

    Reader::Reader(std::string_view name)
        : m_name{ name }
        , m_recommendations{ name }
    {
        std::cout << "Читатель создан: " << m_name << std::endl;
    }

    Reader::~Reader()
    {
        delete[] m_purchasedTitles;
        m_purchasedTitles = nullptr;

        std::cout << "Читатель уничтожен: " << m_name << std::endl;
    }

    void Reader::RateBook(Book& book, int rating)
    {
        if (!book.SetRating(rating))
        {
            std::cout << "Оценка не принята." << std::endl;
            return;
        }

        m_hasActivity = true;

        std::cout << "Читатель " << m_name
            << " оценил книгу \"" << book.GetTitle()
            << "\" на " << rating << " из 5." << std::endl;
    }

    bool Reader::BuyBook(Book& book)
    {
        if (!book.IsAvailable())
        {
            std::cout << "Ошибка: книга \"" << book.GetTitle()
                << "\" снята с продажи и не может быть куплена." << std::endl;
            return false;
        }

        if (IsPurchased(book.GetTitle()))
        {
            std::cout << "Ошибка: книга \"" << book.GetTitle()
                << "\" уже куплена читателем." << std::endl;
            return false;
        }

        if (book.GetStock() <= 0)
        {
            std::cout << "Ошибка: книги \"" << book.GetTitle()
                << "\" нет в наличии." << std::endl;
            return false;
        }

        AddPurchasedTitle(book.GetTitle());
        m_hasActivity = true;

        std::cout << "Читатель " << m_name
            << " купил книгу \"" << book.GetTitle() << "\"." << std::endl;
        return true;
    }

    void Reader::RequestRecommendations(Book* const* candidates, std::size_t count)
    {
        if (!m_hasActivity)
        {
            std::cout << "Недостаточно данных для персональных рекомендаций: "
                "нет покупок и оценок." << std::endl;
            return;
        }

        m_recommendations.Clear();

        for (std::size_t i = 0; i < count; ++i)
        {
            Book* book = candidates[i];
            if (book == nullptr)
            {
                continue;
            }

            if (IsPurchased(book->GetTitle()))
            {
                std::cout << "Книга \"" << book->GetTitle()
                    << "\" уже куплена и не рекомендуется." << std::endl;
                continue;
            }

            m_recommendations.AddBook(book);
        }

        std::cout << "Рекомендательный список сформирован." << std::endl;
    }

    void Reader::PrintStatus() const
    {
        std::cout << "Читатель: " << m_name << std::endl;

        std::cout << "Купленные книги:";
        if (m_purchasedCount == 0)
        {
            std::cout << " нет";
        }
        else
        {
            for (std::size_t i = 0; i < m_purchasedCount; ++i)
            {
                std::cout << " \"" << m_purchasedTitles[i] << "\"";
            }
        }
        std::cout << std::endl;

        std::cout << "Рекомендации:" << std::endl;
        m_recommendations.Print();
    }

    const RecommendationList& Reader::GetRecommendations() const
    {
        return m_recommendations;
    }

    bool Reader::IsPurchased(std::string_view title) const
    {
        for (std::size_t i = 0; i < m_purchasedCount; ++i)
        {
            if (m_purchasedTitles[i] == title)
            {
                return true;
            }
        }

        return false;
    }

    void Reader::AddPurchasedTitle(std::string_view title)
    {
        if (m_purchasedCount == m_purchasedCapacity)
        {
            const std::size_t newCapacity = (m_purchasedCapacity == 0) ? 2 : m_purchasedCapacity * 2;

            std::string* newArray = new std::string[newCapacity];
            for (std::size_t i = 0; i < m_purchasedCount; ++i)
            {
                newArray[i] = m_purchasedTitles[i];
            }

            delete[] m_purchasedTitles;
            m_purchasedTitles = newArray;
            m_purchasedCapacity = newCapacity;
        }

        m_purchasedTitles[m_purchasedCount++] = std::string(title);
    }

} // namespace bookstore