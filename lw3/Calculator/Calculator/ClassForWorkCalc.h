#include <iostream>
#include <unordered_set>
#include <optional>
#include <string>
#include <unordered_map>
#include <fstream>
#include <functional>

class ValueListener
{
public:
	virtual double OnValueChange();
};

class Value
{
public:
	virtual double Get();
	virtual void AddListener(ValueListener listener);
};

class Variable : public Value
{
public:
	Variable(double value)
	{
		m_value = value;
	}
	void SetValue(double value);
	double Get() override;
	void AddListener(ValueListener listener) override;
private:
	std::unordered_set<ValueListener*> m_listeners;
	double m_value;
};

class BasicFunction : public ValueListener, public Value
{
public:
	double Get() override;
private:
	virtual double CalcValue();
	double OnValueChange() override;
	std::optional<double> m_catchedValue;
};

class BinFn
{
public:
	double ADD(double argRight);
	double SUB(double argRight);
	double MUL(double argRight);
	double DIV(double argRight);
};

class UnFn
{
public:
	double IDENTITY(double arg);
};

class BinaryFunction : private BasicFunction
{
public:
	BinaryFunction(BinFn fn, Value arg1, Value agr2);
	void AddListener(ValueListener listener);
private:
	double CalcValue() override;
	BinFn m_fn;
	Value* m_arg1;
	Value* m_arg2;
};

class UnaryFunction : private BasicFunction
{
public:
	UnaryFunction(UnFn fn, Value arg);
	void AddListener(ValueListener listener);
private:
	double CalcValue() override;
	UnFn m_fn;
	Value* m_arg;
};

class Function
{

};

class Memory
{
public:
	void Addvariable(std::string name, double value);
	void AddBinaryFunction(std::string name, BinFn fn, std::string_view arg1, std::string_view arg2);
	void AddUnaryFunction(std::string name, UnFn fn, std::string arg);
	void SetVariableValue(std::string_view name, double value);
	double GetFunctionValue(std::string_view name);
	double GetVariableValue(std::string_view name);
	void EnumarateFunctions(void(*fn)(std::string_view, double));
	void EnumarateVariables(void(*fn)(std::string_view, double));
private:
	std::unordered_map<std::string, Function> m_functions;
	std::unordered_map<std::string, Variable> m_variables;
	std::unordered_map<std::string, const Value*> m_values;
	std::unordered_map<std::string, const Variable*> m_sortedVariables;
	std::unordered_map<std::string, const BasicFunction*> m_sortedFunctions;
};

class ConsoleUI
{
public:
	ConsoleUI(Memory calc, std::istream input, std::ostream output);
	void Run();
private:
	std::unordered_map <std::string, ()> m_commnads;
	Memory& m_memory;
	std::istream& m_input;
	std::ostream& m_input;
};