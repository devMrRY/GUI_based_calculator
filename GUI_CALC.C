#include<math.h>
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
COORD coord={0,0};
void gotoxy(int x,int y){
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}//function for gotoxy in codeblocks
//
void push(char*);
void pop();
void push1(char*);
void pop1();
int priority(char *);
void traversep();
void intopost();
//
void char_to_double(int);
void eval();
void push_num(double *);
void pop_post_stak();
double add(double *,double *);
double sub(double *,double *);
double mul(double *,double *);
double div(double *,double *);
double power(double *,double *);
double a[10]={0.0},stak[10],p;
int ipost,j=0,top_post=-1;
char stack[30],postfix_exp[60];
int top=-1,topa=-1,topp=-1,i;
//
void layout();
void insert(char);
void extract();
void traverse();
void solve();               //this function runs whenever = is pressed
void clr();
char s[20];
int  topstart=-1;

 main(){
 int gd=0,gm,x=100,y=50;
 char chr;
 initgraph(&gd,&gm,"");
 while(1){
 layout();
 if(chr==50)
  y+=5;
 else if(chr==52)
  x-=5;
 else if(chr==54)
  x+=5;
 else if(chr==56)
  y-=5;

 circle(x,y,3);
 setfillstyle(SOLID_FILL,WHITE);
 floodfill(x,y,WHITE);
 chr=getch();
 if(x>10&&x<30&&y>92&&y<115) { if(chr==13) insert('7');}
 else if(x>35&&x<55&&y>92&&y<115) { if(chr==13) insert('8');}
 else if(x>60&&x<80&&y>92&&y<115) { if(chr==13) insert('9');}
 else if(x>85&&x<105&&y>92&&y<115)
 { if(chr==13){
   if((s[topstart]>=48&&s[topstart]<=57)||s[topstart]==')')
   insert('/');
   else if(s[topstart]=='('){}
   else{
   extract();
   insert('/');}
   }
  }
 else if(x>110&&x<138&&y>92&&y<115) { if(chr==13) exit(0);}
 else if(x>141&&x<171&&y>92&&y<115) { if(chr==13) clr();}
 else if(x>10&&x<30&&y>123&&y<146) { if(chr==13) insert('4');}
 else if(x>35&&x<55&&y>123&&y<146) { if(chr==13) insert('5');}
 else if(x>60&&x<80&&y>123&&y<146) { if(chr==13) insert('6');}
 else if(x>85&&x<105&&y>123&&y<146)
 { if(chr==13){
   if((s[topstart]>=48&&s[topstart]<=57)||s[topstart]==')')
   insert('*');
   else if(s[topstart]=='('){}
   else{
   extract();
   insert('*');}
   }
  }
 else if(x>110&&x<138&&y>123&&y<146)
 { if(chr==13){
   if((s[topstart]>=48&&s[topstart]<=57)||s[topstart]==')')
   insert('^');
   else if(s[topstart]=='('){}
   else{
   extract();
   insert('^');}
   }
  }
 else if(x>141&&x<171&&y>123&&y<146) { if(chr==13) extract();}
 else if(x>10&&x<30&&y>154&&y<177) { if(chr==13) insert('1');}
 else if(x>35&&x<55&&y>154&&y<177) { if(chr==13) insert('2');}
 else if(x>60&&x<80&&y>154&&y<177) { if(chr==13) insert('3');}
 else if(x>85&&x<105&&y>154&&y<177) { if(chr==13){
   if((s[topstart]>=48&&s[topstart]<=57)||s[topstart]==')')
   insert('-');
   else{
   extract();
   insert('-');}
   }
  }
 else if(x>110&&x<138&&y>154&&y<177) { if(chr==13) insert('(');}
 else if(x>141&&x<171&&y>154&&y<177) { if(chr==13) exit(0);}
 else if(x>10&&x<30&&y>185&&y<208) { if(chr==13) insert('.');}
 else if(x>35&&x<55&&y>185&&y<208) { if(chr==13) insert('0');}
 else if(x>60&&x<80&&y>185&&y<208) { if(chr==13) solve();}
 else if(x>85&&x<105&&y>185&&y<208)
 { if(chr==53){
   if((s[topstart]>=48&&s[topstart]<=57)||s[topstart]==')')
   insert('+');
   else if(s[topstart]=='('){}
   else{
   extract();
   insert('+');}
   }
  }
 else if(x>110&&x<138&&y>185&&y<208) { if(chr==13) insert(')');}
 else if(x>141&&x<171&&y>185&&y<208) { if(chr==13) exit(0);}
 //
 cleardevice();
 }
}
void layout(){
 gotoxy(3,7); printf("7"); gotoxy(6,7); printf("8"); gotoxy(9,7); printf("9");
 gotoxy(3,9); printf("4"); gotoxy(6,9); printf("5"); gotoxy(9,9); printf("6");
 gotoxy(3,11); printf("1"); gotoxy(6,11); printf("2"); gotoxy(9,11); printf("3");
 gotoxy(3,13); printf("."); gotoxy(6,13); printf("0"); gotoxy(9,13); printf("=");
 gotoxy(12,7); printf("/"); gotoxy(15,7); printf("OFF"); gotoxy(19,7);printf("CLR");
 gotoxy(12,9); printf("*");gotoxy(16,9); printf("^"); gotoxy(19,9); printf("DEL");
 gotoxy(12,11); printf("-"); gotoxy(16,11); printf("(");
 gotoxy(12,13); printf("+"); gotoxy(16,13); printf(")");
 rectangle(7,14,174,215);         //border
 gotoxy(17,2);
 printf("CASIO");
 rectangle(10,30,171,85);         //result window
 //buttons************************
 rectangle(10,92,30,115);         //7
 rectangle(35,92,55,115);         //8
 rectangle(60,92,80,115);         //9
 rectangle(85,92,105,115);        // /
 rectangle(110,92,138,115);       //OFF
 rectangle(141,92,171,115);       //clr
  rectangle(10,123,30,146);       //4
 rectangle(35,123,55,146);        //5
 rectangle(60,123,80,146);        //6
 rectangle(85,123,105,146);       //*
 rectangle(110,123,138,146);      //DEL
 rectangle(141,123,171,146);      //^
  rectangle(10,154,30,177);       //1
 rectangle(35,154,55,177);        //2
 rectangle(60,154,80,177);        //3
 rectangle(85,154,105,177);       //-
 rectangle(110,154,138,177);      //(
 rectangle(141,154,171,177);      //
  rectangle(10,185,30,208);       //.
 rectangle(35,185,55,208);        //0
 rectangle(60,185,80,208);        //=
 rectangle(85,185,105,208);       //+
 rectangle(110,185,138,208);      //)
 rectangle(141,185,171,208);      //
 traverse();
}
 void insert(char ch){
  if(topstart==18)
  printf("too long value to evaluate");
  else{
  s[++topstart]=ch;}
 }
 void extract(){
 if(topstart==-1)
 printf("0");
 else{
  s[topstart--]='\0';
  }
 }
 void traverse(){
 int i,x=3,y=5;
 for(i=0;i<=topstart;i++){
 gotoxy(x,y);
 printf("%c",s[i]);
 x++;
 }
 }
 void solve()
 {
     int u,q=0;
 for(u=0;u<strlen(s);u++){
    push(&s[u]);
 }
  intopost();
    while(q<strlen(postfix_exp)-1){
    ++q;
    for(q=q;postfix_exp[q]!=')';q++){}
    char_to_double(q);
  }
  eval();
  printf("= %.2lf",stak[top_post]);
 }
 void clr(){
 int i;
  for(i=0;i<=19;i++)
 { s[i]='\0';
  topstart=-1;}
 }
 //
 void push(char *ch){
  s[++top]=*ch;
 }
  void push1(char *ch){
  stack[++topa]=*ch;
  }
  void pop1(){
  if(topa==-1)
  printf("0");
  else{ stack[topa--]='\0';}
  }
  void pushp(char *ch){
  postfix_exp[++topp]=*ch;
  }

  void popp(){
 if(topp==-1)
 printf("0");
 else{ postfix_exp[topp--]='\0';}
 }
  void traversep(){
 for(i=0;i<=topp;i++){
 printf("%c",postfix_exp[i]);
 }}
  int priority(char *ptr){
  if(*ptr=='(') return 0;
  else if(*ptr=='-')  return 1;
  else if(*ptr=='+')return 2;
  else if(*ptr=='*')return 3;
  else if(*ptr=='/') return 4;
  else if(*ptr=='^') return 5;
 }

  void intopost(){
   int j;
   char ch='(',chr=')';
   push1(&ch);
   push(&chr);
   pushp(&ch);

   for(i=0;i<=strlen(s)-1;i++){

    if(s[i]>=48&&s[i]<=57){
	pushp(&s[i]); }

	else if(s[i]=='.'){
	   pushp(&s[i]);
	}

    else if(s[i]=='('){
	push1(&s[i]);
    }
	else if(s[i]==')'){
    push1(&s[i]);
    pushp(&s[i]);
   }

    else if((s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/'||s[i]=='^')&&(stack[topa]=='+'||stack[topa]=='-'||stack[topa]=='*'||stack[topa]=='/'||stack[topa]=='^'||stack[topa]=='(')){
	if(priority (&stack[topa])<=priority (&s[i])){
	pushp(&chr);
	pushp(&ch);
	push1(&s[i]);
	}
    else{
    pushp(&chr);
    while(priority(&stack[topa])>priority(&s[i])){
        pushp(&stack[topa]);
        pop1();
      }
    pushp(&ch);
    push1(&s[i]);
    }
  }
}
    if(stack[topa--]==')'){
    while(stack[topa]!='('){

    if(stack[topa]=='('){
	   break;
	  }
    pushp(&stack[topa]);
    pop1();
    }
    if(topa==0)
        pop1();
   }
   }
//**************************************************************************************************************
void char_to_double(int l){
    double dividend=1.0;
    for(ipost=l-1,p=0.0;postfix_exp[ipost]!='(';ipost--){
    if(postfix_exp[ipost]=='.'){
        ipost--;
        dividend=pow(10.0,p);
    }
    if(postfix_exp[ipost]>=48&&postfix_exp[ipost]<=57){
        a[j]=a[j]+(postfix_exp[ipost]-48)*pow(10.0,p);
        p++;
    }
   }
  a[j]=a[j]/dividend;
  j++;
}
void push_num(double *num){
    stak[++top_post]=*num;
}
void pop_post_stak(){
    stak[top_post--]='\0';
}
double add(double *num1,double *num2){
*num1=*num1+*num2;
return (*num1);
}
double sub(double *num1,double *num2){
*num1=*num1-*num2;
return (*num1);
}
double mul(double *num1,double *num2){
*num1=*num1*(*num2);
return (*num1);
}
double div(double *num1,double *num2){
*num1=*num1/(*num2);
return (*num1);
}
double power(double *num1,double *num2){
*num1=pow(*num1,*num2);
return (*num1);
}
void eval(){
    int j=0;
    double num2,num1,result;
    for(ipost=1;ipost<strlen(postfix_exp);ipost++){
        if(postfix_exp[ipost]==')'){
            push_num(&a[j]);
            j++;
        }

        else if(postfix_exp[ipost]=='+'||postfix_exp[ipost]=='-'||postfix_exp[ipost]=='/'||postfix_exp[ipost]=='*'||postfix_exp[ipost]=='^'){
            num2=stak[top_post];
            pop_post_stak();
            num1=stak[top_post];
            pop_post_stak();
            if(postfix_exp[ipost]=='+'){
                result=add(&num1,&num2);
                push_num(&result);
            }
            else if(postfix_exp[ipost]=='-'){
                result=sub(&num1,&num2);
                push_num(&result);
            }
            else if(postfix_exp[ipost]=='*'){
                result=mul(&num1,&num2);
                push_num(&result);
            }
            else if(postfix_exp[ipost]=='/'){
                result=div(&num1,&num2);
                push_num(&result);
            }
            else if(postfix_exp[ipost]=='^'){
                result=power(&num1,&num2);
                push_num(&result);
            }
        }
    }
}
