#pragma once
#include <string>
#include <string_view>
#include <memory>
#include <iostream>

namespace bookstore {
    class Author {
    public:
        std::string name;
        Author(std::string_view n) : name(n) { std::cout << "  [Author создан: " << name << "]\n"; }
        ~Author() { std::cout << "  [Author уничтожен: " << name << "]\n"; }
    };

    class BaseProduct {
    protected:

        [[nodiscard]] std::string Header() const {
            return "Товар #" + std::to_string(m_id) + ": \"" + m_title + "\" (Автор: " + m_author->name + ")";
        }

        std::shared_ptr<Author> m_author; 

    private:
        inline static int m_nextId = 1; 
        int m_id;
        std::string m_title;

    public:
        BaseProduct(std::string_view title, std::shared_ptr<Author> author);

        virtual ~BaseProduct() = default;

        [[nodiscard]] int GetId() const { return m_id; }
        [[nodiscard]] std::string_view GetTitle() const { return m_title; }

        [[nodiscard]] virtual std::string GetFormat() const = 0;
        [[nodiscard]] virtual std::string Describe() const {
            return Header() + " | Формат: " + GetFormat();
        }

        [[nodiscard]] virtual std::unique_ptr<BaseProduct> Clone() const = 0;
    };

} // namespace bookstore