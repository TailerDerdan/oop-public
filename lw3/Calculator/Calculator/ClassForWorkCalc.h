#pragma once
#include <set>
#include <string>
#include <regex>
#include <iostream>
#include <iterator>
#include <algorithm>

class Variable;
class Functions;

class Memory
{
public:
	void PrintVars();
	void PrintFunc();
	void Print(std::string name);
	bool ParseSequence(std::string sequence);
	void WorkWithMemory();
protected:
	static std::set<Variable> m_variables;
	static std::set<Functions> m_funcs;
private:
	std::string sequence;
	const std::set<char> m_operations = {'+', '-', '*', '/'};
};

class Identificator
{
public:

	std::string GetName() const { return m_name; }
	
	Identificator() {};
	Identificator(std::string name);
	
	bool CheckCorrectnessIdent();
	bool operator==(Identificator name) const;
	void operator=(const Identificator& name);
	
	~Identificator();
	
private:
	std::string m_name;
	const std::string m_identRegex = R"(^[a-zA-Z_][a-zA-Z0-9_]*$)";
};

class Variable : public Memory
{
public:
	Identificator GetName() const;
	double GetValue() const;
	
	Variable() {};
	
	bool MakeAVar(std::string& name, std::string& err);
	bool MakeAVar(std::string& name, std::string& value, std::string& err);
	bool AssignAVar(std::string& name, std::string& value, std::string& err);
	bool operator<(const Variable& var) const;
	void operator=(const Variable& varRight);
	
	~Variable();
	
private:
	bool IsIdentDoubleNum(std::string& value, std::string& err);
	Variable HasSecondIdentFound(std::string& value, std::string& err);
	Identificator m_name;
	double m_value;
};


class Operator : public Memory
{
public:
	Operator();
	std::string GetOperation() const;

	double Calculate(const std::string& operation);
	bool FindAndAssignIdent(const std::string& var);
	bool FindAndAssignIdent(const std::string& varLeft, const std::string& varRight);

	~Operator();
private:
	void UpdateValues();
	Identificator m_leftVar, m_rightVar;
	double m_identLeft, m_identRight;
	std::string m_operator;
};


class Functions : public Memory
{
public:
	Identificator GetName() const;
	double GetResult() const;
	Operator GetOperator() const;

	bool MakeAFunc(const std::string& name, const std::string& var);
	bool MakeAFunc(const std::string& name, const std::string& varLeft,
		const std::string& varRight, const std::string& operation);
	bool operator<(const Functions& funcRight) const;

private:
	bool WasThereIdentBefore(const Identificator& name);
	Identificator m_name;
	double m_result;
	Operator m_localVariable;
};
