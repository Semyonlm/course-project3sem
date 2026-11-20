#pragma once
#include "BaseProduct.hpp"

namespace bookstore {

    class PaperBook : public BaseProduct {
    private:
        int m_stock;

    public:
        PaperBook(std::string_view title, std::shared_ptr<Author> author, int stock);

        PaperBook(const PaperBook& other);

        PaperBook& operator=(const PaperBook&) = delete; 
        PaperBook(PaperBook&&) noexcept = default;
        PaperBook& operator=(PaperBook&&) noexcept = default;
        ~PaperBook() override;

        [[nodiscard]] std::string GetFormat() const override { return "Печатная"; }

        [[nodiscard]] std::string Describe() const override;

        [[nodiscard]] std::unique_ptr<BaseProduct> Clone() const override;
    };

} // namespace bookstore