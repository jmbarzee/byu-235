#include "ExpressionManager.h"
#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <cctype>
#include <stack>

using namespace std;

string intToString(int in) {
	stringstream ss;
	ss << in;
	string out = ss.str();
	return out;
}
int stringToInt(string in) {
	stringstream ss;
	ss.str(in);
	int out;
	ss >> out;
	return out;
}
bool isNum(string in) {
	stringstream ss;
	ss.str(in);
	int out;
	ss >> out;
	if (ss.fail() || !ss.eof())
		return false;
	return true;
}

/*
 * Checks whether an expression is balanced on its parentheses
 *
 * - The given expression will have a space between every number or operator
 *
 * @return true if expression is balanced
 * @return false otherwise
 */

bool ExpressionManager::isBalanced(string expression) {
	//cout << "isBalanced( " << expression << ')' << endl;
	int nums = 0;
	int ops = 0;
	stringstream ss;
	ss.str(expression);
	string temp;
	while (ss.rdbuf()->in_avail() != 0) {
		ss >> temp;
		if (isNum(temp)) {
			nums++;
		} else if (temp[0] == '*' || temp[0] == '/' || temp[0] == '+'
				|| temp[0] == '-' || temp[0] == '%') {
			ops++;
		}
	}
	if (nums - ops != 1 && nums + ops != 0) {
		return false;
	}
	stack<char> history;
	for (int i = 0; i < expression.size(); i++) {
		if (expression[i] == '(' || expression[i] == '{'
				|| expression[i] == '[') {
			history.push(expression[i]);
		} else if (expression[i] == ')') {
			if (history.size() == 0)
				return false;
			if (history.top() == '(')
				history.pop();
			else
				return false;
		} else if (expression[i] == '}') {
			if (history.size() == 0)
				return false;
			if (history.top() == '{')
				history.pop();
			else
				return false;
		} else if (expression[i] == ']') {
			if (history.size() == 0)
				return false;
			if (history.top() == '[')
				history.pop();
			else
				return false;
		} else if (expression[i] == '.') {
			return false;
		}
	}
	if (!history.empty())
		return false;
	return true;
}
/**
 * Converts a postfix expression into an infix expression
 * and returns the infix expression.
 *
 * - The given postfix expression will have a space between every number or operator.
 * - The returned infix expression must have a space between every number or operator.
 * - Redundant parentheses are acceptable i.e. ( ( 3 * 4 ) + 5 ).
 * - Check lab requirements for what will be considered invalid.
 *
 * return the string "invalid" if postfixExpression is not a valid postfix expression.
 * otherwise, return the correct infix expression as a string.
 *
 *
 */
string ExpressionManager::postfixToInfix(string postfixExpression) {
	if (!isBalanced(postfixExpression))
		return "invalid";
	//cout << "postfixToInfix( " << postfixExpression << ')' << endl;
	stringstream ss;
	ss.str(postfixExpression);
	stack<string> tokens;
	string temp;
	while (!ss.fail() || !ss.eof()) {
		ss >> temp;
		if (ss.fail())
			break;
		//cout << "read: " << temp << endl;
		if (isNum(temp)) {
			//cout << "    pushed: " << temp << endl;
			tokens.push(temp);
		} else if (temp[0] == '*' || temp[0] == '/' || temp[0] == '+'
				|| temp[0] == '-' || temp[0] == '%') {
			if (tokens.size() < 2)
				return "invalid";
			string right = tokens.top();
			//cout << "    popped : " << tokens.top() << endl;
			tokens.pop();
			string left = tokens.top();
			//cout << "    popped : " << tokens.top() << endl;
			tokens.pop();
			stringstream sstemp;
			sstemp << "( " << left << ' ' << temp << ' ' << right << " )";
			//cout << "    pushed: " << sstemp.str() << endl;
			tokens.push(sstemp.str());
		} else {
			return "invalid";
		}
	}
	return tokens.top();
}

/*
 * Converts an infix expression into a postfix expression
 * and returns the postfix expression
 *
 * - The given infix expression will have a space between every number or operator.
 * - The returned postfix expression must have a space between every number or operator.
 * - Check lab requirements for what will be considered invalid.
 *
 * return the string "invalid" if infixExpression is not a valid infix expression.
 * otherwise, return the correct postfix expression as a string.
 *
 */
string ExpressionManager::infixToPostfix(string infixExpression) {
	if (!isBalanced(infixExpression))
		return "invalid";
	//cout << "infixToPostfix( " << infixExpression << ')' << endl;
	stringstream in;
	stringstream out;
	in.str(infixExpression);
	stack<int> ops;
	string temp;
	while (!in.fail() || !in.eof()) {
		in >> temp;
		if (in.fail())
			break;
		if (isNum(temp)) {
			//cout << "read: " << temp << endl;
			out << temp << ' ';
			//cout << "    on output: " << temp << endl;
		} else if (temp[0] == '(') {
			//cout << "read: " << temp << endl;
			ops.push(temp[0]);
			//cout << "    on stack: " << temp << endl;
		} else if (temp[0] == ')') {
			//cout << "read: " << temp << endl;
			while (ops.top() != '(') {
				//cout << "    off stack: " << (char) ops.top() << endl;
				out << (char) ops.top() << ' ';
				ops.pop();
			}
			//cout << "    off stack: " << (char) ops.top() << endl;
			ops.pop();
		} else if (temp[0] == '*' || temp[0] == '/' || temp[0] == '%') {
			//cout << "read: " << temp << endl;
			if (ops.size() != 0) {
				while (ops.top() == '*' || ops.top() == '/' || ops.top() == '%') {
					//cout << "    off stack: " << (char) ops.top() << endl;
					out << (char) ops.top() << ' ';
					ops.pop();
					if (ops.size() == 0)
						break;
				}
			}
			//cout << "    on stack: " << temp << endl;
			ops.push(temp[0]);
		} else if (temp[0] == '-' || temp[0] == '+') {
			//cout << "read: " << temp << endl;
			if (ops.size() != 0) {
				while (ops.top() == '*' || ops.top() == '/' || ops.top() == '%'
						|| ops.top() == '-' || ops.top() == '+') {
					//cout << "    off stack: " << (char) ops.top() << endl;
					out << (char) ops.top() << ' ';
					ops.pop();
					if (ops.size() == 0)
						break;
				}
			}
			//cout << "    on stack: " << temp << endl;
			ops.push(temp[0]);
		} else {
			return "invalid";
		}
	}
	//cout << "empty stack" << endl;
	while (ops.size() != 0) {
		//cout << "    off stack: " << (char) ops.top() << endl;
		out << (char) ops.top();
		if (ops.size() != 1)
			out << ' ';
		ops.pop();
	}
	return out.str();
}

/*
 * Evaluates a postfix expression returns the result as a string
 *
 * - The given postfix expression will have a space between every number or operator.
 * - Check lab requirements for what will be considered invalid.
 *
 * return the string "invalid" if postfixExpression is not a valid postfix Expression
 * otherwise, return the correct evaluation as a string
 */
string ExpressionManager::postfixEvaluate(string postfixExpression) {
	//cout << "PostfixEvaluate( " << postfixExpression << " )" << endl;
	if (!isBalanced(postfixExpression))
		return "invalid";
	stringstream ss;
	ss.str(postfixExpression);
	stack<int> values;
	string temp;
	while (!ss.fail() || !ss.eof()) {
		ss >> temp;
		//cout << "read: " << temp << endl;
		if (ss.fail())
			break;
		if (temp[0] == '*') {
			if (values.size() < 2)
				return "invalid";
			int right = values.top();
			values.pop();
			int left = values.top();
			values.pop();
			//cout << "    popped: " << right << endl;
			//cout << "    popped: " << left << endl;
			//cout << "    pushed: " << left * right << endl;
			values.push(left * right);
		} else if (temp[0] == '/') {
			if (values.size() < 2)
				return "invalid";
			int right = values.top();
			values.pop();
			int left = values.top();
			values.pop();
			//cout << "    popped: " << right << endl;
			//cout << "    popped: " << left << endl;
			if (right == 0) {
				//cout << "div by zero!!!" << endl;
				return "invalid";
			}
			//cout << "    pushed: " << left / right << endl;
			values.push(left / right);
		} else if (temp[0] == '+') {
			if (values.size() < 2)
				return "invalid";
			int right = values.top();
			values.pop();
			int left = values.top();
			values.pop();
			//cout << "    popped: " << right << endl;
			//cout << "    popped: " << left << endl;
			//cout << "    pushed: " << left + right << endl;
			values.push(left + right);
		} else if (temp[0] == '-') {
			if (values.size() < 2)
				return "invalid";
			int right = values.top();
			values.pop();
			int left = values.top();
			values.pop();
			values.push(left - right);
			//cout << "    popped: " << right << endl;
			//cout << "    popped: " << left << endl;
			//cout << "    pushed: " << left - right << endl;
		} else if (temp[0] == '%') {
			if (values.size() < 2)
				return "invalid";
			int right = values.top();
			values.pop();
			int left = values.top();
			values.pop();
			//cout << "    popped: " << right << endl;
			//cout << "    popped: " << left << endl;
			//cout << "    pushed: " << left % right << endl;
			values.push(left % right);
		} else if (isNum(temp)) {
			//cout << "    pushed: " << temp << endl;
			values.push(stringToInt(temp));
		} else {
			return "invalid";
		}
	}
	return intToString(values.top());
}
