#ifndef CPF_INVALIDO_EXCEPTION
#define CPF_INVALIDO_EXCEPTION

#include <stdexcept>

namespace sistema
{

class CPFInvalidoException : public std::runtime_error{
    public:
        CPFInvalidoException(const long cpf);
        virtual ~CPFInvalidoException() = default;

        const long cpf;
};

} // namespace sistema

#endif