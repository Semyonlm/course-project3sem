#include "PaperBook.hpp"

namespace bookstore {

    PaperBook::PaperBook(std::string_view title, std::shared_ptr<Author> author, int stock)
        : BaseProduct{ title, std::move(author) } 
        , m_stock{ stock }
    {
        std::cout << "PaperBook конструктор: " << GetTitle() << "\n";
    }

    PaperBook::PaperBook(const PaperBook& other)
        : BaseProduct{ other.GetTitle(), std::make_shared<Author>(*other.m_author) } 
        , m_stock{ other.m_stock }
    {
        std::cout << "PaperBook конструктор копирования: " << GetTitle() << "\n";
    }

    PaperBook::~PaperBook() {
        std::cout << "PaperBook деструктор: " << GetTitle() << "\n";
    }

    std::string PaperBook::Describe() const {
        return BaseProduct::Describe() + " | Наличие на складе: " + std::to_string(m_stock) + " шт.";
    }

    std::unique_ptr<BaseProduct> PaperBook::Clone() const {
        return std::make_unique<PaperBook>(*this);
    }

} // namespace bookstore