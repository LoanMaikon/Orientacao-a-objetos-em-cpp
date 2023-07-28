#include "Funcionario.hpp"

#include <string>
#include <iostream>

using namespace sistema; //namespace

Funcionario::Funcionario(){}

Funcionario::Funcionario(const std::string nome, const long cpf, const int idade, const int salario, const int cargo)
{
    this->setNome(nome);
	this->setCPF(cpf);
	this->setIdade(idade);
	this->setSalario(salario);
	this->setCargo(cargo);
}

Funcionario::~Funcionario(){}

long Funcionario::getCPF() const
{
    return this->cpf;
}

void Funcionario::setCPF(const long cpf)
{
    if (! validarCPF(cpf))
		throw CPFInvalidoException{cpf};

	this->cpf = cpf;
}

std::string Funcionario::getNome() const
{
    return this->nome;
}

void Funcionario::setNome(const std::string nome)
{
    this->nome = nome;
}

int Funcionario::getIdade() const
{
    return this->idade;
}

void Funcionario::setIdade(const int idade)
{
	this->idade = idade;
}

int Funcionario::getSalario() const
{
    return this->salario;
}
    
void Funcionario::setSalario(const int salario)
{
    this->salario = salario;
}

int Funcionario::getCargo() const
{
	return this->cargo;
}

void Funcionario::setCargo(const int cargo)
{
	this->cargo = cargo;
}

bool Funcionario::validarCPF(long cpf)
{
	int somatorioValidaUltimo;
	int modulo;
	int somatorioValidaPenultimo = 0;
	int ultimo = cpf%10;
	cpf = cpf/10;
	int penultimo = cpf%10;
	cpf = cpf/10;
	somatorioValidaUltimo = penultimo*2;

	for (int i=2; i <= 11; i++)
    {
		modulo = cpf%10;
		cpf = cpf/10;
		somatorioValidaPenultimo += modulo*i;
		somatorioValidaUltimo += modulo*(i+1);
	}

	modulo = somatorioValidaPenultimo%11;
	if (modulo < 2)
    {
		if (! penultimo)
			return false; //cpf invalido
	}
    else
    {
		if (penultimo != 11 - modulo)
			return false; //cpf invalido
	}

	modulo = somatorioValidaUltimo%11;
	if (modulo < 2)
    {
		if (! ultimo)
			return false; //cpf invalido
	}
    else
    {
		if (ultimo != 11-modulo)
			return false; //cpf invalido
	}

	return true; //cpf valido
}

bool Funcionario::operator==(const Funcionario &funcionario) const
{
	return this->cpf == funcionario.cpf;
}

bool Funcionario::operator!=(const Funcionario &funcionario) const
{
	return this->cpf != funcionario.cpf;
}

/* retorna string do cargo do funcionário */
std::string getStringCargo(int cargo)
{
    if (cargo == static_cast<int>(EnumTipoFuncionario::DIRETOR))
        return "Diretor";
    else if (cargo == static_cast<int>(EnumTipoFuncionario::GERENTE))
        return "Gerente";
    else if (cargo == static_cast<int>(EnumTipoFuncionario::ASSESSOR))
        return "Assessor";
    else
        return "Cargo inválido";
}

void Funcionario::imprimirFuncionario() const
{
	std::string cargo; //para imprimir cargo

	std::cout << "Nome do funcionário: " << this->getNome() << std::endl;
    std::cout << "CPF do funcionário: " << this->getCPF() << std::endl;
    std::cout << "Idade do funcionário: " << this->getIdade() << std::endl;
    std::cout << "Salário do funcionário: " << this->getSalario() << std::endl;

    /* imprimindo cargo */
    cargo = getStringCargo(this->getCargo()); //função para retornar string do cargo
    std::cout << "Cargo do funcionário: " << cargo << std::endl << std::endl;
}