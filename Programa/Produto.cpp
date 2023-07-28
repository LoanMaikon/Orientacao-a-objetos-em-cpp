#include "Produto.hpp"
#include "Fornecedor.hpp"

#include <iostream>

using namespace sistema; //namespace

Produto::Produto(){}

Produto::Produto(const int valor, const int estoque, const std::string codigoBarras)
{
	this->setValor(valor);
	this->setEstoque(estoque);
	this->setCodigoBarras(codigoBarras);
}

Produto::~Produto()
{
    this->excluirFornecedores();
}

int Produto::getValor() const
{
    return this->valor;
}
        
void Produto::setValor(const int valor)
{
    this->valor = valor;
}

int Produto::getEstoque() const
{
    return this->estoque;
}
        
void Produto::setEstoque(const int estoque)
{
    this->estoque = estoque;
}

std::string Produto::getCodigoBarras() const
{
    return this->codigoBarras;
}
        
void Produto::setCodigoBarras(const std::string codigoBarras)
{
    if (! validarCodigoBarras(codigoBarras))
		throw CodigoBarrasInvalidoException{codigoBarras};

	this->codigoBarras = codigoBarras;
}

bool Produto::validarCodigoBarras(const std::string codigoBarras) const
{
    if (codigoBarras.length() != 13)
        return false;
    return true;
}

/* adiciona fornecedor no vetor de fornecedores do produto */
void Produto::adicionarFornecedor(Fornecedor *fornecedor)
{
    /* colocando fornecedor no vetor de fornecedores do produto */
    this->fornecedores.push_back(fornecedor);

    /* colocando produto no vetor de produtos do fornecedor passado */
    fornecedor->produtos.push_back(this);
}

/* exclui fornecedor do vetor de fornecedores do produto */
/* exclui produto do vetor de produtos de cada fornecedor do produto */
void Produto::excluirFornecedor(const std::string cnpj)
{
    std::list<Fornecedor*>::iterator it; //fornecedores
    std::list<Produto*>::iterator aux; //produtos de um fornecedor

    /* encontrando fornecedor cujo cnpj foi passado como parâmetro */
    it = this->fornecedores.begin();
    while (it != this->fornecedores.end() && (*it)->cnpj != cnpj)
        it++;
    
    /* fornecedor não encontrado */
    if (it == this->fornecedores.end())
    {
        std::cout << "Fornecedor não vende esse produto" << std::endl;
        return;
    }

    /* apontando aux para o produto no vetor de produtos do fornecedor */
    aux = (*it)->produtos.begin();
    while (aux != (*it)->produtos.end() && (*aux)->getCodigoBarras() != this->getCodigoBarras())
        aux++;
    
    /* produto não encontrado */
    if (aux == (*it)->produtos.end())
    {
        std::cout << "Produto não ofertado pelo fornecedor" << std::endl;
        return;
    }

    /* apagando produto do vetor de produtos de um fornecedor */
    aux = (*it)->produtos.erase(aux);

    /* apagando fornecedor do vetor de fornecedores do produto */
    it = this->fornecedores.erase(it);
}

std::list<Fornecedor*> &Produto::getFornecedores()
{
    return this->fornecedores;
}

/* exclui fornecedores do vetor de fornecedores do produto */
/* exclui produto do vetor de produtos de cada fornecedor do produto */
void Produto::excluirFornecedores()
{
    std::list<Fornecedor*>::iterator it; //iterar por fornecedores do produto
    std::list<Produto*>::iterator aux; //iterar por produtos do fornecedor (*it)

    /* it itera por todos os fornecedores do produto */
    for (it = this->fornecedores.begin(); it != this->fornecedores.end(); it++)
    {
        /* aux itera pelo vetor de produtos do fornecedor (*it) */
        aux = (*it)->produtos.begin();

        /* apontando aux para o produto certo no vetor de produtos do fornecedor (*it) */
        while (aux != (*it)->produtos.end() && (*aux)->getCodigoBarras() != this->codigoBarras)
            aux++;

        /* tirando produto do vetor de produtos do fornecedor (*it) */
        aux = (*it)->produtos.erase(aux);
    }

    /* limpando o vetor de fornecedores do produto */
    this->fornecedores.clear();
}

bool Produto::operator==(const Produto &produto) const
{
    return this->codigoBarras == produto.codigoBarras;
}

bool Produto::operator!=(const Produto &produto) const
{
    return this->codigoBarras != produto.codigoBarras;
}

void Produto::imprimirFornecedoresPorProduto()
{
    std::list<Fornecedor*>::const_iterator aux; //para iterar nos fornecedores do produto

    std::cout << "Código de barras do produto: " << this->getCodigoBarras() << std::endl;

    /* se vetor de fornecedores do produto this está vazio, imprime "nenhum fornecedor" */
    if (this->getFornecedores().empty())
        std::cout << "Nenhum fornecedor" << std::endl << std::endl;

    /* caso contrário, imprime os fornecedores */
    for (aux = this->getFornecedores().begin(); aux != this->getFornecedores().end(); aux++)
            std::cout << "CNPJ: " << (*aux)->getCNPJ() << std::endl;
}

void Produto::imprimirProduto()
{
    std::cout << "Código de barras do produto: " << this->getCodigoBarras() << std::endl;
    std::cout << "Valor do produto: " << this->getValor() << std::endl;
    std::cout << "Estoque do produto: " << this->getEstoque() << std::endl << std::endl;
}