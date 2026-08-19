/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "ulimitedrational.h"

UnlimitedInt *compare1(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if (i1->get_size() > i2->get_size())
    {
        return i1;
    }
    else if (i1->get_size() < i2->get_size())
    {
        return i2;
    }
    else
    {
        for (int i = i1->get_size(); i > 0; i--)
        {
            if (i1->get_array()[i] > i2->get_array()[i])
            {
                return i1;
            }
            else if (i1->get_array()[i] < i2->get_array()[i])
            {
                return i2;
            }
        }
        return i1;
    }
}

UnlimitedInt *hcf(UnlimitedInt *i1, UnlimitedInt *i2)
{
    if(i1->to_string()=="0" || i2->to_string()=="0"){
        return new UnlimitedInt("1");
    }
    if (compare1(i1, i2) == i1)
    {
        if (UnlimitedInt::mod(i1, i2)->to_string() == "0")
        {
            return new UnlimitedInt(i2->to_string());
        }
        else
        {
            UnlimitedInt *dummy1 = new UnlimitedInt(i1->to_string());
            UnlimitedInt *dummy2 = new UnlimitedInt(i2->to_string());
            while (UnlimitedInt::mod(dummy1, dummy2)->to_string() != "0")
            {
                string s1 = dummy1->to_string();
                string s2 = dummy2->to_string();
                delete dummy1;
                delete dummy2;
                dummy1 = new UnlimitedInt(s2);
                dummy2 = new UnlimitedInt(UnlimitedInt::mod(new UnlimitedInt(s1), new UnlimitedInt(s2))->to_string());
            }
            return dummy2;
        }
    }
    else
    {
        if (UnlimitedInt::mod(i2, i1)->to_string() == "0")
        {
            return new UnlimitedInt(i1->to_string());
        }
        else
        {
            UnlimitedInt *dummy1 = new UnlimitedInt(i2->to_string());
            UnlimitedInt *dummy2 = new UnlimitedInt(i1->to_string());
            while (UnlimitedInt::mod(dummy1, dummy2)->to_string() != "0")
            {
                string s1 = dummy1->to_string();
                string s2 = dummy2->to_string();
                delete dummy1;
                delete dummy2;
                dummy1 = new UnlimitedInt(s2);
                dummy2 = new UnlimitedInt(UnlimitedInt::mod(new UnlimitedInt(s1), new UnlimitedInt(s2))->to_string());
            }
            return dummy2;
        }
    }
}

UnlimitedRational ::UnlimitedRational()
{
    p = new UnlimitedInt("0");
    q = new UnlimitedInt("1");
}

UnlimitedRational ::UnlimitedRational(UnlimitedInt *num, UnlimitedInt *den)
{
    p = num;
    q = den;
}

UnlimitedRational :: ~UnlimitedRational(){
    delete p;
    delete q;
}

UnlimitedInt* UnlimitedRational :: get_p(){
    return p;
}

UnlimitedInt* UnlimitedRational :: get_q(){
    return q;
}

string UnlimitedRational :: get_p_str(){
    return p->to_string();
}

string UnlimitedRational :: get_q_str(){
    return q->to_string();
}

string UnlimitedRational :: get_frac_str(){
    if(q->to_string()=="0"){
        return "0/0";
    }
    if(p->to_string()=="0"){
        return "0/" + q->to_string();
    }
    UnlimitedInt* dummy1 = UnlimitedInt::div(p, hcf(p,q));
    UnlimitedInt* dummy2 = UnlimitedInt::div(q, hcf(p,q));
    string s = "";
    s = dummy1->to_string();
    s = s + "/" + dummy2->to_string();
    return s;
}

UnlimitedRational* UnlimitedRational:: add(UnlimitedRational* i1, UnlimitedRational* i2){
    if((i1->get_q_str())=="0" || (i2->get_q_str())=="0"){
        return new UnlimitedRational(new UnlimitedInt("0"), new UnlimitedInt("0"));
    }
    UnlimitedInt* p1 = new UnlimitedInt(i1->get_p_str());
    UnlimitedInt* p2 = new UnlimitedInt(i2->get_p_str());
    UnlimitedInt* q1 = new UnlimitedInt(i1->get_q_str());
    UnlimitedInt* q2 = new UnlimitedInt(i2->get_q_str());
    UnlimitedInt* p = new UnlimitedInt(UnlimitedInt::add(new UnlimitedInt(UnlimitedInt::mul(p1,q2)->to_string()), new UnlimitedInt(UnlimitedInt::mul(p2,q1)->to_string()))->to_string());
    UnlimitedInt* q = new UnlimitedInt(UnlimitedInt::mul(q1, q2)->to_string());
    delete p1;
    delete p2;
    delete q1;
    delete q2;
    UnlimitedInt* h = hcf(p,q);
    UnlimitedRational* i = new UnlimitedRational(UnlimitedInt::div(p,h), UnlimitedInt::div(q,h));
    delete h;
    delete p;
    delete q;
    return i;
}

UnlimitedRational* UnlimitedRational:: sub(UnlimitedRational* i1, UnlimitedRational* i2){
    if((i1->get_q_str())=="0" || (i2->get_q_str())=="0"){
        return new UnlimitedRational(new UnlimitedInt("0"), new UnlimitedInt("0"));
    }
    UnlimitedInt* p1 = new UnlimitedInt(i1->get_p_str());
    UnlimitedInt* p2 = new UnlimitedInt(i2->get_p_str());
    UnlimitedInt* q1 = new UnlimitedInt(i1->get_q_str());
    UnlimitedInt* q2 = new UnlimitedInt(i2->get_q_str());
    UnlimitedInt* p = new UnlimitedInt(UnlimitedInt::sub(new UnlimitedInt(UnlimitedInt::mul(p1,q2)->to_string()), new UnlimitedInt(UnlimitedInt::mul(p2,q1)->to_string()))->to_string());
    UnlimitedInt* q = new UnlimitedInt(UnlimitedInt::mul(q1, q2)->to_string());
    delete p1;
    delete p2;
    delete q1;
    delete q2;
    UnlimitedInt* h = hcf(p,q);
    // cout<<h->to_string()<<endl;
    UnlimitedRational* i = new UnlimitedRational(UnlimitedInt::div(p,h), UnlimitedInt::div(q,h));
    delete h;
    delete p;
    delete q;
    return i;
}

UnlimitedRational* UnlimitedRational:: mul(UnlimitedRational* i1, UnlimitedRational* i2){
    UnlimitedInt* p = UnlimitedInt::mul(new UnlimitedInt(i1->get_p_str()), new UnlimitedInt(i2->get_p_str()));
    UnlimitedInt* q = UnlimitedInt::mul(new UnlimitedInt(i1->get_q_str()), new UnlimitedInt(i2->get_q_str()));
    UnlimitedInt* h = hcf(p,q);
    UnlimitedRational* i = new UnlimitedRational(UnlimitedInt::div(p,h), UnlimitedInt::div(q,h));
    delete p;
    delete q;
    delete h;
    return i;
}

UnlimitedRational* UnlimitedRational::div(UnlimitedRational* i1, UnlimitedRational* i2){
    if(i1->get_q_str()=="0" || i2->get_p_str()=="0" || i2->get_q_str()=="0"){
        return new UnlimitedRational(new UnlimitedInt("0"), new UnlimitedInt("0"));
    }
    UnlimitedInt* p = UnlimitedInt::mul(new UnlimitedInt(i1->get_p_str()), new UnlimitedInt(i2->get_q_str()));
    UnlimitedInt* q = UnlimitedInt::mul(new UnlimitedInt(i1->get_q_str()), new UnlimitedInt(i2->get_p_str()));
    UnlimitedInt* h = hcf(p,q);
    UnlimitedRational* i = new UnlimitedRational(UnlimitedInt::div(p,h), UnlimitedInt::div(q,h));
    delete p;
    delete q;
    delete h;
    return i;
}
// #include<iostream>

// int main()
// {
//     UnlimitedInt* num = new UnlimitedInt("277568815104");
//     UnlimitedInt* den = new UnlimitedInt("665416609183179841");

//     UnlimitedRational* temp = new UnlimitedRational(num,den);
//         cout<<temp->get_frac_str()<<endl;

//     UnlimitedRational* divs = new UnlimitedRational(UnlimitedInt::mul(new UnlimitedInt("5"),new UnlimitedInt("42")),new UnlimitedInt("1"));
//     UnlimitedRational* difjf = UnlimitedRational::div(divs,temp);

//     cout<<temp->get_frac_str()<<endl;
//     std::cout<<difjf->get_frac_str()<<endl;
//     UnlimitedRational* difghj = UnlimitedRational:: div(difjf, temp);
//     std::cout<<difghj->get_frac_str();

// }