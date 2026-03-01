#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

using namespace std;






                // Term Struct and Equation class and Solver class

            





////////////////////////
////////////////////////



// تمثيل حد واحد (Variable + Coefficient)


struct Term {
    float coeff;
    string var;

};

class Equation {

public:

    vector<Term> terms;
    float rhs = 0;

    // تحويل المعادلة للشكل الصحيح يعني - (تجميع المتغيرات المكررة وترتيبها)

    void simplify() {
        vector<Term> temp;
        for (int i = 0; i < terms.size(); i++) {
            bool found = false;
            for (int j = 0; j < temp.size(); j++) {
                if (temp[j].var == terms[i].var) {
                    temp[j].coeff += terms[i].coeff;
                    found = true;
                    break;
                }
            }
            if (!found)
                temp.push_back(terms[i]);
        }






        // ترتيب المتغيرات أبجدياً (Selection Sort بسيط لتجنب Lambda)
        for (int i = 0; i < (int)temp.size() - 1; i++) {
            for (int j = i + 1; j < temp.size(); j++) {
                if (temp[i].var > temp[j].var) swap(temp[i], temp[j]);
            }
        }
        terms = temp;
    }








    // تحويل الكائن إلى نص للطباعة

    string toString() {
        ostringstream oss;
        for (int i = 0; i < terms.size(); i++) {
            float c = terms[i].coeff;
            if (i > 0 && c > 0) oss << "+";
            if (c == 1) oss << terms[i].var;
            else if (c == -1) oss << "-" << terms[i].var;
            else oss << c << terms[i].var;
        }
        oss << "=" << rhs;
        return oss.str();
    }
};











////////////////////////
////////////////////////




class Solver {



    vector<Equation> eqs;
    vector<string> all_vars;




    // دالة لاستخراج المعامل واسم المتغير من النص
    void parseTerm(string s, Equation& eq) {
        int x_idx = -1;
        for (int i = 0; i < s.length(); i++) {
            if (isalpha(s[i]))
            { x_idx = i; 
            break; }
        }
        if (x_idx == -1) { // إذا كان رقماً فقط بدون متغير
            eq.rhs -= atof(s.c_str());
        }
        else {



            Term t;
            t.var = s.substr(x_idx);
            string co = s.substr(0, x_idx);
            if (co == "" || co == "+") t.coeff = 1;
            else if (co == "-") t.coeff = -1;
            else t.coeff = atof(co.c_str());
            eq.terms.push_back(t);


        }
    }






public:




    void readEquations(int n) {
        for (int i = 0; i < n; i++) {
            string line; cin >> line;
            size_t eq_pos = line.find('=');
            string left = line.substr(0, eq_pos);
            Equation eq;
            eq.rhs = atof(line.substr(eq_pos + 1).c_str());

            string current = "";
            for (int j = 0; j < left.length(); j++) {
                if (j > 0 && (left[j] == '+' || left[j] == '-')) {
                    parseTerm(current, eq);
                    current = "";
                }
                current += left[j];
            }
            parseTerm(current, eq);
            eq.simplify();
            eqs.push_back(eq);
        }
        updateVarList();
    }






    void updateVarList() {
        all_vars.clear();
        for (int i = 0; i < eqs.size(); i++) {
            for (int j = 0; j < eqs[i].terms.size(); j++) {
                bool exists = false;
                for (int k = 0; k < all_vars.size(); k++) {
                    if (all_vars[k] == eqs[i].terms[j].var) exists = true;
                }
                if (!exists) all_vars.push_back(eqs[i].terms[j].var);
            }
        }
        sort(all_vars.begin(), all_vars.end());
    }






    void execute() {
        string cmd;
        while (cin >> cmd && cmd != "quit") {
            if (cmd == "num_vars") {
                cout << all_vars.size() << endl;
            }
            else if (cmd == "equation") {
                int idx; cin >> idx;
                cout << eqs[idx - 1].toString() << endl;
            }
            else if (cmd == "column") {
                string v; cin >> v;
                for (int i = 0; i < eqs.size(); i++) {
                    float val = 0;
                    for (int j = 0; j < eqs[i].terms.size(); j++) {
                        if (eqs[i].terms[j].var == v) val = eqs[i].terms[j].coeff;
                    }
                    cout << val << endl;
                }
            }
        }
    }
 









    };
















int main() {

                            // run it on CMD
     


    int n;
    if (!(cin >> n))
        return 0;


    Solver mySolver;

    mySolver.readEquations(n);
    mySolver.execute();
   
    
    


    
    
    
    
    
    
    
    
    
    return 0;



     

}