//Name: Patience Lamb
//Semester: Spring 2022
//Date: January 24, 2021
//Email:lambpati@isu.edu
//Brief: Calculates the size of payments and the total paid over the life of the loan.
//       All the values for APR, amount of years are doubles to allow for fractional total payment amounts and fractional apr.
//       Years are expressed in an integer value.

#include <iostream>
#include <cmath>

// Calculates factor using APR and the number of years
double calculateFactor(double aprPercent, int totalPayments){
    double decIntPerPayment = (aprPercent/100)/12;
    double factor = (1-pow((1+decIntPerPayment),(-1*totalPayments*12)))/decIntPerPayment;
    return factor;
}

// Calculates monthly payment using loan amount and calculated factor
double calculatePayment(double loanAmount, double factor){
    double paymentSize = loanAmount/factor;

    return paymentSize;
}

int main(int argc, char const *argv[])
{
    double apr;
    int years;
    double paymentAmt;
    char yN;

    bool loop = true;
    while(loop){
        //User inputs
        std::cout << "Enter percent APR:" << std::endl;
        std::cin >> apr;
        std::cout << "Enter year amount:" << std::endl;
        std::cin >> years;
        std::cout << "Enter total loan amount:" << std::endl;
        std::cin >> paymentAmt;

        double payment = calculatePayment(paymentAmt, calculateFactor(apr,years));

        std::cout << "Payment amount: $" << payment << std::endl;
        std::cout << "Recalculate payment amount? Y/n" << std::endl;
        std::cin >> yN;
        if(yN == 'n'){
            loop = false;
        }
    }
    return 0;
}
