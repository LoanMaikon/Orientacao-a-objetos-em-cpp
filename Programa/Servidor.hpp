#ifndef SERVIDOR_H
#define SERVIDOR_H

#include "Fornecedor.hpp"
#include "Funcionario.hpp"
#include "Produto.hpp"
#include "Menus.hpp"
#include "CPFInvalidoException.hpp"
#include "CNPJInvalidoException.hpp"
#include "CodigoBarrasInvalidoException.hpp"

namespace sistema
{

class Servidor
{
    public:
        Servidor();
        virtual ~Servidor();

        void venderProduto();
        void comprarProduto();

        void cadastrarProduto();
        void descadastrarProduto();

        void cadastrarFornecedor();
        void descadastrarFornecedor();

        void cadastrarFuncionario();
        void descadastrarFuncionario();

        void mostrarSaldo() const;

        void listarProdutos() const;
        void listarFornecedores() const;
        void listarFuncionarios() const;

        void cadastrarProdutoEmFornecedor();
        void descadastrarProdutoEmFornecedor();

        void listarProdutosPorFornecedor() const;
        void listarFornecedoresPorProduto() const;

        void listarEstoqueBaixo() const;

        void gerarRelatorioVendas() const;
        void gerarRelatorioCompras() const;

        void pagarFuncionarios();

    private:
        std::list<Funcionario*> funcionarios;
        std::list<Produto*> produtos;
        std::list<Fornecedor*> fornecedores;

        std::list<Produto*> compras;
        std::list<Produto*> vendas;

        static int saldo;
        constexpr static int estoqueBaixo{5};
};

} //namespace sistema

#endif