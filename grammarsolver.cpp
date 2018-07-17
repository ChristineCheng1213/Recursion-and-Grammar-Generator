// This is the CPP file you will edit and turn in. (TODO: Remove this comment!)

#include "grammarsolver.h"
#include <fstream>
#include "filelib.h"
#include "vector.h"
#include "map.h"
#include "strlib.h"
#include "set.h"
#include "error.h"
#include "random.h"
using namespace std;

//ask what to do about () in expression.txt
//repeated used adj. matters? e.g. the wonderful faulty fat big wonderful fat mother
void checkIfTerminal(Map<string, Vector<string> >& g, string s, Set<string>& terminals);
string generateGrammarString(const Map<string, Vector<string> >& g, string input);


Vector<string> grammarGenerate(istream& input, string symbol, int times) {

    Map<string, Vector<string> > grammar;
    Vector<string> result;

    //build map
    string line;
    while (getline(input, line)) {
        Vector<string> v = stringSplit(line, "::=");
        if (grammar.containsKey(v[0])){
            throw "exception: repeated definition of non-terminal";
        } else {
            Vector<string> rules = stringSplit(v[1], "|");
            grammar[v[0]] = rules;
        }
    }

    for (int i = 0; i < times; i++){
        result.add(generateGrammarString(grammar, symbol));
    }

    return result;           // this is only here so it will compile
}



string generateGrammarString(const Map<string, Vector<string> >& g, string input){

    string result = "";

    if (g.containsKey(input)){
        //is non-terminal, do recursively

        int index = randomInteger(0, g[input].size() - 1);
        string ruleChosen = g[input][index];


        if (ruleChosen.find(" ") == string::npos){
            //contains only one token
            result += generateGrammarString(g, ruleChosen);
        } else {
            //contains multiple tokens
            Vector<string> tokens = stringSplit(ruleChosen, " ");
            for (string t : tokens ){
                result += generateGrammarString(g, t);
            }
        }

    } else {
        //terminal, return itself
        result = input + " ";
    }

    return result;
}
