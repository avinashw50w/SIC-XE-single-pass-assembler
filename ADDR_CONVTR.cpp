   //*+++++++++++++++++++++++++++++++++++++++++*//
  //           ~~~~~ @VIN@SH ~~~~~             //
 //          ~~~~ IIEST SHIBPUR ~~~~          //
//*+++++++++++++++++++++++++++++++++++++++++*//

typedef string hexa;

// extends the hexadecimal number by adding zeroes at the front
hexa extendTo(int len,hexa a)
{
    hexa temp = "";
    for(int i=0;i<len-a.size();++i)
        temp += '0';
    return temp + a;
}

// converts a decimal number to its equivalent hexadecimal form
string toHex(int a) {
    string lookup = "0123456789ABCDEF";
    string res = "";
    while(a)
    {
        res = lookup[a%16] + res;
        a /= 16;
    }
    return res;
}

int toDecimal_digit(char a) {
    if(a=='0') return 0;
    if(a=='1') return 1;
    if(a=='2') return 2;
    if(a=='3') return 3;
    if(a=='4') return 4;
    if(a=='5') return 5;
    if(a=='6') return 6;
    if(a=='7') return 7;
    if(a=='8') return 8;
    if(a=='9') return 9;
    if(a=='A') return 10;
    if(a=='B') return 11;
    if(a=='C') return 12;
    if(a=='D') return 13;
    if(a=='E') return 14;
    if(a=='F') return 15;
}


char toHex_digit(int a) {
    if(a==0) return '0';
    if(a==1) return '1';
    if(a==2) return '2';
    if(a==3) return '3';
    if(a==4) return '4';
    if(a==5) return '5';
    if(a==6) return '6';
    if(a==7) return '7';
    if(a==8) return '8';
    if(a==9) return '9';
    if(a==10) return 'A';
    if(a==11) return 'B';
    if(a==12) return 'C';
    if(a==13) return 'D';
    if(a==14) return 'E';
    if(a==15) return 'F';
}


int toDec(string s) {
    int mul = 1, res = 0;
    for(int n=s.size()-1; n>=0; --n) {
        res += toDecimal_digit(s[n])*mul;
        mul *= 16;
    }
    return res;
}

string twos_complement(string s){
    string res = "";
    int a = atoi(s.c_str());
    while(a){
        res = toHex(15 - a%10) + res;
        a /= 10;
    }
    int l = 3-s.size();
    while(l>0) res = "F" + res, l--;
    res = toHex(toDec(res) + 1);
    return res;
}
