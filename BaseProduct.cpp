#include "BaseProduct.hpp"

namespace bookstore {

    BaseProduct::BaseProduct(std::string_view title, std::shared_ptr<Author> author)
        : m_id{ m_nextId++ }
        , m_title{ title }
        , m_author{ std::move(author) }
    {
        std::cout << "BaseProduct конструктор: " << m_title << "\n";
    }

} // namespace bookstore