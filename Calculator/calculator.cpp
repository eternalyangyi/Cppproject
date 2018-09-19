//
//  main.cpp
//  assigment1
//
//  Created by yy on 2017/8/1.
//  Copyright © 2017年 yy. All rights reserved.
//



/*
 *  For this assignment, datas pushed into stack should be identified as int or double.
 *  Since C++ stack have to be defined as one data type. Therefore, string based stack should work.
 *  If input data is numbers(include int and double), we push them as string into stack.
 *  Otherwise, if a command is typed in, we get element which have already pushed, turn thems into int or double based on .find('.') method.
 *  After computation, results are turned into string and push them into stack.
 *  When reverse command is detected, we get the top element in stack as N and pop it.
 *  Then pop N elements and push them into a pre-defined queue(reverseq).
 *  After pop, pop elements from queue and push them into stack, finish the reverse command.
 *  For repeat and endrepeat command, when repeat command starts, pop and get first element in stack.
 *  Then we store next several strings into a queue(repeat) untill endrepeat is detected.
 *  When endrepeat is detected, add elements into stack from repeat queue one by oneand compute this commands.
 *  Meanwhile copy the repeat queue into a queue(copyrepeat) because of multiple executions.
 */
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stack>
#include <queue>

namespace variable{
    std::string add = "add";
    std::string sub = "sub";
    std::string mul = "mult";
    std::string div = "div";
    std::string sqrt = "sqrt";
    std::string pop = "pop";
    std::string reverse = "reverse";
    std::string repeat = "repeat";
    std::string endrepeat = "endrepeat";
    std::stack<std::string> stack;
    std::queue<std::string> queue;
    std::queue<std::string> reverseq;
    int reverse_count1;
    int reverse_count2;
    
}
/*
 Calculate is designed to handle commands include add, sup, div and mult.
 */
void calculate(std::string a, std::string b,std::string op){
    std::string newtop;
    if (op.compare(variable::add) ==0){
        if(a.find('.') != std::string::npos){
            double x = std::stod(a);
            if(b.find('.') != std::string::npos){
                double y = std::stod(b);
                double z = x + y;
                std::cout<<x<<" + "<<y<<" = "<<z<<std::endl;
                newtop = std::to_string(z);
            }
            else{
                int y = std::stod(b);
                double z = x + y;
                std::cout<<x<<" + "<<y<<" = "<<z<<std::endl;
                newtop = std::to_string(z);
            }
        }
        else{
            int x =std::stod(a);
            if(b.find('.') != std::string::npos){
                double y = std::stod(b);
                double z = x + y;
                std::cout<<x<<" + "<<y<<" = "<<z<<std::endl;
                newtop = std::to_string(z);
            }
            else{
                int y = std::stod(b);
                int z = x + y;
                std::cout<<x<<" + "<<y<<" = "<<z<<std::endl;
                newtop = std::to_string(z);
            }
        }
    }
    else if (op.compare(variable::sub) ==0){
        if(a.find('.') != std::string::npos){
            double x = std::stod(a);
            if(b.find('.') != std::string::npos){
                double y = std::stod(b);
                double z = x - y;
                std::cout<<x<<" - "<<y<<" = "<<z<<std::endl;
                newtop = std::to_string(z);
            }
            else{
                int y = std::stod(b);
                double z = x - y;
                std::cout<<x<<" - "<<y<<" = "<<z<<std::endl;
                newtop = std::to_string(z);
            }
        }
        else{
            int x =std::stod(a);
            if(b.find('.') != std::string::npos){
                double y = std::stod(b);
                double z = x - y;
                std::cout<<x<<" - "<<y<<" = "<<z<<std::endl;
                newtop = std::to_string(z);
            }
            else{
                int y = std::stod(b);
                int z = x - y;
                std::cout<<x<<" - "<<y<<" = "<<z<<std::endl;
                newtop = std::to_string(z);
            }
        }
    }
    else if (op.compare(variable::mul) ==0){
        if(a.find('.') != std::string::npos){
            double x = std::stod(a);
            if(b.find('.') != std::string::npos){
                double y = std::stod(b);
                double z = x * y;
                std::cout<<x<<" * "<<y<<" = "<<z<<std::endl;
                newtop = std::to_string(z);
            }
            else{
                int y = std::stod(b);
                double z = x * y;
                std::cout<<x<<" * "<<y<<" = "<<z<<std::endl;
                newtop = std::to_string(z);
            }
        }
        else{
            int x =std::stod(a);
            if(b.find('.') != std::string::npos){
                double y = std::stod(b);
                double z = x * y;
                std::cout<<x<<" * "<<y<<" = "<<z<<std::endl;
                newtop = std::to_string(z);
            }
            else{
                int y = std::stod(b);
                int z = x * y;
                std::cout<<x<<" * "<<y<<" = "<<z<<std::endl;
                newtop = std::to_string(z);
            }
        }
    }
    else if (op.compare(variable::div) ==0){
        if(a.find('.') != std::string::npos){
            double x = std::stod(a);
            if(b.find('.') != std::string::npos){
                double y = std::stod(b);
                double z = x / y;
                std::cout<<x<<" / "<<y<<" = "<<z<<std::endl;
                newtop = std::to_string(z);
            }
            else{
                int y = std::stod(b);
                double z = x / y;
                std::cout<<x<<" / "<<y<<" = "<<z<<std::endl;
                newtop = std::to_string(z);
            }
        }
        else{
            int x =std::stod(a);
            if(b.find('.') != std::string::npos){
                double y = std::stod(b);
                double z = x / y;
                std::cout<<x<<" / "<<y<<" = "<<z<<std::endl;
                newtop = std::to_string(z);
            }
            else{
                int y = std::stod(b);
                int z = x / y;
                std::cout<<x<<" / "<<y<<" = "<<z<<std::endl;
                newtop = std::to_string(z);
            }
        }
    }
    variable::stack.push(newtop);
}

/*
 * Handling commands exclude repeat and four arithmetic operations.
 */
void command(std::string s){
    if(isdigit(s[0])){
        variable::stack.push(s);
    }
    else{
        std::string top;
        std::string a;
        std::string b;
        if(s.compare(variable::add) ==0 ||s.compare(variable::sub) ==0 ||s.compare(variable::mul) ==0 ||s.compare(variable::div) ==0 ){
            a =variable::stack.top();
            variable::stack.pop();
            b =variable::stack.top();
            variable::stack.pop();
            calculate(a,b,s);
        }
        else if(s.compare(variable::sqrt) ==0){
            top = variable::stack.top();
            variable::stack.pop();
            double x = std::stod(top);
            std::cout<<"sqrt "<<x<<" = "<<sqrt(x)<<std::endl;
            std::string newtop = std::to_string(sqrt(x));
            variable::stack.push(newtop);
        }
        else if(s.compare(variable::pop) ==0){
            variable::stack.pop();
        }
        else if(s.compare(variable::reverse) == 0){
            variable::reverse_count1 = std::stoi(variable::stack.top());
            variable::reverse_count2 = std::stoi(variable::stack.top());
            variable::stack.pop();
            while(variable::reverse_count1 > 0){
                std::string reverse = variable::stack.top();
                variable::reverseq.push(reverse);
                variable::stack.pop();
                --variable::reverse_count1;
            }
            while(variable::reverse_count2 > 0){
                std::string reverse = variable::reverseq.front();
                variable::stack.push(reverse);
                variable::reverseq.pop();
                --variable::reverse_count2;
            }
        }
    }
}
/*
 *  Handling repeat and endrepeat commands.
 */
void repeatfunction(std::istream& in){
    int repeat_count = std::stoi(variable::stack.top());
    variable::stack.pop();
    std::queue<std::string> repeat;
    std::queue<std::string> copyrepeat;
    std::string s;
    while(in >> s){
        if(s.compare(variable::endrepeat)==0){
            for(int count = 0; count <repeat_count; ++count){
                while(!repeat.empty()){
                    command(repeat.front());
                    copyrepeat.push(repeat.front());
                    repeat.pop();
                }
                while(!copyrepeat.empty()){
                    repeat.push(copyrepeat.front());
                    copyrepeat.pop();
                }
            }
            return;
        }
        else{
            repeat.push(s);
        }
    }
}
int main(int argc, char* argv[]) {
    
    // setup the print out format for the precision required.
    std::cout.setf(std::ios::fixed,std::ios::floatfield);
    std::cout.precision(3);
    
    // open the file for reading
    std::ifstream in;
    in.open(argv[1]);
    // string to be read into
    std::string s;
    // read the file while we have input.
    
    while (in >> s) {
        //std::cout<<s<<std::endl;
        if (s.compare(variable::repeat)==0){
            //std::cout<<&in<<std::endl;
            repeatfunction(in);
        }
        //std::string result = command(s);
        //std::cout << result <<std::endl;
        else{
            command(s);
        }
    }
    
in.close();
}
