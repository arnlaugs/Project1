#include <iostream>
#include <cmath>
using namespace std;

/*double u(double x){
    return 1-(1-exp(-10))x-exp(-10x);
}*/


double f_analytic(double x){
    return (100*exp(-10*x));
}


/*double f(double a,double b, double c,double v, double v_pluss, double a_minus, double h){

    return (a*v_minus+b*v+c*v_pluss)/h^2;

}*/


int print_matrix(int n, double* a, double* b, double* c, double* v, double* tilde)
{
    cout << "| a  b c | v | tilde |" << endl;

    for(int i=0; i<n; i++){
        cout << "| " << *(a + i) << " " << *(b + i) << " " << *(c + i) << " | " << *(v + i) << " | "<< *(tilde + i) << " |" << endl;
    }
    return 0;
}


int main()
{
// INITIALIZATION
int n = 10;
double* v_vector = new double [n];
double* a_vector = new double [n];
double* b_vector = new double [n];
double* c_vector = new double [n];
double* tilde_vector = new double[n];

for(int i=0; i<n; i++){
    *(a_vector + i)=1.0;
    *(b_vector + i)=-2.0;
    *(c_vector + i)=1.0;
    *(tilde_vector + i)=f_analytic(i*(1.0/(n+1)));
}

print_matrix(n, a_vector, b_vector, c_vector, v_vector, tilde_vector);


// FORWARD SUBSTITUTION
for(int i=0; i<n; i++){
    *(tilde_vector+i) = *(tilde_vector+i) - *(tilde_vector+i-1) * (*(a_vector+i)/(*(b_vector+i)));
    *(b_vector+i+1) = *(b_vector+i+1) - *(c_vector+i) * (*(a_vector+i)/(*(b_vector+i)));
    *(a_vector+i) = *(a_vector+i) - *(b_vector+i) * (*(a_vector+i)/(*(b_vector+i))); // The same as writing *(a_vector + i) = 0;
}

cout << "Forward substitution gjennomføres." << endl;
print_matrix(n, a_vector, b_vector, c_vector, v_vector, tilde_vector);

// BACKWARD SUBSTITUTION
*(v_vector+(n-1)) = *(tilde_vector+n-1)/(*(b_vector+n-1));
cout << "tall: " << *(v_vector+(n-1)) << endl;

for(int i=n-2;i>-1;i--){
    *(v_vector+i)=(1.0/(*(b_vector+i)))*(*(tilde_vector+i) - *(c_vector+i)*(*(v_vector+i+1)));
}

cout << "Backward substitution gjennomføres." << endl;
print_matrix(n, a_vector, b_vector, c_vector, v_vector, tilde_vector);

}


