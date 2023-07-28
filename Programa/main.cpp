#include <iostream>

#include "Servidor.hpp"
#include "Produto.hpp"
#include "Funcionario.hpp"
#include "Fornecedor.hpp"
#include "Menus.hpp"

using namespace sistema; //namespace do sistema

int main()
{
    Servidor *servidor = new Servidor;
    int opcao{1};

    while (opcao != 0)
    {
        imprimirMenuPrincipal();
        std::cin >> opcao;
        //system("clear");

        switch (opcao)
        {
            case 0:
                break;
            case 1:
                servidor->comprarProduto();
                break;
            case 2:
                servidor->venderProduto();
                break;
            case 3:
                while (opcao != 0)
                {
                    imprimirMenuCadastro();
                    std::cin >> opcao;
                    //system("clear");

                    switch (opcao)
                    {
                        case 0:
                            break;
                        case 1:
                            servidor->cadastrarProduto();
                            break;
                        case 2:
                            servidor->descadastrarProduto();
                            break;
                        case 3:
                            servidor->cadastrarFornecedor();
                            break;
                        case 4:
                            servidor->descadastrarFornecedor();
                            break;
                        case 5:
                            servidor->cadastrarFuncionario();
                            break;
                        case 6:
                            servidor->descadastrarFuncionario();
                            break;
                        case 7:
                            servidor->cadastrarProdutoEmFornecedor();
                            break;
                        case 8:
                            servidor->descadastrarProdutoEmFornecedor();
                            break;
                        default:
                            std::cout << "Opção inválida" << std::endl;
                            break;
                    }
                }
                opcao = 1;
                break;
            case 4:
                while (opcao != 0)
                {
                    imprimirMenuRelatorios();
                    std::cin >> opcao;
                    //system("clear");

                    switch (opcao)
                    {
                        case 0:
                            break;
                        case 1:
                            servidor->listarProdutos();
                            break;
                        case 2:
                            servidor->listarFornecedores();
                            break;
                        case 3:
                            servidor->listarFuncionarios();
                            break;
                        case 4:
                            servidor->listarProdutosPorFornecedor();
                            break;
                        case 5:
                            servidor->listarFornecedoresPorProduto();
                            break;
                        case 6:
                            servidor->listarEstoqueBaixo();
                            break;
                        case 7:
                            servidor->gerarRelatorioCompras();
                            break;
                        case 8:
                            servidor->gerarRelatorioVendas();
                            break;
                        default:
                            std::cout << "Opção inválida" << std::endl;
                            break;
                    }
                }
                opcao = 1;
                break;
            case 5:
                servidor->pagarFuncionarios();
                break;
            case 6:
                servidor->mostrarSaldo();
                break;
            default:
                std::cout << "Opção inválida" << std::endl;
                break;
        }
    }

    delete servidor;

    return 0;
}