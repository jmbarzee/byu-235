#include "ExpressionManagerInterface.h"

using namespace std;

class ExpressionManager: public ExpressionManagerInterface {
	public:
		ExpressionManager(){};
		~ExpressionManager(){};
		bool isBalanced(string expression);
		string postfixToInfix(string postfixExpression);
		string infixToPostfix(string infixExpression);
		string postfixEvaluate(string postfixExpression);
};
