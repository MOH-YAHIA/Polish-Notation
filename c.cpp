#include<bits/stdc++.h>
using namespace std;
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using ordered_set=tree<long long,null_type,less<long long>,rb_tree_tag,tree_order_statistics_node_update>;
using multi_ordered_set=tree<long long,null_type,less_equal<long long>,rb_tree_tag,tree_order_statistics_node_update>;
#define ll long long
#define FAST ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define all(x) (x).begin(), (x).end()
//=======================================================================//
bool isOperator(string s)
{
  if(s=="*"||s=="/"||s=="^"||s=="+"||s=="-")  return true;
  return false;
}
bool isStronger(string op1,string op2)
{
  if(op1=="^")  return op2!="^";
  if(op1=="*" || op1=="/")
  {
      return op2=="+"|| op2=="-";
  }
  return false;
}
double calculate(char c,double x,double y)
{

  switch (c)
  {
  case '+':
    return x+y;
    break;
  case '-':
    return x-y;
    break;
  case '^':
    return pow(x,y);
    break;
  case '*':
    return x*y;
    break;
  case '/':
    return x/y;
    break;
  default:
  return 0;
    break;
  }
}
vector<string> postfix(vector<string> vr)
{
  stack<string>op;
  vector<string>res;
  int operators=0,numbers=0;
  for(int i=0; i<vr.size(); i++)
  {
      if(i<vr.size()-1 && !isOperator(vr[i]) && !isOperator(vr[i+1]))
          goto location;
      if(isOperator(vr[i]))
      {
        operators++;
        while(!op.empty() && !isStronger(vr[i],op.top()))
        {
          res.push_back(op.top());
          op.pop();
        }
        op.push(vr[i]);
      }else 
      {
         res.push_back(vr[i]);
         numbers++;
      }   
  }
  while(!op.empty())
  {
      res.push_back(op.top());
      op.pop();
  }
  if(operators!=numbers-1)  //invalid expression kind of more operators than numbers
  {
      location:
      res.clear(); //make vector empty
  }
  return res;
}
double valuOfPostfix(vector<string> vr)
{
  stack<double>st;
  for(string s:vr)
  {
    if(isOperator(s))
    {
      double x=st.top();
      st.pop();
      double y=st.top();
      st.pop();
      st.push(calculate(s[0],y,x));
    }else
      st.push(stod(s));
  }
  return st.top();
}
int main()
{
    FAST;
    int items;cin>>items;
    vector<string>vr(items);
    for(int i=0; i<items; i++)
      cin>>vr[i];
    vector<string>ans=postfix(vr);
    if(ans.empty()) cout<<"invaild expression\n";
    else
      cout<<valuOfPostfix(ans);


}