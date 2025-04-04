#include "lexic.h"

void Lexic::transition(char c){
    // std::cout << symbol << std::endl;
    // std::cout << state << std::endl;
    // std::cout << c << std::endl;

    switch(state){
        case 0:
            if(isalpha(c)){
                symbol += c; 
                state = 1;
            }
            else if(c == '0' || c == '1'){
                symbol += c;
                state = 3;
            }
            else if(isdigit(c)){
                symbol += c;
                state = 4;
            }
            else if(c != '\n' && c != ' ' && c != '\0'){
                state = -1;
                symbol += c;
            }

            break;
        case 1:
            if(isalpha(c)){
                symbol += c;
                if(symbol == "ILOAD" || symbol == "DUP" || symbol == "BIPUSH"){state = 2;}
            }
            else{
                state = -1;
                symbol += c;
            }

            break;
        case 2:
            if(c == '\n' || c == ' ' || c == '\0'){
                insert_token("INSTRUCTION");
                state = 0;
            }
            else{
                state = -1;
                symbol += c;
            }
            
            break;
        case 3:
            if(symbol.size() < 8 && (c == '1' || c == '0')){ 
                symbol += c;
            }
            else if(isdigit(c)){ // Isso pode ser confuso, mas se um numero de 0 e 1 tiver mais de 8 bits, irá ser considerado como um número decimal
                symbol += c;
                state = 4;
            }
            else if(c == '\n' || c == ' ' || c == '\0'){ 
                if(symbol.size() == 8){
                    insert_token("BYTE");
                } else{
                    insert_token("NUMBER");
                }

                state = 0;
            }
            else{
                state = -1;
                symbol += c;
            }

            break;
        case 4:
            if(isdigit(c)){
                symbol += c;
            }
            else if(c == '\n' || c == ' ' || c == '\0'){
                insert_token("NUMBER");
                state = 0;
            }
            else{
                state = -1;
                symbol += c;
            }

            break;
    }

}

void Lexic::insert_token(std::string classifier){
    token temp;

    temp.classifier = classifier;
    temp.content = symbol;

    symbol.clear();
    table.push_back(temp);

    state = 0;
}

void Lexic::print_table(){
    for(token t : table){
        std::cout << t.classifier << "  " << t.content << std::endl;
    }
}

void Lexic::start(){
    state = 0;
    symbol.clear();
    table.clear();
}

void Lexic::end(){
    if(state == -1 || state == 1){
        throw "[ERRO] Palavra \'" + symbol + "\' invalida!";
    }

    switch(state){
        case 2:
            insert_token("INSTRUCTION");
            break;
        case 3:
            if(symbol.size() == 8){
                insert_token("BYTE");
            } else{
                insert_token("NUMBER");
            }
            break;
        case 4:
            insert_token("NUMBER");
            break;
    }

    // print_table();
}