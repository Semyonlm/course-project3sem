#include "EBook.hpp"

namespace bookstore {

    EBook::EBook(std::string_view title, std::shared_ptr<Author> author, double size)
        : BaseProduct{ title, std::move(author) }
        , m_fileSizeMb{ size }
    {
        std::cout << "EBook конструктор: " << GetTitle() << "\n";
    }

    EBook::~EBook() {
        std::cout << "EBook деструктор: " << GetTitle() << "\n";
    }

    std::string EBook::Describe() const {
        return "Электронная книга \"" + std::string(GetTitle()) + "\" | Размер: " + std::to_string(m_fileSizeMb) + " МБ";
    }

    std::unique_ptr<BaseProduct> EBook::Clone() const {
        return std::make_unique<EBook>(*this); 
    }

} // namespace bookstore