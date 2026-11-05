#include "reader.hpp"
#include "book.hpp"
#include <iostream>

namespace bookstore {
    Reader::Reader() : Reader("Без имени") {}
    Reader::Reader(std::string_view name) : m_name{ name }, m_recommendations{ name } {
        std::cout << "Читатель создан: " << m_name << std::endl;
    }

    void Reader::RateBook(Book& book, int rating) {
        if (book.SetRating(rating)) {
            m_hasActivity = true;
            std::cout << "Читатель " << m_name << " оценил \"" << book.GetTitle() << "\" на " << rating << "." << std::endl;
        }
    }

    bool Reader::BuyBook(const std::shared_ptr<Book>& book) {
        if (!book || !book->IsAvailable() || book->GetStock() <= 0 || IsPurchased(book->GetTitle())) {
            std::cout << "Ошибка покупки книги." << std::endl;
            return false;
        }
        AddPurchasedTitle(book->GetTitle());
        m_hasActivity = true;
        std::cout << "Читатель " << m_name << " купил \"" << book->GetTitle() << "\"." << std::endl;
        return true;
    }
    void Reader::RequestRecommendations(const std::shared_ptr<Book>* candidates, std::size_t count) {
        if (!m_hasActivity) {
            std::cout << "Недостаточно данных для рекомендаций." << std::endl;
            return;
        }
        m_recommendations.Clear();
        for (std::size_t i = 0; i < count; ++i) {
            if (!IsPurchased(candidates[i]->GetTitle())) {
                m_recommendations.AddBook(candidates[i]);
            }
        }
    }

    void Reader::PrintStatus() const {
        std::cout << "Читатель: " << m_name << "\nРекомендации:\n";
        m_recommendations.Print();
    }

    bool Reader::IsPurchased(std::string_view title) const {
        for (std::size_t i = 0; i < m_purchasedCount; ++i) {
            if (m_purchasedTitles[i] == title) return true;
        }
        return false;
    }

    void Reader::AddPurchasedTitle(std::string_view title) {
        if (m_purchasedCount == m_purchasedCapacity) {
            std::size_t newCapacity = (m_purchasedCapacity == 0) ? 2 : m_purchasedCapacity * 2;
            auto newArray = std::make_unique<std::string[]>(newCapacity);

            for (std::size_t i = 0; i < m_purchasedCount; ++i) {
                newArray[i] = m_purchasedTitles[i];
            }

            m_purchasedTitles = std::move(newArray);
            m_purchasedCapacity = newCapacity;
        }
        m_purchasedTitles[m_purchasedCount++] = std::string(title);
    }
}