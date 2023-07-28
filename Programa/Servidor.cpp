#include "Servidor.hpp"

#include <iostream>
#include <list>

using namespace sistema; //namespace

/* saldo do servidor começa em 0 */
int Servidor::saldo{0};

Servidor::Servidor(){}

Servidor::~Servidor()
{
    std::list<Produto*>::iterator it1; //para iterar no vetor de produtos do servidor
    std::list<Fornecedor*>::iterator it2; //para iterar no vetor de fornecedores do servidor
    std::list<Funcionario*>::iterator it3; //para iterar no vetor de funcionários do servidor

    /* itera no vetor de produtos do servidor */
    for (it1 = this->produtos.begin(); it1 != this->produtos.end(); it1++)
        delete (*it1); //chama destrutor
    
    /* apaga vetor de produtos do servidor */
    this->produtos.clear();

    /* itera no vetor de fornecedores do servidor */
    for (it2 = this->fornecedores.begin(); it2 != this->fornecedores.end(); it2++)
        delete (*it2); //chama destrutor
    
    /* apaga vetor de fornecedores do servidor */
    this->fornecedores.clear();

    /* itera no vetor de funcionários do servidor */
    for (it3 = this->funcionarios.begin(); it3 != this->funcionarios.end(); it3++)
        delete (*it3); //chama destrutor

    /* apaga vetor de funcionários do servidor */
    this->funcionarios.clear();

    /* itera no vetor de compras do servidor */
    for (it1 = this->compras.begin(); it1 != this->compras.end(); it1++)
        delete (*it1); //chama destrutor

    /* apaga vetor de compras do servidor */
    this->compras.clear();

    /* itera no vetor de vendas do servidor */
    for (it1 = this->vendas.begin(); it1 != this->vendas.end(); it1++)
        delete (*it1); //chama destrutor
    
    /* apaga vetor de vendas do servidor */
    this->vendas.clear();
}

/* aloca memória para um produto, lê as informações de sua venda e retorna o produto */
Produto *lerVendaProduto()
{
    Produto *produto = new Produto; //aloca memória para o produto
    int estoque;
    std::string codigoBarras;
    bool verificacao{false};

    /* cabeçalho */
    imprimirVenderProduto();

    /* recebendo a quantidade vendida do produto */
    std::cout << "Digite a quantidade vendida de produtos: ";
    std::cin >> estoque;
    produto->setEstoque(estoque);

    /* recebendo o código de barras do produto */
    while (! verificacao)
    {
        try
        {
            /* lê código de barras */
            std::cout << "Digite o código de barras: ";
            std::cin >> codigoBarras;

            produto->setCodigoBarras(codigoBarras); //tenta dar set no código de barras
            verificacao = true; //caso tenha passado pelo setCodigoBarras sem lançar exceção
        }
        catch (CodigoBarrasInvalidoException &cbe)
        {
            std::cout << "Erro de código de barras: " << cbe.what() << " " << cbe.codigoBarras << std::endl;
        }
        catch (std::exception &ex)
        {
            std::cout << "Erro: " << ex.what() << std::endl;
        }
    }

    return produto;
}

void Servidor::venderProduto()
{
    int novoEstoque;
    int valor;
    Produto *produto = lerVendaProduto(); //lendo informações de venda
    std::list<Produto*>::iterator it; //para verificar se produto existe e o estoque no servidor

    /* iterando no vetor de produtos do servidor */
    it = this->produtos.begin();
    while (it != this->produtos.end() && (*it)->getCodigoBarras() != produto->getCodigoBarras())
        it++;

    /* não encontrou o código de barras digitado na venda do produto */
    if (it == this->produtos.end())
    {
        std::cout << "Produto não cadastrado" << std::endl;
        delete produto;
        return;
    }

    /* produto encontrado, mas não tem estoque suficiente para o pedido de venda */
    if ((*it)->getEstoque() < produto->getEstoque())
    {
        std::cout << "Estoque do produto não é suficiente" << std::endl;
        delete produto;
        return;
    }

    /* copiando o valor do produto no vetor de produtos para o valor do produto vendido */
    valor = (*it)->getValor();
    produto->setValor(valor);

    /* adicionando produto criado no vetor de vendad do servidor */
    this->vendas.push_back(produto);

    /* atualizando estoque */
    novoEstoque = (*it)->getEstoque() - produto->getEstoque();
    (*it)->setEstoque(novoEstoque);

    /* atualizando saldo */
    Servidor::saldo += (produto->getEstoque() * valor);
}

/* aloca memória para um produto, lê as informações de sua compra e retorna o produto */
Produto *lerCompraProduto()
{
    Produto *produto = new Produto; //aloca memória para o produto
    int valor;
    int estoque;
    std::string codigoBarras;
    bool verificacao{false};

    /* cabeçalho */
    imprimirComprarProduto();

    /* recebendo valor de compra do produto */
    std::cout << "Digite o valor do produto: ";
    std::cin >> valor;
    produto->setValor(valor);

    /* recebendo quantidade de produtos comprados */
    std::cout << "Digite a quantidade comprada de produtos: ";
    std::cin >> estoque;
    produto->setEstoque(estoque);

    /* recebendo código de barras do produto comprado */
    /* recebendo o código de barras do produto */
    while (! verificacao)
    {
        try
        {
            /* lê código de barras */
            std::cout << "Digite o código de barras: ";
            std::cin >> codigoBarras;

            produto->setCodigoBarras(codigoBarras); //tenta dar set no código de barras
            verificacao = true; //caso tenha passado pelo setCodigoBarras sem lançar exceção
        }
        catch (CodigoBarrasInvalidoException &cbe)
        {
            std::cout << "Erro de código de barras: " << cbe.what() << " " << cbe.codigoBarras << std::endl;
        }
        catch (std::exception &ex)
        {
            std::cout << "Erro: " << ex.what() << std::endl;
        }
    }
    return produto;
}

void Servidor::comprarProduto()
{
    int novoEstoque;
    Produto *produto = lerCompraProduto(); //lendo informações de compra do produto
    std::list<Produto*>::iterator it; //para iterar no vetor de produtos do servidor

    /* procurando produto no vetor de produtos do servidor */
    it = this->produtos.begin();
    while (it != this->produtos.end() && (*it)->getCodigoBarras() != produto->getCodigoBarras())
        it++;

    /* produto não foi encontrado no vetor de produtos do servidor */
    if (it == this->produtos.end())
    {
        std::cout << "Produto não cadastrado" << std::endl;
        delete produto;
        return;
    }

    /* colocando produto no vetor de compras do servidor */
    this->compras.push_back(produto);

    /* atualizando saldo */
    Servidor::saldo += - (produto->getEstoque() * produto->getValor());

    /* atualizando estoque do produto no vetor de produtos do servidor */
    novoEstoque = (*it)->getEstoque() + produto->getEstoque();
    (*it)->setEstoque(novoEstoque);
}

/* ler informações de cadastro de um produto no vetor de produtos do servidor */
Produto *lerProduto()
{
    Produto *produto = new Produto; //alocando memória para o produto
    int valor;
    std::string codigoBarras;
    bool verificacao{false};

    /* cabeçalho */
    imprimirCadastrarProduto();

    /* recebendo valor do produto */
    std::cout << "Digite o valor do produto: ";
    std::cin >> valor;
    produto->setValor(valor);

    /* recebendo código de barras do produto */
    /* recebendo o código de barras do produto */
    while (! verificacao)
    {
        try
        {
            /* lê código de barras */
            std::cout << "Digite o código de barras: ";
            std::cin >> codigoBarras;

            produto->setCodigoBarras(codigoBarras); //tenta dar set no código de barras
            verificacao = true; //caso tenha passado pelo setCodigoBarras sem lançar exceção
        }
        catch (CodigoBarrasInvalidoException &cbe)
        {
            std::cout << "Erro de código de barras: " << cbe.what() << " " << cbe.codigoBarras << std::endl;
        }
        catch (std::exception &ex)
        {
            std::cout << "Erro: " << ex.what() << std::endl;
        }
    }

    /* iniciando estoque do produto com 0 */
    produto->setEstoque(0);

    /* retorna produto já alocado */
    return produto;
}

void Servidor::cadastrarProduto()
{
    Produto *produto = lerProduto(); //lê informações de cadastro do produto
    std::list<Produto*>::iterator it; //para iterar no vetor de produtos do servidor

    /* verifica se código de barras passado já eixste no vetor de produtos do servidor */
    it = this->produtos.begin();
    while (it != this->produtos.end() && (*it)->getCodigoBarras() != produto->getCodigoBarras())
        it++;

    if (it == this->produtos.end()) //se não existe, coloca
        this->produtos.push_back(produto);
    else //se já existe, não coloca
    {
        std::cout << "Produto com código de barras já existente" << std::endl;
        delete produto;
    }
}

/* libera memória do produto passado */
void Servidor::descadastrarProduto()
{
    std::string codigoBarras;
    std::list<Produto*>::iterator it; //para iterar no vetor de produtos do servidor

    /* cabeçalho */
    imprimirDescadastrarProduto();

    /* recebendo código de barras do produto que será descadastrado */
    std::cout << "Digite o código de barras para ser descadastrado: ";
    std::cin >> codigoBarras;

    /* apontando it para o produto no vetor de produtos do servidor */
    it = this->produtos.begin();
    while (it != this->produtos.end() && (*it)->getCodigoBarras() != codigoBarras)
        it++;

    if (it != this->produtos.end()) //achou o produto
    {
        delete (*it); //chama destrutor
        it = this->produtos.erase(it); //tira produto do vetor de produtos do servidor
    }
    else //não achou o produto
        std::cout << "Produto não cadastrado" << std::endl;
}

/* lê informações de cadastro de um fornecedor e retorna ele */
Fornecedor *lerFornecedor()
{
    Fornecedor *fornecedor = new Fornecedor; //aloca memória para fornecedor
    std::string nome;
    std::string cnpj;
    bool verificacao{false};

    /* cabeçalho */
    imprimirCadastrarFornecedor();

    /* recebendo nome do fornecedor */
    std::cout << "Digite o nome do fornecedor: ";
    std::cin >> nome;
    fornecedor->setNome(nome);

    /* recebendo CNPJ do fornecedor */
    while (! verificacao)
    {
        try
        {
            /* lê CNPJ */
            std::cout << "Digite o CNPJ: ";
            std::cin >> cnpj;

            fornecedor->setCNPJ(cnpj); //tenta dar set no CNPJ
            verificacao = true; //caso tenha passado pelo setCNPJ sem lançar exceção
        }
        catch (CNPJInvalidoException &cnpje)
        {
            std::cout << "Erro de CNPJ: " << cnpje.what() << " " << cnpje.cnpj << std::endl;
        }
        catch (std::exception &ex)
        {
            std::cout << "Erro: " << ex.what() << std::endl;
        }
    }

    /* retorna fornecedor já alocado */
    return fornecedor;
}

void Servidor::cadastrarFornecedor()
{
    Fornecedor *fornecedor = lerFornecedor(); //lendo informaçõe de cadastro do fornecedor
    std::list<Fornecedor*>::iterator it; //para iterar no vetor de fornecedores do servidor

    /* verifica se o cnpj passado já existe no vetor de fornecedores do servidor */
    it = this->fornecedores.begin();
    while (it != this->fornecedores.end() && (*it)->getCNPJ() != fornecedor->getCNPJ())
        it++;

    if (it == this->fornecedores.end()) //fornecedor ainda não existe
        this->fornecedores.push_back(fornecedor);
    else //fornecedor já existe,  não faz nada
    {
        std::cout << "Fornecedor com CNPJ já existente" << std::endl;
        delete fornecedor;
    }
}

/* desaloca memória do fornecedor e tira ele tira do vetor de fornecedores do servidor */
void Servidor::descadastrarFornecedor()
{
    std::string cnpj;
    std::list<Fornecedor*>::iterator it; //para iterar no vetor de fornecedores do servidor

    /* cabeçalho */
    imprimirDescadastrarFornecedor();

    /* recebendo cnpj do fornecedor que será descadastrado */
    std::cout << "Digite o CNPJ para ser descadastrado: ";
    std::cin >> cnpj;

    /* it aponta para o fornecedor no vetor de fornecedores do servidor */
    it = this->fornecedores.begin();
    while (it != this->fornecedores.end() && (*it)->getCNPJ() != cnpj)
        it++;

    if (it != this->fornecedores.end()) //achou fornecedor no vetor
    {
        delete (*it); //chama destrutor
        it = this->fornecedores.erase(it); //tira fornecedor do vetor de fornecedores do servidor
    }
    else //não achou fornecedor no vetor
        std::cout << "Fornecedor não cadastrado" << std::endl;
}

/* aloca memória para o funcionário e lê informações de cadastro */
Funcionario *lerFuncionario()
{
    Funcionario *funcionario = new Funcionario; //aloca memória para o funcionário
    std::string nome;
    long cpf;
    int idade;
    int salario;
    int cargo;
    bool verificacao{false};

    /* cabeçalho */
    imprimirCadastrarFuncionario();

    /* recebe nome do funcionário */
    std::cout << "Digite o nome do funcionário: ";
    std::cin >> nome;
    funcionario->setNome(nome);

    /* recebe idade do funcionário */
    std::cout << "Digite a idade do funcionário: ";
    std::cin >> idade;
    funcionario->setIdade(idade);

    /* recebe salário do funcionário */
    std::cout << "Digite o salário do funcionário: ";
    std::cin >> salario;
    funcionario->setSalario(salario);

    /* recebe o cargo do funcionário com enum */
    imprimirMenuCargo();
    std::cin >> cargo;
    funcionario->setCargo(cargo);

    /* recebe cpf do funcionário */
    while (! verificacao)
    {
        try
        {
            /* lê CPF */
            std::cout << "Digite o CPF: ";
            std::cin >> cpf;

            funcionario->setCPF(cpf); //tenta dar set no CPF
            verificacao = true; //caso tenha passado pelo setCPF sem lançar exceção
        }
        catch (CPFInvalidoException &cpfe)
        {
            std::cout << "Erro de CPF: " << cpfe.what() << " " << cpfe.cpf << std::endl;
        }
        catch (std::exception &ex)
        {
            std::cout << "Erro: " << ex.what() << std::endl;
        }
    }

    /* retorna funcionário já alocado */
    return funcionario;
}

void Servidor::cadastrarFuncionario()
{
    Funcionario *funcionario = lerFuncionario(); //lê informações de cadastro do funcionário
    std::list<Funcionario*>::iterator it; //para iterar no vetor de funcionários do servidor

    /* cabeçalho */
    imprimirCadastrarFuncionario();

    /* it verifica se funcionário já existe no vetor de funcionários do servidor */
    it = this->funcionarios.begin();
    while (it != this->funcionarios.end() && (*it)->getCPF() != funcionario->getCPF())
        it++;

    if (it == this->funcionarios.end()) //se não existe, coloca
        this->funcionarios.push_back(funcionario);
    else //se existe, não faz nada
    {
        std::cout << "Funcionário com CPF já existente" << std::endl;
        delete funcionario;
    }
}

/* desaloca memória do funcionário e tira ele do vetor de funcionários do servidor */
void Servidor::descadastrarFuncionario()
{
    long cpf;
    std::list<Funcionario*>::iterator it; //para iterar no vetor de funcionários do servidor

    /* cabeçalho */
    imprimirDescadastrarFuncionario();

    /* recebendo cpf que será descadastrado */
    std::cout << "Digite o CPF para ser descadastrado: ";
    std::cin >> cpf;

    /* it aponta para o funcionário no vetor de funcionários do servidor */
    it = this->funcionarios.begin();
    while (it != this->funcionarios.end() && (*it)->getCPF() != cpf)
        it++;

    if (it != this->funcionarios.end()) //achou o funcionário
    {
        delete (*it); //chama destrutor
        it = this->funcionarios.erase(it); //tira funcionário do vetor de funcionários do servidor
    }
    else //não achou o funcionário
        std::cout << "Funcionário não cadastrado" << std::endl;
}

/* imprime o saldo atual do servidor */
void Servidor::mostrarSaldo() const
{
    /* cabeçalho */
    imprimirMostrarSaldo();

    std::cout << "Saldo = " << this->saldo << std::endl;
}

void Servidor::listarProdutos() const
{
    int i{1}; //índice do produto
    std::list<Produto*>::const_iterator it; //para iterar no vetor de produtos do servidor

    /* cabeçalho */
    imprimirListarProdutos();

    /* itera no vetor de produtos do servidor */
    for (it = this->produtos.begin(); it != this->produtos.end(); it++)
    {
        std::cout << "Produto " << i << std::endl;
        
        /* imprimindo informações do produto */
        (*it)->imprimirProduto();

        i++; //acrescenta ao índice
    }
}

void Servidor::listarFornecedores() const
{
    int i{1}; //índice do fornecedor
    std::list<Fornecedor*>::const_iterator it; //para iterar no vetor de fornecedores do servidor

    /* cabeçalho */
    imprimirListarFornecedores();

    /* iterando  no vetor de fornecedores do servidor */
    for (it = this->fornecedores.begin(); it != this->fornecedores.end(); it++)
    {
        std::cout << "Fornecedor " << i << std::endl;
        
        /* imprimindo informações do fornecedor */
        (*it)->imprimirFornecedor();

        i++; //acrescenta ao índice
    }
}

void Servidor::listarFuncionarios() const
{
    int i{1}; //índice do funcionário
    std::list<Funcionario*>::const_iterator it; //para iterar no vetor de funcionários do servidor
    std::string cargo; //para imprimir cargo

    /* cabeçalho */
    imprimirListarFuncionarios();

    /* iterando no vetor de funcionários do servidor */
    for (it = this->funcionarios.begin(); it != this->funcionarios.end(); it++)
    {
        std::cout << "Funcionário " << i << std::endl;
        
        /* imprimindo informações do funcionário */
        (*it)->imprimirFuncionario();

        i++; //acrescenta ao índice
    }
}

/* coloca produto no vetor de produtos do fornecedor */
/* coloca fornecedor no vetor de fornecedores do produto */
void Servidor::cadastrarProdutoEmFornecedor()
{
    std::string cnpj;
    std::string codigoBarras;
    std::list<Produto*>::iterator it; //para iterar no vetor de produtos do servidor
    std::list<Fornecedor*>::iterator aux; //para iterar no vetor de fornecedores do servidor

    /* cabeçalho */
    imprimirCadastrarProdutoEmFornecedor();

    /* recebe o cnpj do fornecedor */
    std::cout << "Digite o CNPJ do fornecedor" << std::endl;
    std::cin >> cnpj;

    /* recebe o código de barras do produto */
    std::cout << "Digite o código de barras do produto" << std::endl;
    std::cin >> codigoBarras;

    /* it tenta achar o produto no vetor de produtos do servidor */
    it = this->produtos.begin();
    while (it != this->produtos.end() && (*it)->getCodigoBarras() != codigoBarras)
        it++;
    
    if (it == this->produtos.end()) //não achou
    {
        std::cout << "Produto não cadastrado" << std::endl;
        return;
    }

    /* aux tenta achaar o fornecedor no vetor de fornecedores do servidor */
    aux = this->fornecedores.begin();
    while (aux != this->fornecedores.end() && (*aux)->getCNPJ() != cnpj)
        aux++;
    
    if (aux == this->fornecedores.end()) //não achou
    {
        std::cout << "Fornecedor não cadastrado" << std::endl;
        return;
    }

    /* adiciona fornecedor no vetor de fornecedores do produto */
    /* na mesma função, adiciona produto no vetor de produtos do fornecedor */
    (*it)->adicionarFornecedor((*aux));
}

/* tira produto do vetor de produtos do fornecedor */
/* tira fornecedor do vetor de fornecedores do produto */
void Servidor::descadastrarProdutoEmFornecedor()
{
    std::string cnpj;
    std::string codigoBarras;
    std::list<Produto*>::iterator it; //para iterar no vetor de produtos do servidor
    std::list<Fornecedor*>::iterator aux; //para iterar no vetor de fornecedores do servidor

    /* cabeçalho */
    imprimirDescadastrarProdutoEmFornecedor();

    /* recebendo cnpj do fornecedor */
    std::cout << "Digite o CNPJ do fornecedor" << std::endl;
    std::cin >> cnpj;

    /* recebendo código de barras do produto */
    std::cout << "Digite o código de barras do produto" << std::endl;
    std::cin >> codigoBarras;

    /* it tenta encontrar produto no vetor de produtos do servidor */
    it = this->produtos.begin();
    while (it != this->produtos.end() && (*it)->getCodigoBarras() != codigoBarras)
        it++;
    
    if (it == this->produtos.end()) //não achou
    {
        std::cout << "Produto não cadastrado" << std::endl;
        return;
    }

    /* aux tenta encontrar o fornecedor no vetor de fornecedores do servidor */
    aux = this->fornecedores.begin();
    while (aux != this->fornecedores.end() && (*aux)->getCNPJ() != cnpj)
        aux++;
    
    if (aux == this->fornecedores.end()) //não achou
    {
        std::cout << "Fornecedor não cadastrado" << std::endl;
        return;
    }

    /* tira fornecedor do vetor de fornecedores do produto */
    /* na mesma função, tira produto do vetor de produtos do fornecedor */
    (*it)->excluirFornecedor(cnpj);
}

void Servidor::listarProdutosPorFornecedor() const
{
    int i{1}; //índice do fornecedor
    std::list<Fornecedor*>::const_iterator it; //para iterar no vetor de fornecedores do servidor

    /* cabeçalho */
    imprimirListarProdutosPorFornecedor();

    /* it itera no vetor de fornecedores do servidor */
    for (it = this->fornecedores.begin(); it != this->fornecedores.end(); it++)
    {
        /* imprimindo informações do fornecedor */
        std::cout << "Fornecedor " << i << std::endl; //índice
        
        (*it)->imprimirProdutosPorFornecedor();

        i++; //acrescenta ao índice
    }
}

void Servidor::listarFornecedoresPorProduto() const
{
    int i{1}; //índice do produto
    std::list<Produto*>::const_iterator it; //para iterar no vetor de produtos do servidor

    /* cabeçalho */
    imprimirListarFornecedoresPorProduto();

    /* it itera no vetor de produtos do servidor */
    for (it = this->produtos.begin(); it != this->produtos.end(); it++)
    {
        /* imprimindo informações do produto */
        std::cout << "Produto " << i << std::endl; //índice

        (*it)->imprimirFornecedoresPorProduto();    

        i++;
    }
}

void Servidor::listarEstoqueBaixo() const
{
    std::list<Produto*>::const_iterator it; //para iterar no vetor de produtos do servidor

    /* cabeçalho */
    imprimirListarEstoqueBaixo();

    /* it itera pelo vetor de produtos do servidor */
    for (it = this->produtos.begin(); it != this->produtos.end(); it++)
        if ((*it)->getEstoque() <= this->estoqueBaixo) //estoque baixo é uma constante do servidor
            std::cout << (*it)->getCodigoBarras() << " está com " 
            << (*it)->getEstoque() << " itens" << std::endl;
}

void Servidor::gerarRelatorioVendas() const
{
    int saldo{0}; //saldo de vendas começa em 0
    std::list<Produto*>::const_iterator it; //para iterar no vetor de vendas do servidor

    /* cabeçalho */
    imprimirGerarRelatorioVendas();

    /* it itera no vetor de vendas do servidor */
    for (it = this->vendas.begin(); it != this->vendas.end(); it++)
    {
        /* imprime número de vendas de um prouto */
        std::cout << (*it)->getEstoque() << " unidades foram vendidas de " 
        << (*it)->getCodigoBarras() << std::endl;
        
        /* atualiza o saldo de vendas */
        saldo += (*it)->getValor() * (*it)->getEstoque();
    }
    std::cout << std::endl;

    /* imprime saldo final de vendas */
    std::cout << "Fechamento das vendas: " << saldo << std::endl;
}

void Servidor::gerarRelatorioCompras() const
{
    int saldo{0}; //saldo de compras começa em 0
    std::list<Produto*>::const_iterator it; //para iterar no vetor de compras do servidor

    /* cabeçalho */
    imprimirGerarRelatorioCompras();

    /* it itera no vetor de compras do servidor */
    for (it = this->compras.begin(); it != this->compras.end(); it++)
    {
        /* imprimindo número de compras de um produto */
        std::cout << (*it)->getEstoque() << " unidades foram compradas de " 
        << (*it)->getCodigoBarras() << std::endl;
        
        /* atualizando saldo de compras */
        saldo += - (*it)->getValor() * (*it)->getEstoque();
    }
    std::cout << std::endl;

    /* imprimindo saldo final de compras */
    std::cout << "Fechamento das compras: " << saldo << std::endl;
}

void Servidor::pagarFuncionarios()
{
    std::list<Funcionario*>::iterator it; //para iterar no vetor de funcionários do servidor

    /* it itera no vetor de funcionários do servidor */
    for (it = this->funcionarios.begin(); it != this->funcionarios.end(); it++)
        saldo += - ((*it)->getSalario()); //diminui salário de (*it) do saldo
}