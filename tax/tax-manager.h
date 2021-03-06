#pragma once
#include <iostream>
#include <string>
#include "finance-info.h"
#include "tax-submitter.h"
#include "tax-calculator.h"
#include "tax-calculator-factory.h"
using namespace std;


class TaxManager
{          
    FinancialInfoSource *source;
    //TaxCalculator *calculator;
    TaxCalculatorFactory * calculatorFactory;
    TaxSubmitter *submitter;
    public:      

        //default dependencies
        TaxManager()
        {
            this->calculatorFactory=new SimpleTaxCalculatorFactory();
            this->source = new FixedFinancialInfoSource();            
            this->submitter = new ConsoleTaxSubmitter();
        }

        void setFinancialInfoSource(FinancialInfoSource* source){ this->source=source;}
        void setTaxCalculatorFactory(TaxCalculatorFactory* calculatorFactory){ this->calculatorFactory=calculatorFactory;}
        void setTaxSubmitter(TaxSubmitter *submitter){ this->submitter=submitter;}


        void fileTax(string pan, int year){
            //Step 1 get the financial details;
            FinancialInfo info= source->fetchData(pan,year);

            //Step 2 calculate tax
            TaxCalculator * calculator= calculatorFactory->forYear(year);
            int tax = calculator->calculateTax(info);      

            //Step 3 submit the tex
            submitter->submitTax(pan,year,tax);

        }
        
};