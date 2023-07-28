#ifndef PRODUTO_H
#define PRODUTO_H

#include "CodigoBarrasInvalidoException.hpp"

#include <list>
#include <string>

namespace sistema
{

class Fornecedor;

class Produto
{
    public:
        Produto();
        explicit Produto(const int valor, const int estoque, const std::string codigoBarras);
        virtual ~Produto();
        
        int getValor() const;
        void setValor(const int valor);

        int getEstoque() const;
        void setEstoque(const int estoque);

        std::string getCodigoBarras() const;
        void setCodigoBarras(const std::string codigoBarras);

        std::list<Fornecedor*> &getFornecedores();

        void adicionarFornecedor(Fornecedor *fornecedor);
        void excluirFornecedor(const std::string cnpj);

        void excluirFornecedores();

        void imprimirFornecedoresPorProduto();
        void imprimirProduto();

        bool operator==(const Produto &produto) const; //sobrecarga e operador
        bool operator!=(const Produto &produto) const; //sobrecarga e operador

    private:
        bool validarCodigoBarras(const std::string codigoBarras) const;

        int valor;
        int estoque;
        std::string codigoBarras;
        std::list<Fornecedor*> fornecedores;
};

} // namespace sistema

#endif