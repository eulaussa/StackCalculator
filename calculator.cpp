#include <iostream>
#include <fstream>
#include <stack>
#include <iomanip>
#include <string>

using namespace std;
bool IsOperand(char c) {
	return (c >= '0' && c <= '9');
}

bool IsOperator(char c) {
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

int GetPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    else if (op == '*' || op == '/') return 2;
	return -1;
}

int CalcPrecedence(char op1, char op2) {
	int c1weight = GetPrecedence(op1), c2weight = GetPrecedence(op2);
	return (c1weight >= c2weight);
}

string ToPostfix(string input) {
	stack<char> ops;
	string postfix = ""; 
	for(int i = 0;i< input.length();i++) {
		if(IsOperator(input[i])) {
			while(!ops.empty() && ops.top() != '(' && CalcPrecedence(ops.top(),input[i])) {
				postfix+= ops.top();
				ops.pop();
			}
			ops.push(input[i]);
		}
		else if(IsOperand(input[i]))
			postfix +=input[i];

		else if (input[i] == '(') 
		    ops.push(input[i]);

		else if(input[i] == ')') {
			while(!ops.empty() && ops.top() !=  '(') {
				postfix += ops.top();
				ops.pop();
			}
			ops.pop();
		}
	}
	while(!ops.empty()) {
		postfix += ops.top();
		ops.pop();
	}
	return postfix;
}

double EvaluatePostfix(string input) { 
    stack<double> numbers; 
    for (int i = 0; i < input.length(); ++i) {  
        if (IsOperand(input[i])){
            string c = "";
            c += input[i];
            numbers.push(stod(c));
        } 
        else {  
            double number1 = numbers.top();
            numbers.pop();  
            double number2 = numbers.top();
            numbers.pop();  
            switch (input[i]) {  
            case '+': numbers.push(number2 + number1); break;  
            case '-': numbers.push(number2 - number1); break;  
            case '*': numbers.push(number2 * number1); break;  
            case '/': numbers.push(number2 / number1); break;  
            }  
        }  
    }  
    return numbers.top();  
}  

int main(int argc, char* argv[]) {
    string inputFile = argv[1], outputFile = argv[2];
    ifstream input; ofstream output;

    input.open(inputFile);
    string expression;
    getline(input, expression);
    string pf = ToPostfix(expression);
    double result = EvaluatePostfix(pf);
    output.open(outputFile);
    output << fixed << setprecision(2) << result;
    output.close();
    cout << "Done!" << endl;

    return 0;
}