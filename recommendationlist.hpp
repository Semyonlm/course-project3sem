#pragma once

#include <cstddef>
#include <string>
#include <string_view>

namespace bookstore
{

    class Book;

    class RecommendationList
    {
    public:
        static constexpr std::size_t MAX_SIZE = 5;

        RecommendationList();
        explicit RecommendationList(std::string_view ownerName);
        ~RecommendationList();

        RecommendationList(const RecommendationList&) = delete;
        RecommendationList(RecommendationList&&) = delete;
        RecommendationList& operator=(const RecommendationList&) = delete;
        RecommendationList& operator=(RecommendationList&&) = delete;

        bool AddBook(Book* book);

        void Clear();
        [[nodiscard]] std::size_t GetSize() const;
        [[nodiscard]] bool Contains(const Book* book) const;

        void Print() const;

    private:
        std::string m_ownerName{ "Без владельца" };
        Book** m_books{ nullptr };
        std::size_t m_size{ 0 };
        std::size_t m_capacity{ 0 };
    };

} // namespace bookstore