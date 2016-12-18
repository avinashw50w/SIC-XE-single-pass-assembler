   //*+++++++++++++++++++++++++++++++++++++++++*//
  //           ~~~~~ @VIN@SH ~~~~~             //
 //          ~~~~ IIEST SHIBPUR ~~~~          //
//*+++++++++++++++++++++++++++++++++++++++++*//

#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <utility>
#include <ctype.h>
#include <string>
#include <cstdio>
#include <vector>
#include <time.h>
#include <map>

using namespace std;

#define oo  0x3f3f3f3f
#define ooo (1LL<<60)
#define MOD 1000000007
#define MP  make_pair
#define MT  make_tuple
#define PB  push_back
#define WR(o)  cout<<(o)
#define LL  long long int
#define SZ(o) ((int)(o).size())
#define ULL long long unsigned int
#define FORE(i,o) for(auto &i:(o))
#define ALL(o) (o).begin(),(o).end()
#define FILL(o,n) memset((o),(n),sizeof (o))
#define REP(i,a,b) for(int i=(int)(a);i<(int)(b);++i)
#define PER(i,b,a) for(int i=(int)(b);i>=(int)(a);i--)
#define CASET  int __T,case_n=1; cin>>__T; while(__T--)
#define MIII unordered_map< int, unordered_map<int,int> >
#define UNIQUE(o) (sort(ALL(o)), ((o).erase(unique(ALL(o)), (o).end())))
#define RUNTIME cout<<"\nRunning time : "<<(double)clock()/CLOCKS_PER_SEC<<"\n"
#define BOOST  ios_base::sync_with_stdio(0);cin.tie(0)
#define FF first
#define SS second
#define Gc getchar
#define Pc putchar
#ifdef DEBUG
     #define debug(args...) {dbg,args; cerr<<endl;}
#else
    #define debug(args...)
#endif
struct debugger{
    template<typename T> debugger& operator , (const T& v) { cerr<<v<<" "; return *this; }
} dbg;

const double EPS = 1e-7;
typedef vector<int> VI;
typedef pair<int,int> PII;
typedef vector<PII> VII;
typedef map<int,int> MII;

template<typename T> struct Comp{ bool operator()(const T &A,const T &B){ return A > B; } };  // LAMBDA: [](T a,T b){return a>b;}
inline void input(LL X){LL N=0;int S=1;register int c=Gc();if(c=='-')S=-1,c=Gc();while(c>='0'&&c<='9')N=(N<<3)+(N<<1)+(c-48),c = Gc();X=N*S;}
inline void output(LL N){if(abs(N)!=N)Pc('-');char buf[20];int i=0;do{buf[i++]=N%10+48;N/=10;}while(N);i--;while(i>=0)Pc(buf[i--]);Pc('\n');}

/*==========================================PROGRAM STARTS FROM HERE=========================================================================*/

#include "ADDR_CONVTR.cpp"
#include "TABLES.cpp"

#define SIC_XE Activate_SIC_XE_Formats;

string generateCode(string , string);

void incrmtTheCntr(string , string);

inline bool isSpace(char s)
{
    if(s == ' ')  return true;
    if(s == '\t') return true;
    return false;
}
/*=========================PARSE EACH LINE============================*/
inline void parse(string a,string token[],int &count)
{
    int i;
    for(i=0;i<4;++i) token[i] = "";
    count = 0;
    i = 0;
    while(isSpace(a[i]) and i<a.size()) { ++i; continue; }
    if(i == a.size() or a[i] == '.')   return;
    for( ; i<a.size(); )
    {
        while(isSpace(a[i]) and i<a.size()) { ++i; continue; }
        if(i == a.size()) break;
        for( ; !isSpace(a[i]) && i<a.size(); ++i) token[count] += a[i];
        ++count;
    }
}
/*==========================================================================*/

int line;
hexa pc , locctr , start , prog_start , length = "0" , obj_code , base ;
bool error_flag , imm , ind , indx;
string file_name;

ifstream Inp;
ofstream Interm , List , Obj , Modify;

/*================== MAIN PROGRAM FOR ONE PASS ASSEMBLER ===================*/

void run_the_SIC_XE_Assembler() {

	create_the_optab();

    BOOST;

	string s, token[4];
	Inp.open("INPUT1.txt" , ios::in);
	List.open("LIST.txt" , ios::out);
	Modify.open("MODIFY.txt" , ios::out);
	Interm.open("INTERMED.txt");
	line = 0;
	int count = 0;

	getline(Inp, s);
	parse(s, token, count);

	List <<"Line\tAddress\t   Sorce Statement\t\tObject code"<<endl;
	List <<"-----------------------------------------------------------------"<<endl;

	while(count == 0) {
		cout<< s << endl;
		List << line++ << "  "<< s << endl;
		getline(Inp, s);
		parse(s, token, count);
	}
	if(token[0] == "START") {
		cout << "NO FILENAME...!!" << endl;
		cout << "STARTING EXECUTION..." << endl;
		file_name = "NULL";
		locctr = token[1];
		pc = start = locctr;
		base = locctr;
		cout << "STARTING ADDRESS : "<< start << endl;
		List << line++ 
             <<"\t\t"<<token[0]
             <<"\t"<<token[1]
             <<endl;
	}
	else if(token[1] == "START") {
		file_name = token[0];
		cout << "STARTING EXECUTION OF "
			 << file_name <<"...." 
			 << endl;
		locctr = token[2];
		pc = start = locctr;
		base = locctr;
		cout << "STARTING ADDRESS : "
			 << start << endl;
		List << line++ 
             <<"\t\t"<<token[0]
             <<"\t"<<token[1]
             <<"\t"<<token[2]
             <<endl;
	}
	else {
		cerr << "PROGRAM HAS NO START !!" << endl;
		return;
	}

	BLOCK.start = start;
	BLOCK.length = "0";
	BLOCK.object = "";

	while(token[0] != "END") {
		getline(Inp, s);
		parse(s, token, count);
		if(count == 0) {
			cout << s <<endl;
			List << line++ << "  "<< s << endl;
			continue;
		}
		locctr = pc;
		/*
		if(token[0] == "BASE") {
			base = SYMTAB[token[1]].addr;
			List << line++ <<"\t"<<extendTo(4,locctr) 
                 <<"\t\t"<<token[0]<<"\t"<<token[1]<<endl;
			continue;
			}
		*/
		if(DIRECT[token[1]].exist == 'y') {
			if(SYMTAB[token[0]].exist == 'y'){
				cerr << "Duplicate Symbol Detected : "
					 << token[0] <<endl;
				return;
			}
			else {
				SYMTAB[token[0]].exist = 'y';
				SYMTAB[token[0]].addr = locctr;

				incrmtTheCntr(token[1],token[2]);
				obj_code = generateCode(token[1],token[2]);
				if(toDec(length)*2 + obj_code.size() > 60) {
					Interm << "T^"
                           << extendTo(6,BLOCK.start)
                           << "^"<<extendTo(2,length)
                           << BLOCK.object<< endl;
					
                    BLOCK.object = "";
					BLOCK.start  = locctr;
					length       = "0";
				}
				length = toHex(toDec(length) + obj_code.size()/2);

				List << line++ 
                     << "\t"<<extendTo(4,locctr) 
                     << "\t"<<token[0]<<"\t"
                     << token[1]<<"\t"
                     << token[2]<<"\t\t"
                     << obj_code<<endl;

				if(token[1] == "RESW" or token[1] == "RESB") continue;
				BLOCK.object = BLOCK.object + "^" + obj_code;
			}
		}
		else break;  // count != 0 and token[1] is not a directive;
	}

	Interm <<"T^" << extendTo(6,BLOCK.start)
           <<"^"<< extendTo(2,length) 
           << BLOCK.object << endl;
	length = "0";

	line += (5 - line%5) - 5;
	prog_start = pc;
	BLOCK.start = pc;
	BLOCK.length = "0";
	BLOCK.object = "";

	while(token[0] != "END") {
		line += 5;
		if(count == 0) {
			cout << s <<endl;
			List << line << "  " << s << endl;
			getline(Inp, s);
			parse(s, token, count);
			continue;
		}

		locctr = pc;

	#if 0
		if(token[0] == "BASE") {
			base = SYMTAB[token[1]].addr;
			List << line++ <<"\t"<<extendTo(4,locctr) 
                 <<"\t\t"<<token[0]<<"\t"<<token[1]<<endl;
			getline(Inp, s);
			parse(s, token, count);
			continue;
			}
		if(token[0] == "NOBASE"){
			base = "FFFF";
			List << line++ <<"\t"<<extendTo(4,locctr) 
				 <<"\t\t"<<token[0]<<endl;
			getline(Inp, s);
			parse(s, token, count);
			continue;
		}
	#endif

		int fmt4 = 0;
		if(token[0][0] == '+') { 
			token[0] = token[0].substr(1); fmt4 = 1; 
		}

		// if first token is an opcode //
		if(OPTAB[token[0]].exist == 'y') {
			if(fmt4) token[0] = "+" + token[0];
			incrmtTheCntr(token[0],token[1]);
			obj_code = generateCode(token[0],token[1]);

			if(toDec(length)*2 + obj_code.size() > 60) {
				Interm << "T^" << extendTo(6,BLOCK.start)
                       << "^"  << extendTo(2,length)
                       << BLOCK.object<< endl;
				BLOCK.object = "";
				BLOCK.start  = locctr;
				length       = "0";
			}
			length = toHex(toDec(length) + obj_code.size()/2);
			BLOCK.object = BLOCK.object + "^" + obj_code;
			List << line 
                 << "\t" << extendTo(4,locctr) 
                 << "\t\t" << token[0] <<"\t"
                 << token[1] << "\t\t"
                 << obj_code << endl;
		}

		// if first token is a symbol //
		else {

			if(SYMTAB[token[0]].exist == 'n') {
				SYMTAB[token[0]].exist = 'y';
				SYMTAB[token[0]].addr = locctr;

				incrmtTheCntr(token[1],token[2]);
				obj_code = generateCode(token[1],token[2]);

				if(toDec(length)*2 + obj_code.size() > 60) {
					Interm <<"T^"<<extendTo(6,BLOCK.start)
                           <<"^"<<extendTo(2,length)
                           <<BLOCK.object<< endl;
					BLOCK.object = "";
					BLOCK.start  = locctr;
					length       = "0";
				}
				length = toHex(toDec(length) + obj_code.size()/2);
				if(token[1] != "RESW" and token[1] != "RESB")
					BLOCK.object = BLOCK.object + "^" + obj_code;

				List << line 
                     <<"\t"<<extendTo(4,locctr) 
                     <<"\t"<<token[0]
                     <<"\t"<<token[1]
                     <<"\t"<<token[2]
                     <<"\t\t"<< obj_code << endl;
			}

			else if(SYMTAB[token[0]].exist == 'y' and 
                   (SYMTAB[token[0]].addr.compare("*") == 0 or 
                    SYMTAB[token[0]].addr.compare("**") == 0) ) {
					
					bool modify = 0;
					if(SYMTAB[token[0]].addr.compare("**") == 0) modify = 1;

					SYMTAB[token[0]].addr = locctr;

					Interm <<"T^"<< extendTo(6,BLOCK.start)
                           <<"^"<< extendTo(2,length) 
                           << BLOCK.object << endl;

					length = "0";
					incrmtTheCntr(token[1],token[2]);
					obj_code = generateCode(token[1],token[2]);
					length = toHex(toDec(length) + obj_code.size()/2);
					BLOCK.object = "";
					BLOCK.start = locctr;
					if(token[1] != "RESW" and token[1] != "RESB")
						BLOCK.object = "^" + obj_code;

					List << line 
                         <<"\t"<<extendTo(4,locctr) 
                         <<"\t"<<token[0]
                         <<"\t"<<token[1]
                         <<"\t"<<token[2]
                         <<"\t\t"<<obj_code<<endl;

					for(int i=0; i<SYMTAB[token[0]].ref.size(); ++i){
						Interm << "T^" 
                               << extendTo(6,SYMTAB[token[0]].ref[i]) 
                               << "^02^"
                               << extendTo(4,SYMTAB[token[0]].addr) << endl;
						if(modify)
							Modify << "M^" 
                                   << extendTo(6,SYMTAB[token[0]].ref[i]) 
                                   << "^05" << endl;
					}
			}

			else {
				cerr <<"Duplicate Symbol Detected : "<< token[0] << endl;
				return;
			}

		}

		getline(Inp, s);
		parse(s, token, count);
	}

    //  check symbol table for undefined symbols  //
	for(map<string,symbol_info>::iterator it=SYMTAB.begin(); 
		it!=SYMTAB.end(); ++it) {
		if(it->SS.addr == "*") {
			cerr <<"\nSYMBOL ADDRESS NOT DEFINED : " 
                 << it->FF << "  !!!" <<endl;
			error_flag = 1;
		}
	}
	if(error_flag) return;

	Interm <<"T^"<< extendTo(6,BLOCK.start)
           <<"^"<< extendTo(2,length) 
           << BLOCK.object << endl;
	length = "0";

	hexa program_len = toHex(toDec(pc) - toDec(start));

	Obj.open("OBJECT.txt");
	Obj <<"H^" << file_name <<"  ^"
        << extendTo(6,start) <<"^"
        << extendTo(6,program_len) << endl;

	ifstream fin;
	fin.open("INTERMED.txt", ios::in);
	while(getline(fin,s)) {
		Obj << s << endl;
	}
	ifstream fin1;
	fin1.open("MODIFY.txt" , ios::in);
	while(getline(fin1,s)) {
		Obj << s << endl;
	}

	if(token[0] == "END"){
		prog_start = (token[1] == "") ? 
                     prog_start : extendTo(6,SYMTAB[token[1]].addr);
		Obj << "E^" << prog_start << endl;

		List << line <<"\t\t\t"
			 <<token[0]<<"\t"
			 <<token[1]
			 <<endl;
	}

	cout << "\n\nOBJECT CODE GENERATED SUCCESSFULLY !!" << endl;
}

/*===================== INCREMENTS THE LOCATION COUNTER=====================*/

void incrmtTheCntr(string opc , string opr){
	if(opc[0] == '+'){
		cout <<"Format 4 : "<< opc <<endl;
		pc = toHex(toDec(pc) + 4);
		return;
	}

	if(OPTAB[opc].exist == 'y'){
		pc = toHex(toDec(pc) + OPTAB[opc].format);
		return;
	}

	if(opc == "WORD")       pc = toHex(toDec(pc) + 3);
	else if(opc == "RESW")  pc = toHex(toDec(pc) + 3*(atoi(opr.c_str())));
	else if(opc == "RESB")  pc = toHex(toDec(pc) + atoi(opr.c_str()));
	else if(opc == "BYTE") {
		int len = opr.size()-3;
		if(opr[0] == 'X') len /= 2;
		pc = toHex(toDec(pc) + len);
	}
}

/*===========================================================================*/

/*======================== GENERATES OBJECT CODE ============================*/

string generateCode(string opc, string opr){
	hexa code1 , code2 , code3;
	int format;
	bool overFlow = 0;

	if(opc == "RESW" or opc == "RESB") return "";

	if(opc == "BYTE"){
		code1 = "";
		int l = opr.size()-3;
		if(opr[0] == 'X'){
			for(int i=2; i<opr.size()-1; ++i)
				code1 += opr[i];
		}
		else {
			for(int i=2; i<opr.size()-1; ++i)
				code1 += toHex((int)opr[i]);
		}
		return code1;
	}

	if(opc == "WORD"){
		code1 = toHex(atoi(opr.c_str()));
		return extendTo(6,code1);
	}

	if(opc == "RSUB"){
		code1 = "4F0000";
		return code1;
	}

	if(opc == "+RSUB"){
		code1 = "4F000000";
		return code1;
	}

	if(opc[0] == '+'){
		format = 4;
		opc = opc.substr(1);
	}

	else
		format = OPTAB[opc].format;

	/*================== FORMAT 1 =======================*/

	if(format == 1){
		code1 = OPTAB[opc].opcode;
		return code1;
	}
	/*================================================================*/

	/*=================== FORMAT 2 ===================================*/

	if(format == 2){
		code1 = OPTAB[opc].opcode;
		if(opr.size() == 3) {
			code2 = toHex_digit(reg_num(opr[0]));
			if(isdigit(opr[2]))
				code2 += toHex_digit(opr[2]-48);
			else
				code2 += toHex_digit(reg_num(opr[2]));
		}
		else {
			if(isdigit(opr[0]))
				code2 = toHex(atoi(opr.c_str())) + "0";
			else
				code2 = toHex(reg_num(opr[0])) + "0";
		}
		return (code1 + extendTo(2,code2));
	}
	/*================================================================*/

	/*======================= FORMAT 3 ===============================*/

	imm = 0 , ind = 0 , indx = 0;

	if(format == 3){
		code1 = OPTAB[opc].opcode;

		#ifdef SIC_XE
		//  immediate addressing  //
		if(opr[0] == '#'){
			imm = true;
			code1 = toHex(toDec(code1) + 1);
			opr = opr.substr(1);
			if(isdigit(opr[0])){
				code2 = toHex(atoi(opr.c_str()));
				return (extendTo(2,code1) + extendTo(4,code2));
			}
		}

		//  indirect addressing  //
		else if(opr[0] == '@'){
			ind = true;
			code1 = toHex(toDec(code1) + 2);
			opr = opr.substr(1);
		}
		else
			code1 = toHex(toDec(code1) + 3);

		#endif

		code2 = "0";
		int sz = opr.size();
		if(opr[sz-2] == ','){
			indx = true;
			opr = opr.substr(0,sz-2);
			code2 = toHex(toDec(code2) + (1<<3));
		}

		if(SYMTAB[opr].exist == 'n'){
			SYMTAB[opr].exist = 'y';
			SYMTAB[opr].addr = "*";
			SYMTAB[opr].ref.PB(toHex(toDec(locctr) + 1));

			cout<<opr <<" ref : "<<toHex(toDec(locctr) + 1) << endl;
			if(imm)  opr = "#" + opr;
			if(ind)  opr = "@" + opr;
			if(indx) opr += ",X";

			return code1 + extendTo(4,code2);
		}

		else if(SYMTAB[opr].addr.compare("*") == 0){
			SYMTAB[opr].ref.PB(toHex(toDec(locctr) + 1));

			cout<<opr <<" ref : "<<toHex(toDec(locctr) + 1) << endl;
			if(imm)  opr = "#" + opr;
			if(ind)  opr = "@" + opr;
			if(indx) opr += ",X";

			return extendTo(2,code1) + extendTo(4,code2);
		}

		else {
			string opr_addr = SYMTAB[opr].addr;

			//  PC relative  //
			int disp = toDec(opr_addr) - toDec(pc);
      		if(-2048<=disp and disp<2048){
				if(disp<0) {
					disp = -disp;
					code3 = twos_complement(toHex(disp));
				}
				else code3 = toHex(disp);
				code2 = toHex(toDec(code2) + 2);
				return extendTo(2,code1) + code2 +  extendTo(3,code3);
			}

			//  Base relative  //
			disp = toDec(opr_addr) - toDec(base);
			if(0<=disp and disp<4096){
				code2 = toHex(toDec(code2) + 4);
				code3 = toHex(disp);
				return extendTo(2,code1) + code2 + extendTo(3,code3);
			}

			else{
				overFlow = 1;
				cerr << "MEMORY OVERFLOW...!!!" << endl;
			}
		}
	}
	/*=======================================================================*/

	/*============================= FORMAT 4 ================================*/

	#ifdef SIC_XE
	if(format == 4){
		code1 = OPTAB[opc].opcode;
		if(opr[0] == '#'){
			imm = true;
			code1 = toHex(toDec(code1) + 1);
			opr = opr.substr(1);
			if(isdigit(opr[0])){
				code2 = toHex(atoi(opr.c_str()));
				opc = "+" + opc;
				return extendTo(2,code1) + extendTo(6,code2);
			}
		}

		else if(opr[0] == '@'){
			ind = true;
			code1 = toHex(toDec(code1) + 2);
			opr = opr.substr(1);
		}

		else
			code1 = toHex(toDec(code1) + 3);

		code2 = "1";
		int sz = opr.size();
		if(opr[sz-2] == ','){
			indx = true;
			code2 = toHex(toDec(code2) + (1<<3));
			opr = opr.substr(0,sz-2);
		}


		if(SYMTAB[opr].exist == 'n'){
			SYMTAB[opr].exist = 'y';
			SYMTAB[opr].addr = "**";
			SYMTAB[opr].ref.PB(toHex(toDec(locctr) + 1));

			cout<<opr <<" ref : "<<toHex(toDec(locctr) + 1) << endl;

			if(imm)  opr = "#" + opr;
			if(ind)  opr = "@" + opr;
			if(indx) opr += ",X";
			opc = "+" + opc;

			return extendTo(2,code1) + code2 + extendTo(5,"0");
		}

		else if(SYMTAB[opr].addr.compare("**") == 0){
			SYMTAB[opr].ref.PB(toHex(toDec(locctr) + 1));

			cout<<opr <<" ref : "<<toHex(toDec(locctr) + 1) << endl;

			if(imm)  opr = "#" + opr;
			if(ind)  opr = "@" + opr;
			if(indx) opr += ",X";
			opc = "+" + opc;

			return extendTo(2,code1) + code2 + extendTo(5,"0");
		}

		else {
			string opr_addr = SYMTAB[opr].addr;
			code3 = opr_addr;

			if(imm)  opr = "#" + opr;
			if(ind)  opr = "@" + opr;
			if(indx) opr += ",X";
			opc = "+" + opc;

			string mem_addr = toHex(toDec(locctr) + 1 - toDec(start));
            /** starting location of the addr field 
             * and the lenght of the addr field
             */          
			Interm << "M^" << extendTo(6,mem_addr) << "^05" << endl;  
			return extendTo(2,code1) + code2 + extendTo(5,code3);
		}
	}
	#endif
}
/*===========================================================================*/

/*=================================  END OF PROGRAM  ========================*/
         
/*
	               _            .                                 .x+=:.
	              u            @88>                              z`    ^%    .uef^"
	             88Nu.   u.    %8P      u.    u.                    .   <k :d88E
	      u     '88888.o888c    .     x@88k u@88c.       u        .@8Ned8" `888E
	   us888u.   ^8888  8888  .@88u  ^"8888""8888"    us888u.   .@^%8888"   888E .z8k
	.@88 "8888"   8888  8888 ''888E`   8888  888R  .@88 "8888" x88:  `)8b.  888E~?888L
	9888  9888    8888  8888   888E    8888  888R  9888  9888  8888N=*8888  888E  888E
	9888  9888    8888  8888   888E    8888  888R  9888  9888   %8"    R88  888E  888E
	9888  9888   .8888b.888P   888E    8888  888R  9888  9888    @8Wou 9%   888E  888E
	9888  9888    ^Y8888*""    888&   "*88*" 8888" 9888  9888  .888888P`    888E  888E
	"888*""888"     `Y"        R888"    ""   'Y"   "888*""888" `   ^"F     m888N= 888>
	 ^Y"   ^Y'                  ""                  ^Y"   ^Y'               `Y"   888
	                                                                             J88"
	                                                                             @%
	                                                                           :"
*/
