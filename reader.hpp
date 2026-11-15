#pragma once
#include "recommendationlist.hpp"
#include <string>
#include <string_view>
#include <memory>

namespace bookstore 
{
    class Book;

    class Reader {
    public:
        Reader();
        explicit Reader(std::string_view name);
        ~Reader() = default;

        void RateBook(Book& book, int rating);
        bool BuyBook(const std::shared_ptr<Book>& book);
        void RequestRecommendations(const std::shared_ptr<Book>* candidates, std::size_t count);
        void PrintStatus() const;

    private:
        bool IsPurchased(std::string_view title) const;
        void AddPurchasedTitle(std::string_view title);

        std::string m_name{ "Без имени" };
        RecommendationList m_recommendations; 

        std::unique_ptr<std::string[]> m_purchasedTitles{ nullptr };
        std::size_t m_purchasedCount{ 0 };
        std::size_t m_purchasedCapacity{ 0 };

        bool m_hasActivity{ false };
    };
} 