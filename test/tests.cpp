#include "gtest.h"
#include "tstack.h"
#include "tformula.h"
#include <iostream>
using namespace std;

TEST(TStack, can_create_instance_without_parameters) {
    ASSERT_NO_THROW(TStack s());
}

TEST(TStack, can_define_empty_statement) {
    TStack s(4);
    ASSERT_EQ(true, s.IsEmpty());
}

TEST(TStack, can_put_element) {
    TStack s(4);
    s.Put(5);
    ASSERT_EQ(5, s.TopElem());
}

TEST(TStack, stack_is_not_empty_after_put_operation) {
    TStack s(4);
    s.Put(5);
    ASSERT_NE(true, s.IsEmpty());
}

TEST(TStack, can_define_full_statement) {
    TStack s(2);
    s.Put(5);
    s.Put(6);
    ASSERT_EQ(true, s.IsFull());
}

TEST(TStack, cant_put_to_full_stack) {
    TStack s(2);
    s.Put(5);
    s.Put(6);
    s.Put(7);
    ASSERT_NE(DataOK, s.GetRetCode());
}

TEST(TStack, cant_get_from_empty_stack) {
    TStack s(2);
    s.Get();
    ASSERT_NE(DataOK, s.GetRetCode());
}

TEST(TStack, cant_check_top_element_from_empty_stack) {
    TStack s(2);
    s.TopElem();
    ASSERT_NE(DataOK, s.GetRetCode());
}

TEST(TStack, get_function_deletes_top_element) {
    TStack s(4);
    s.Put(3);
    s.Put(4);
    s.Put(5);
    for (int i = 0; i < 3; ++i)
        s.Get();
    ASSERT_EQ(true, s.IsEmpty());
}

TEST(TStack, TopElem_function_doesnt_delete_top_element) {
    TStack s(4);
    s.Put(3);
    s.Put(4);
    s.Put(5);
    for (int i = 0; i < 3; ++i)
        s.TopElem();
    ASSERT_NE(true, s.IsEmpty());
}

TEST(TStack, can_perform_multiple_puts) {
    TStack s(20);
    for (int i = 0; i < 20; ++i) {
        s.Put(i);
        EXPECT_EQ(DataOK, s.GetRetCode());
    }
    s.Put(20);
    ASSERT_NE(DataOK, s.GetRetCode());
}

TEST(TStack, can_perform_multiple_gets) {
    TStack s(20);
    for (int i = 0; i < 20; ++i)
        s.Put(i);
    for (int i = 0; i < 20; ++i) {
        s.Get();
        EXPECT_EQ(DataOK, s.GetRetCode());
    }
    s.Get();
    ASSERT_NE(DataOK, s.GetRetCode());
}

TEST(TStack, cant_create_stack_with_negative_number_of_elements) {
    ASSERT_ANY_THROW(TStack s(-1));
}

TEST(TFormula, expression1) {
    TFormula f("2+2*2");
    ASSERT_EQ(6., f.FormulaCalculator());
}

TEST(TFormula, expression2) {
    TFormula f("(2+2)*2");
    ASSERT_EQ(8., f.FormulaCalculator());
}

TEST(TFormula, expression3) {
    TFormula f("4.5");
    ASSERT_EQ(4.5, f.FormulaCalculator());
}

TEST(TFormula, expression4) {
    TFormula f("(4.5)");
    ASSERT_EQ(4.5, f.FormulaCalculator());
}

TEST(TFormula, expression5) {
    TFormula f("4+(4*7)-28-4");
    ASSERT_EQ(0., f.FormulaCalculator());
}

TEST(TFormula, expression6) {
    TFormula f("(2*2)*(9+(10+((15)*20)))");
    ASSERT_EQ(1276., f.FormulaCalculator());
}

TEST(TFormula, expression7) {
    TFormula f("(9+10)*7/10");
    ASSERT_EQ(13.3, f.FormulaCalculator());
}

TEST(TFormula, expression8) {
    TFormula f("1/78");
    ASSERT_EQ(1./78, f.FormulaCalculator());
}

TEST(TFormula, expression9) {
    TFormula f("(1+0.0)/2/3/4/5");
    ASSERT_EQ(1./2/3/4/5, f.FormulaCalculator());
}

TEST(TFormula, expression10) {
    TFormula f("(0.5*(74645.32 - 1))-2358+13.24");
    ASSERT_EQ((0.5*(74645.32 - 1))-2358+13.24, f.FormulaCalculator());
}

TEST(TFormula, expression11) {
    TFormula f("2 + 1 - 10*1*((40)/(18/9)/2)");
    ASSERT_EQ(2 + 1 - 10*1*((40)/(18/9)/2), f.FormulaCalculator());
}

TEST(TFormula, expression12) {
    TFormula f("2 + 1 - 10*1*((40)+(18/9)+2)");
    ASSERT_EQ(2 + 1 - 10*1*((40)+(18/9)+2), f.FormulaCalculator());
}

TEST(TFormula, expression13) {
    TFormula f("(1+(2+3))");
    ASSERT_EQ(1+(2+3), f.FormulaCalculator());
}

TEST(TFormula, expression14) {
    TFormula f("4.5)");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, expression15) {
    TFormula f("(4.5");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, expression16) {
    TFormula f("(((4.5)))");
    f.FormulaCalculator();
    ASSERT_EQ(4.5, f.FormulaCalculator());
}

TEST(TFormula, expression17) {
    TFormula f("(4.5+)");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, expression18) {
    TFormula f("(4.5++8)");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, expression19) {
    TFormula f("4a5");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, expression20) {
    TFormula f("64.464+(3534534.2       -  345.54)*((2.1-9.34)/43.3)/(4354.2/65.35)/546.2");
    ASSERT_EQ(64.464+(3534534.2-345.54)*((2.1-9.34)/43.3)/(4354.2/65.35)/546.2, f.FormulaCalculator());
}

TEST(TFormula, expression21) {
    TFormula f("((((((10))))))");
    ASSERT_EQ(10, f.FormulaCalculator());
}

TEST(TFormula, expression22) {
    TFormula f("4,5");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, expression23) {
    TFormula f("4!");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, expression24) {
    TFormula f("((10+)5)");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, expression25) {
    TFormula f("5*(1+(10))");
    ASSERT_EQ(55, f.FormulaCalculator());
}

TEST(TFormula, expression26) {
    TFormula f("(10())");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, expression27) {
    TFormula f("(1(+5))");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, expression28) {
    TFormula f("(1(+5))");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, expression29) {
    TFormula f("(1+7+(5)+)");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, expression30) {
    TFormula f("(1+(2+3)");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, expression31) {
    TFormula f("(1+(2)+3)");
    ASSERT_EQ(6, f.FormulaCalculator());
}

TEST(TFormula, expression32) {
    TFormula f("(((1/(((1.3))+((((((9.0))))))))))");
    ASSERT_EQ(1./(1.3+9.0), f.FormulaCalculator());
}

TEST(TFormula, expression33) {
    TFormula f("1+()");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, expression34) {
    TFormula f("()+1");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, expression35) {
    TFormula f("+()1");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, expression36) {
    TFormula f("1()+1");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, expression37) {
    TFormula f("1+()1");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}

TEST(TFormula, expression38) {
    TFormula f("1(/2)");
    ASSERT_ANY_THROW(f.FormulaCalculator());
}
