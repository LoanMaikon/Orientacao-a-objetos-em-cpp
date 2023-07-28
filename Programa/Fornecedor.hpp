#ifndef FORNECEDOR_H
#define FORNECEDOR_H

#include <list>
#include <string>

#include "Produto.hpp"
#include "CNPJInvalidoException.hpp"

namespace sistema
{

class Fornecedor
{
    friend class Produto; //Produto acessa dados privados de Fornecedor

    public:
        Fornecedor();
        explicit Fornecedor(const std::string nome, const std::string cnpj);
        virtual ~Fornecedor();

        std::string getNome() const;
        void setNome(const std::string nome);

        std::string getCNPJ() const;
        void setCNPJ(const std::string cnpj);

        std::list<Produto*> &getProdutos();

        void excluirProdutos();

        bool operator==(const Fornecedor &fornecedor) const; //sobrecarga e operador
        bool operator!=(const Fornecedor &fornecedor) const; //sobrecarga e operador

        void imprimirProdutosPorFornecedor();
        void imprimirFornecedor();

    private:
        bool validarCNPJ(const std::string cnpj);

        std::string nome;
        std::string cnpj;
        std::list<Produto*> produtos;
};

} // namespace sistema

#endif