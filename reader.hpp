#pragma once

#include "recommendationlist.hpp"

#include <cstddef>
#include <string>
#include <string_view>

namespace bookstore
{

    class Book;

    class Reader
    {
    public:
        Reader();
        explicit Reader(std::string_view name);
        ~Reader();

        Reader(const Reader&) = delete;
        Reader(Reader&&) = delete;
        Reader& operator=(const Reader&) = delete;
        Reader& operator=(Reader&&) = delete;

        void RateBook(Book& book, int rating);
        bool BuyBook(Book& book);
        void RequestRecommendations(Book* const* candidates, std::size_t count);

        void PrintStatus() const;

        [[nodiscard]] const RecommendationList& GetRecommendations() const;

    private:
        [[nodiscard]] bool IsPurchased(std::string_view title) const;
        void AddPurchasedTitle(std::string_view title);

        std::string m_name{ "Без имени" };
        RecommendationList m_recommendations; 

        std::string* m_purchasedTitles{ nullptr };
        std::size_t m_purchasedCount{ 0 };
        std::size_t m_purchasedCapacity{ 0 };

        bool m_hasActivity{ false };
    };

} // namespace bookstore