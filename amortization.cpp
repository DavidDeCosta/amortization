/*
    This program uses information from a file to create an amortization table
*/
//Programmer: < David DeCosta>
//Date of last modification: < 2 April 2021>

#include <iostream>
#include <fstream>
#include <math.h> // for pow()
#include <iomanip>

using namespace std;

//prototypes
double monthly_payment(double loanAmount, double interestRate, int totalMonths);

int main(){

    ifstream i_stream;
    ofstream o_stream;
    char fileName[50];
    char name[31];
    double loanAmount, interestRate,Balance,principle;
    int totalMonths;

    o_stream.open("Loans.txt");

    do{
        i_stream.clear();
        cout << "Enter the name of your file : ";
        cin >> fileName;
        i_stream.open(fileName);
    }while(i_stream.fail());

    while(!i_stream.eof()){
        loanAmount = 0;
        interestRate = 0;
        totalMonths = 0;
        i_stream.get(name, 31);

        while(i_stream.peek()!= '\n'){
            i_stream >> loanAmount >> interestRate >> totalMonths;
            monthly_payment(loanAmount,interestRate,totalMonths);
            double payment = monthly_payment(loanAmount,interestRate,totalMonths);
            Balance = loanAmount;
            interestRate = interestRate /12 /100;
            principle = payment - (Balance * interestRate);
            o_stream << endl << setw(8) << "Payment" << setw(12)<< "Amount" << setw(16) << "Interest" << setw(16)<< "Principal" << setw(15) 
                     << "Balance" <<endl;
            o_stream << name << setw(35) << loanAmount << endl;
            for(int n = 1; n <= totalMonths; n++){
                o_stream.setf(ios:: showpoint | ios:: fixed);
                o_stream << setprecision(2);
                o_stream << setw(4) << n;
                o_stream << setw(16) << payment;
                o_stream << setw(15) << Balance * interestRate;
                o_stream << setw(15) << principle;
                o_stream << setw(15) << Balance << endl;
                Balance -= principle;
                principle = payment -(Balance * interestRate);
            }
        }
        i_stream >> ws;

    }


    i_stream.close();
    o_stream.close();

    return 0;
}

double monthly_payment(double loanAmount, double interestRate, int totalMonths){

    interestRate = interestRate / 12/100; // turns the interest rate into a decimal
    double onePlusR = (1 + interestRate); // adds one to the interest rate
    double d = pow(onePlusR,totalMonths); // raises the expression (1+r) to the total months
    double k = interestRate * d; // multiplies the interest rate by the expression (1+interest rate)^ months
    double onePlusRminusOne = d -1; // takes the expression (1+r)^n and subtracts 1
    double montly_payment = loanAmount * k/onePlusRminusOne; // calculates the montly payment


    return montly_payment;


}