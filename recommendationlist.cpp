#include "recommendationlist.hpp"
#include "book.hpp"
#include <iostream>

namespace bookstore {

    RecommendationList::RecommendationList() {
        m_books = std::make_unique<std::weak_ptr<Book>[]>(MAX_SIZE);
        std::cout << "Рекомендательный список создан (владелец: " << m_ownerName << ")" << std::endl;
    }
    RecommendationList::RecommendationList(std::string_view ownerName) : m_ownerName{ ownerName } {
        m_books = std::make_unique<std::weak_ptr<Book>[]>(MAX_SIZE);
        std::cout << "Рекомендательный список создан (владелец: " << m_ownerName << ")" << std::endl;
    }
    bool RecommendationList::AddBook(const std::shared_ptr<Book>& book) {
        if (!book) return false;
        if (m_size >= MAX_SIZE) {
            std::cout << "Ошибка: список заполнен." << std::endl;
            return false;
        }
        if (!book->IsAvailable()) {
            std::cout << "Ошибка: книга \"" << book->GetTitle() << "\" снята с продажи." << std::endl;
            return false;
        }
        m_books[m_size] = book;
        m_size++;
        return true;
    }

    void RecommendationList::Clear() {
        m_size = 0;
    }
    std::size_t RecommendationList::GetSize() const {
        return m_size;
    }

    void RecommendationList::Print() const {
        if (m_size == 0) {
            std::cout << "  (рекомендаций нет)" << std::endl;
            return;
        }
        for (std::size_t i = 0; i < m_size; ++i) {
            if (auto book = m_books[i].lock()) {
                std::cout << "  - " << book->GetTitle() << std::endl;
            }
            else {
                std::cout << "  - [Книга была удалена из памяти]" << std::endl;
            }
        }
    }
}