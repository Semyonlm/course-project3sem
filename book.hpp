#pragma once

#include <string>
#include <string_view>

namespace bookstore
{

    class Book
    {
    public:
        Book();
        Book(std::string_view title, std::string_view author, std::string_view genre, int stock, bool available = true);
        ~Book();

        Book(const Book&) = delete;
        Book(Book&&) = delete;
        Book& operator=(const Book&) = delete;
        Book& operator=(Book&&) = delete;

        [[nodiscard]] std::string_view GetTitle() const;
        [[nodiscard]] std::string_view GetAuthor() const;
        [[nodiscard]] std::string_view GetGenre() const;
        [[nodiscard]] int GetRating() const;
        [[nodiscard]] int GetStock() const;
        [[nodiscard]] bool IsAvailable() const;

        void SetTitle(std::string_view title);
        void SetAuthor(std::string_view author);
        void SetGenre(std::string_view genre);
        void SetStock(int stock);

        bool SetRating(int rating);

        void WithdrawFromSale();

        void Print() const;

    private:
        std::string m_title{ "Без названия" };
        std::string m_author{ "Неизвестен" };
        std::string m_genre{ "Не определён" };
        int m_rating{ 0 };
        int m_stock{ 0 };
        bool m_available{ true };
    };

} // namespace bookstore