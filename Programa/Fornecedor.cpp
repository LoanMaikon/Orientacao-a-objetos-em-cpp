#include "Fornecedor.hpp"

#include <iostream>

using namespace sistema; //namespace

Fornecedor::Fornecedor(){}

Fornecedor::Fornecedor(const std::string nome, const std::string cnpj)
{
    this->setNome(nome);
    this->setCNPJ(cnpj);
}

Fornecedor::~Fornecedor()
{
    this->excluirProdutos();
}

std::string Fornecedor::getNome() const
{
    return this->nome;
}
        
void Fornecedor::setNome(const std::string nome)
{
    this->nome = nome;
}

std::string Fornecedor::getCNPJ() const
{
    return this->cnpj;
}
        
void Fornecedor::setCNPJ(const std::string cnpj)
{
    if (! validarCNPJ(cnpj))
		throw CNPJInvalidoException{cnpj};

	this->cnpj = cnpj;
}

bool Fornecedor::validarCNPJ(const std::string cnpj)
{
    if (cnpj.length() != 14)
        return false;
    return true;
}

std::list<Produto*> &Fornecedor::getProdutos()
{
    return this->produtos;
}

/* limpa o vetor de produtos do fornecedor */
/* tira o fornecedor do vetor de fornecedores de cada produto */ 
void Fornecedor::excluirProdutos()
{
    std::list<Produto*>::iterator it; //iterar no vetor de produtos do fornecedor
    std::list<Fornecedor*>::iterator aux; //iterar no vetor de fornecedores do produto (*it)

    /* it itera no vetor de produtos do fornecedor */
    for (it = this->produtos.begin(); it != this->produtos.end(); it++)
    {
        /* apontando aux para o início do vetor de fornecedores do produto (*it) */
        aux = (*it)->getFornecedores().begin();

        /* apontando aux para o fornecedor no vetor de fornecedores do produto (*it) */
        while (aux != (*it)->getFornecedores().end() && (*aux)->getCNPJ() != this->cnpj)
            aux++;

        /* tirando o fornecedor do vetor de fornecedores do produto (*it) */
        aux = (*it)->getFornecedores().erase(aux);
    }

    /* limpando o vetor de produtos do fornecedor */
    this->produtos.clear();
}

bool Fornecedor::operator==(const Fornecedor &fornecedor) const
{
    return this->cnpj == fornecedor.cnpj;
}

bool Fornecedor::operator!=(const Fornecedor &fornecedor) const
{
    return this->cnpj != fornecedor.cnpj;
}

void Fornecedor::imprimirProdutosPorFornecedor()
{
    std::list<Produto*>::const_iterator aux; //para iterar nos produtos do fornecedor

    std::cout << "CNPJ do fornecedor: " << this->getCNPJ() << std::endl;

    /* se vetor de produtos do fornecedor this está vazio, imprime "nenhum produto" */
    if (this->getProdutos().empty())
        std::cout << "Nenhum produto" << std::endl << std::endl;

    /* caso contrário, imprime os produtos */
    for (aux = this->getProdutos().begin(); aux != this->getProdutos().end(); aux++)
            std::cout << "Código de barras: " << (*aux)->getCodigoBarras() << std::endl;
}

void Fornecedor::imprimirFornecedor()
{
    std::cout << "Nome do fornecedor: " << this->getNome() << std::endl;
    std::cout << "CNPJ do fornecedor: " << this->getCNPJ() << std::endl << std::endl;
}