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

  } ;

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



    //   FUNC 1  parseTerm()


    
    // دالة لاستخراج المعامل واسم المتغير من النص    

    //"3x2" → "x2"
  
    /*  
    
    "3x2" → "3"

     "-x1" → "-"
      "x3" → "" 
        
    

    */

    void parseTerm(string s, Equation& eq) {
        int x_idx = -1;
        for (int i = 0; i < s.length(); i++) {
            if (isalpha(s[i]))
            {
                x_idx = i; 
            break;
            
            }
        }


        if (x_idx == -1) { // إذا كان رقماً فقط بدون متغير
            eq.rhs -= atof(s.c_str());
        }
        else {
             

            Term t;
            t.var = s.substr(x_idx);
            string co = s.substr(0, x_idx);
            if (co == "" || co == "+") t.coeff = 1;
            else if (co == "-")
                t.coeff = -1;
            else
                t.coeff = atof(co.c_str());

            eq.terms.push_back(t);


        }
    }





    ///////////////////////
    //////////////////////




public:


    // FUNC 2 readEquations()





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
            
            //  تحليل آخر حد بعد انتهاء اللوب   
 //   آخر حد مش وراه + ولا -

              //     فمش هيتحلل جوه اللوب

            //تبسيط وتخزين المعادلة  
            eq.simplify();
            eqs.push_back(eq);
        }
        updateVarList();
    }





    ///////////////////////
    //////////////////////




    // FUNC 3 updateVarList()

    void updateVarList() {
        all_vars.clear();
        for (int i = 0; i < eqs.size(); i++) {
            for (int j = 0; j < eqs[i].terms.size(); j++) {
                bool exists = false;
                for (int k = 0; k < all_vars.size(); k++) {
                    if (all_vars[k] == eqs[i].terms[j].var) 
                        exists = true;
                }
                if (!exists) 
                    all_vars.push_back(eqs[i].terms[j].var);
            }
        }
        sort(all_vars.begin(), all_vars.end());
    }













    ///////////////////////
    //////////////////////  





    Equation addEq(Equation a, Equation b) {
        Equation res = a;
        for (int i = 0; i < b.terms.size(); i++)
            res.terms.push_back(b.terms[i]);
        res.rhs += b.rhs;
        res.simplify();
        return res;
    }







    ///////////////////////
    //////////////////////


    Equation subEq(Equation a, Equation b) {
        Equation res = a;
        for (int i = 0; i < b.terms.size(); i++) {
            Term t = b.terms[i];
            t.coeff *= -1;
            res.terms.push_back(t);
        }
        res.rhs -= b.rhs;
        res.simplify();
        return res;
    }




    //////////////////////
    ///////////////////////


    Equation substituteVar(string var, Equation eq1, Equation eq3) {

        Equation result = eq1;

        // معامل المتغير في المعادلة 1
        float a = getCoeff(eq1, var);

        // لو المتغير مش موجود → مفيش تعويض
        if (a == 0)
            return result;

        // نطرح a * equation3 من equation1
        for (int i = 0; i < eq3.terms.size(); i++) {
            Term t = eq3.terms[i];
            t.coeff *= -a;
            result.terms.push_back(t);
        }

        result.rhs -= a * eq3.rhs;

        result.simplify();
        return result;
    }









    ///////////////////////
    //////////////////////


    ///////////////////////
    //////////////////////






    float getCoeff(Equation& eq, string var) {
        for (int i = 0; i < eq.terms.size(); i++)
            if (eq.terms[i].var == var)
                return eq.terms[i].coeff;
        return 0;
    }



    ///////////////////////
    //////////////////////


    vector<vector<float>> getCoeffMatrix() {

        int n = eqs.size();
        vector<vector<float>> mat(n, vector<float>(n));

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                mat[i][j] = getCoeff(eqs[i], all_vars[j]);

        return mat;
    }











    ///////////////////////
    //////////////////////


       //////////////////////
    //////////////////////


    float determinant(vector<vector<float>> m) {
        int n = m.size();
        if (n == 1) return m[0][0];

        float det = 0;
        for (int p = 0; p < n; p++) {
            vector<vector<float>> sub(n - 1, vector<float>(n - 1));
            for (int i = 1; i < n; i++) {
                int colIndex = 0;
                for (int j = 0; j < n; j++) {
                    if (j == p) continue;
                    sub[i - 1][colIndex++] = m[i][j];
                }
            }
            det += (p % 2 == 0 ? 1 : -1) * m[0][p] * determinant(sub);
        }
        return det;
    } 

     



    ///////////////////////
    //////////////////////

    


















// FUNC 4  execute()



                                            // need update

    void execute() {

        string cmd;

        while (cin >> cmd && cmd != "quit") {

            //   D : Coefficient Matrix
            if (cmd == "D") {

                if (cin.peek() == '\n') {
                    // D فقط
                    vector<vector<float>> mat = getCoeffMatrix();

                    for (int i = 0; i < mat.size(); i++) {
                        for (int j = 0; j < mat.size(); j++)
                            cout << mat[i][j] << " ";
                        cout << endl;
                    }
                }
                else {
                    // D x1
                    string var;
                    cin >> var;

                    vector<vector<float>> mat = getCoeffMatrix();

                    int col = -1;
                    for (int i = 0; i < all_vars.size(); i++)
                        if (all_vars[i] == var)
                            col = i;

                    for (int i = 0; i < mat.size(); i++)
                        mat[i][col] = eqs[i].rhs;

                    for (int i = 0; i < mat.size(); i++) {
                        for (int j = 0; j < mat.size(); j++)
                            cout << mat[i][j] << " ";
                        cout << endl;
                    }
                }
            }

            //   D_value
            else if (cmd == "D_value") {

                vector<vector<float>> mat = getCoeffMatrix();
                cout << determinant(mat) << endl;
            }

            //   solve
            else if (cmd == "solve") {

                vector<vector<float>> mat = getCoeffMatrix();
                float D = determinant(mat);

                if (fabs(D) < 1e-6) {
                    cout << "No Solution" << endl;
                    continue;
                }

                for (int v = 0; v < all_vars.size(); v++) {

                    vector<vector<float>> temp = mat;

                    for (int i = 0; i < eqs.size(); i++)
                        temp[i][v] = eqs[i].rhs;

                    float Dv = determinant(temp);
                    cout << all_vars[v] << "=" << Dv / D << endl;
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