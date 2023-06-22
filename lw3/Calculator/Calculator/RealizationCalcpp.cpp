#include "ClassForWorkCalc.h"

std::set<Variable> Memory::m_variables;
std::set<Functions> Memory::m_funcs;

void Memory::PrintFunc()
{
	for (auto iter : m_funcs)
	{
		std::cout << iter.GetName().GetName() << ':' << iter.GetResult() << std::endl;
	}
}

void Memory::PrintVars()
{
	for (auto iter : m_variables)
	{
		std::cout << iter.GetName().GetName() << ':' << iter.GetValue() << std::endl;
	}
}

void Memory::Print(std::string name)
{
	Identificator nameId(name);
	if (!nameId.CheckCorrectnessIdent())
	{
		std::cout << "There is no such identificator" << std::endl;
		return;
	}
	
	for (auto iter : m_variables)
	{
		if (iter.GetName() == nameId)
		{
			if (iter.GetValue() == NAN)
			{
				std::cout << "nan" << std::endl;
				return;
			}
			std::cout << iter.GetValue() << std::endl;
			return;
		}
	}
	
	for (auto iter : m_funcs)
	{
		if (iter.GetName() == nameId)
		{
			iter.GetOperator().Calculate(iter.GetOperator().GetOperation());
			std::cout << iter.GetResult() << std::endl;
			return;
		}
	}
}

bool Memory::ParseSequence(std::string sequence)
{
	if (sequence == "printvars")
	{
		PrintVars();
		return true;
	}
	if (sequence == "printfns")
	{
		PrintFunc();
		return true;
	}

	size_t foundPosSpace = sequence.find_first_of(' ');
	if (foundPosSpace <= sequence.size())
	{
		std::string command;
		std::string arg;
		command.append(sequence, 0, foundPosSpace);
		if (command == "print")
		{
			arg.append(sequence, foundPosSpace + 1, sequence.size() - foundPosSpace);
			Print(arg);

		}
		if (command == "var")
		{
			arg.append(sequence, foundPosSpace + 1, sequence.size() - foundPosSpace);
			Variable var;
			std::string err;
			
			if (var.MakeAVar(arg, err))
			{
				m_variables.insert(var);
				return true;
			}
			
			if (!err.empty())
			{
				std::cout << err << std::endl;
			}
			return false;
		}
		if (command == "let")
		{
			int foundPosEquel = sequence.find_first_of('=');
			arg.append(sequence, foundPosSpace + 1, foundPosEquel - foundPosSpace - 1);
			std::string argRight;
			argRight.append(sequence, foundPosEquel + 1, sequence.size() - foundPosEquel);

			Variable var;
			std::string err;
			
			if (!var.AssignAVar(arg, argRight, err))
			{
				if (var.MakeAVar(arg, argRight, err))
				{
					m_variables.insert(var);
					return true;
				}
				std::cout << err << std::endl;
				return false;
			}
			return true;
		}
		if (command == "fn")
		{
			int foundPosEquel = sequence.find_first_of('=');
			arg.append(sequence, foundPosSpace + 1, foundPosEquel - foundPosSpace - 1);

			size_t foundPosOperation;
			for (auto iter : m_operations)
			{
				foundPosOperation = sequence.find_first_of(iter);
				if (foundPosOperation < sequence.size())
				{
					break;
				}
			}
			if (foundPosOperation >= sequence.size())
			{
				std::string argIdent;
				argIdent.append(sequence, foundPosEquel + 1, sequence.size() - foundPosEquel);
				Functions func;
				if (func.MakeAFunc(arg, argIdent))
				{
					m_funcs.insert(func);
					return true;
				}
			}		

			std::string operation;
			operation.append(sequence, foundPosOperation, 1);

			std::string identLeft;
			identLeft.append(sequence, foundPosEquel + 1, foundPosOperation - foundPosEquel - 1);
			std::string identRight;
			identRight.append(sequence, foundPosOperation + 1, sequence.size() - foundPosOperation);

			Functions func;
			if (func.MakeAFunc(arg, identLeft, identRight, operation))
			{
				m_funcs.insert(func);
				return true;
			}
			return false;
		}
	}
	return false;
}

void Memory::WorkWithMemory()
{
	std::string line;
	
	while (std::getline(std::cin, line))
	{
		ParseSequence(line);
	}
}

Identificator::Identificator(std::string name)
{
	m_name = name;
}

bool Identificator::CheckCorrectnessIdent()
{
	std::regex identRegex(m_identRegex);
	std::smatch identMatch;

	if (std::regex_match(m_name, identMatch, identRegex))
	{
		return true;
	}
	return false;
}

bool Identificator::operator==(Identificator name) const
{
	if (name.GetName() == m_name)
	{
		return true;
	}
	return false;
}

void Identificator::operator=(const Identificator& name)
{
	m_name = name.GetName();
}

Identificator::~Identificator()
{
	m_name.clear();
}

Identificator Variable::GetName() const
{
	return m_name;
}

double Variable::GetValue() const
{
	if (m_value == NAN)
	{
		return NAN;
	}
	return m_value;
}

bool Variable::IsIdentDoubleNum(std::string& value, std::string& err)
{
	Identificator varRight(value);
	if (!varRight.CheckCorrectnessIdent())
	{
		std::regex doubleNumRegex(R"((-?)(0|([1-9][0-9]*))(.[0-9]+)?)");

		std::smatch doubleNumMatch;

		if (!std::regex_match(value, doubleNumMatch, doubleNumRegex))
		{
			err = "Wrong number typed";
			return false;
		}
		return true;
	}
	return false;
}

Variable Variable::HasSecondIdentFound(std::string& value, std::string& err)
{
	Identificator varRight(value);
	for (auto iter : m_variables)
	{
		if (iter.GetName() == varRight)
		{
			return iter;
		}
	}

	err = "There is no identifier to the right of the equals sign";
	Variable var;
	return var;
}

bool Variable::MakeAVar(std::string& name, std::string& err)
{
	Identificator var(name);
	if (!var.CheckCorrectnessIdent())
	{
		err = "The name of the identifier does not comply with the rules";
		return false;
	}
	for (auto iter : m_variables)
	{
		if (iter.GetName() == var)
		{
			err = "Such an identifier already exists";
			return false;
		}
	}
	m_name = var;
	m_value = NAN;

	return true;
}

bool Variable::MakeAVar(std::string& name, std::string& value, std::string& err)
{
	if (MakeAVar(name, err))
	{
		if (IsIdentDoubleNum(value, err))
		{
			this->m_value = std::stod(value);
			return true;
		}

		Variable var = HasSecondIdentFound(value, err);
		if (var.GetName().GetName().empty())
		{
			return false;
		}
		this->m_value = var.GetValue();
		return true;
	}
	return false;
}

bool Variable::AssignAVar(std::string& name, std::string& value, std::string& err)
{
	Identificator varLeft(name);
	for (auto iter : m_variables)
	{
		if (iter.GetName() == varLeft)
		{
			if (IsIdentDoubleNum(value, err))
			{
				iter.m_value = std::stod(value);
				Variable var = iter;
				m_variables.erase(iter);
				m_variables.insert(var);
				return true;
			}

			Variable var = HasSecondIdentFound(value, err);
			if (var.GetName().GetName().empty())
			{
				return false;
			}
			iter.m_value = var.m_value;
			Variable varRight = iter;
			m_variables.erase(iter);
			m_variables.insert(varRight);
			
			return true;
		}
	}
	return false;
}

bool Variable::operator<(const Variable& var) const
{
	if (m_name.GetName() < var.GetName().GetName())
	{
		return true;
	}
	return false;
}

void Variable::operator=(const Variable& varRight)
{
	m_name = varRight.GetName();
	m_value = varRight.GetValue();
}

Variable::~Variable()
{
	m_name.~Identificator();
	m_value = 0;
}

Operator::Operator()
{
	m_identLeft = 0;
	m_identRight = 0;
	m_operator = "+";
}

std::string Operator::GetOperation() const
{
	return m_operator;
}

bool Operator::FindAndAssignIdent(const std::string& var)
{
	Identificator ident(var);
	if (!ident.CheckCorrectnessIdent())
	{
		return false;
	}
	for (auto iter : m_variables)
	{
		if (iter.GetName().GetName() == var)
		{
			m_leftVar = iter.GetName();
		}
	}
	for (auto iter : m_funcs)
	{
		if (iter.GetName().GetName() == var)
		{
			m_leftVar = iter.GetName();
		}
	}
	if ((m_leftVar.GetName().empty()) || (m_rightVar.GetName().empty()))
	{
		return false;
	}
	return true;
}

bool Operator::FindAndAssignIdent(const std::string& varLeft, const std::string& varRight)
{
	Identificator identLeft(varLeft);
	if (!identLeft.CheckCorrectnessIdent())
	{
		return false;
	}
	Identificator identRight(varRight);
	if (!identRight.CheckCorrectnessIdent())
	{
		return false;
	}
	for (auto iter : m_variables)
	{
		if (iter.GetName().GetName() == varLeft)
		{
			m_leftVar = iter.GetName();
		}
		if (iter.GetName().GetName() == varRight)
		{
			m_rightVar = iter.GetName();
		}
	}
	for (auto iter : m_funcs)
	{
		if (iter.GetName().GetName() == varLeft)
		{
			m_leftVar = iter.GetName();
		}
		if (iter.GetName().GetName() == varRight)
		{
			m_rightVar = iter.GetName();
		}
	}
	if ((m_leftVar.GetName().empty()) || (m_rightVar.GetName().empty()))
	{
		return false;
	}
	return true;
}

double Operator::Calculate(const std::string& operation)
{
	UpdateValues();
	m_operator = operation;
	if (m_operator == "+")
	{
		return m_identLeft + m_identRight;
	}
	if (m_operator == "-")
	{
		return m_identLeft - m_identRight;
	}
	if (m_operator == "*")
	{
		return m_identLeft * m_identRight;
	}
	if (m_operator == "/")
	{
		if (m_identRight == 0)
		{
			return NAN;
		}
		return m_identLeft / m_identRight;
	}
	return NAN;
}

Operator::~Operator()
{
	m_leftVar.~Identificator();
	m_rightVar.~Identificator();
	m_identRight = 0;
	m_identLeft = 0;
}

void Operator::UpdateValues()
{
	for (auto iter : m_variables)
	{
		if (iter.GetName() == m_leftVar)
		{
			m_identLeft = iter.GetValue();
		}
		if (iter.GetName() == m_rightVar)
		{
			m_identRight = iter.GetValue();
		}
	}

	for (auto iter : m_funcs)
	{
		if (iter.GetName() == m_leftVar)
		{
			m_identLeft = iter.GetResult();
		}
		if (iter.GetName() == m_rightVar)
		{
			m_identRight = iter.GetResult();
		}
	}
}

Identificator Functions::GetName() const
{
	return m_name;
}

double Functions::GetResult() const
{
	return m_result;
}

Operator Functions::GetOperator() const
{
	return m_localVariable;
}

bool Functions::WasThereIdentBefore(const Identificator& name)
{
	for (auto iter : m_funcs)
	{
		if (iter.GetName() == name)
		{
			return true;
		}
	}
	return false;
}

bool Functions::MakeAFunc(const std::string& name, const std::string& var)
{
	Identificator nameFunc(name);
	if (WasThereIdentBefore(nameFunc))
	{
		return false;
	}
	m_name = nameFunc;

	if (!m_localVariable.FindAndAssignIdent(var))
	{
		return false;
	}
	m_result = m_localVariable.Calculate(m_localVariable.GetOperation());
	return true;
}

bool Functions::MakeAFunc(const std::string& name, const std::string& varLeft,
	const std::string& varRight, const std::string& operation)
{
	Identificator nameFunc(name);
	if (WasThereIdentBefore(nameFunc))
	{
		return false;
	}
	m_name = nameFunc;

	if (!m_localVariable.FindAndAssignIdent(varLeft, varRight))
	{
		return false;
	}
	m_result = m_localVariable.Calculate(operation);
	return true;
}

bool Functions::operator<(const Functions& funcRight) const
{
	if (m_name.GetName() < funcRight.GetName().GetName())
	{
		return true;
	}
	return false;
}