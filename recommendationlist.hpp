#pragma once
#include <string>
#include <string_view>
#include <memory>

namespace bookstore {
    class Book;

    class RecommendationList {
    public:
        RecommendationList();
        explicit RecommendationList(std::string_view ownerName);
        ~RecommendationList() = default;
        bool AddBook(const std::shared_ptr<Book>& book);
        void Clear();
        [[nodiscard]] std::size_t GetSize() const;
        void Print() const;

        static constexpr std::size_t MAX_SIZE = 5;

    private:
        std::string m_ownerName{ "Без владельца" };
        std::unique_ptr<std::weak_ptr<Book>[]> m_books{ nullptr };
        std::size_t m_size{ 0 };
    };
} // namespace bookstore