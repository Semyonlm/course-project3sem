#pragma once
#include "BaseProduct.hpp"

namespace bookstore {

    class EBook final : public BaseProduct { 
    private:
        double m_fileSizeMb;

    public:
        EBook(std::string_view title, std::shared_ptr<Author> author, double size);
        ~EBook() override;

        [[nodiscard]] std::string GetFormat() const override { return "Электронная"; }
        [[nodiscard]] std::string Describe() const override;
        [[nodiscard]] std::unique_ptr<BaseProduct> Clone() const override;
    };

} // namespace bookstore