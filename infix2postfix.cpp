#include "stack.hpp"

using namespace std;

// Auxiliary method, you probably find it useful
// Operands are all lower case and upper case characters
bool isOperand(char c){
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Auxiliary method, you probably find it useful
int precedence(char c)
{
  if(c == '+' || c == '-'){
    return 0;
  }
  if(c == '*' || c == '/'){
    return 1;
  }
  if(c == '^'){
    return 2;
  }
  return -1;
}

int main(){
  freopen("input_infix2postfix.txt", "r", stdin);
  string input;
  string solution;
  int line_counter = 0;
  while(cin >> solution)
  {
    cin >> input;
    Stack<char> stack;
    string result;

     //The input file is in the format "expected_solution infix_expression", 
     //where expected_solution is the infix_expression in postfix format
     // WRITE CODE HERE to store in 'result' the postfix transformation of 'input'

    for (int i = 0; i < input.length(); ++i) {
    char current = input[i];
   
    if (isOperand(current)) {
        
        result += current;
    } else if (current == '(') {
        
          stack.push(current);
    } else if (current == ')') {
      
      
      
        while (stack.size() > 0  && stack.peek() != '(') {
            result += stack.pop();
        }
        
        stack.pop();
    } else {
        

        while (stack.size() > 0  && stack.peek() != '(' && precedence(stack.peek()) >= precedence(current)) {
            result += stack.pop();
        }
        
        stack.push(current);
    }
   }


while (stack.size() > 0 ) {
    result += stack.pop();
}
    // Checking whether the result you got is correct
    if(solution == result){
      cout << "line " << line_counter << ": OK [" << solution << " " << result << "]" << endl;
    }else{
      cout << "line " << line_counter << ": ERROR [" << solution << " " << result << "]" << endl;
    }
    line_counter++;
  }
}