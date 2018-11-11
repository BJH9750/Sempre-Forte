#include "oategrity_map.hpp"

using namespace std;

using Byte_Arr = vector< vector<uint8_t> >;
using Method_Dict = multimap<string, Byte_Arr>;
using Class_Dict = multimap<string, Method_Dict>;

bool cmp(const string &lhs, const string &rhs)
{
    size_t q, w;
    q = lhs.find(string("."));
    w = rhs.find(string("."));
    string a, b;
    if(q-7 == 0) a = "0";
    else a = lhs.substr(7, q-7);
    if(w-7 == 0) b = "0";
    else b = rhs.substr(7, w-7);
    return stoi(a,nullptr) < stoi(b, nullptr);
}

bool not_match(uint8_t lhs, uint8_t rhs)
{
	if(rcvt.find(lhs) != rcvt.end()){
		return rcvt[lhs] == rhs ? false : true;
	}
	return true;
}

uint32_t* op_table = init_table();
/*
	ifstream ifs;
	ifs.open("classes.dex", ios::binary);
	ifs.unsetf(std::ios::skipws);
	ifs.seekg(0,ios::end);
	uint32_t l = ifs.tellg();
	ifs.seekg(0, ios::beg);
	vector<uint8_t> vec;
	vec.reserve(l);
	vec.insert(vec.begin(), (istream_iterator<uint8_t>(ifs)), (istream_iterator<uint8_t>()));
	unique_ptr<LIEF::DEX::File> dex_parse = LIEF::DEX::Parser::parse(vec);
	LIEF::DEX::File* dex = dex_parse.get();
*/
bool check_valid(vector<uint8_t> &dex_raw, vector<uint8_t> &vdex_raw)
{
	unique_ptr<LIEF::DEX::FILE> dex_parse = LIEF::DEX::Parser::parse(dex_raw);
	unique_ptr<LIEF::DEX::FILE> vdex_parse = LIEF::DEX::Parser::parse(vdex_raw);
	uint64_t dex_size, vdex_size;

	if (dex_size != vdex_size) return false;
	
	LIEF::DEX::Header dex_h = dex
}

int main(int argc, char** argv)
{
	const char *optstr = "v";

	uint32_t param_opt;
	clock_t st, ed;
	bool is_v = false;

	while(-1 != (param_opt = getopt(argc, argv, optstr))){
		switch(param_opt){
			case 'v':
				is_v = true;
				break;
			case '?':
				printf("USAGE : \n");
				printf("-d : using .vdex\n");
				exit(0);
		}
	}
	vector<string> strs;

	string str_dex;
	string str_vdex;

	str_vdex = "base-M.odex";

	FILE* pp;
	bool invalid_flag = false;
	char buffer[32];
	
	system("unzip -o base.apk *.dex > /dev/null");
	pp = popen("ls | grep classes", "r");
	while((EOF != fscanf(pp, "%s", buffer))){
		strs.push_back(string(buffer));
	}

	pclose(pp);
	sort(strs.begin(), strs.end(), cmp);
	uint32_t dex_cnt = strs.size();
	st = clock();

	unique_ptr<LIEF::OAT::Binary> vdex_parse = LIEF::OAT::Parser::parse(str_vdex);
	/*ed = clock();
	cout<< "vdex iter time : " << (float)(ed-st)/CLOCKS_PER_SEC << endl;
	st = clock();
*/
	LIEF::DEX::it_dex_files vdexes = vdex_parse->dex_files();
	
	vector<uint8_t> raw_dex;
	vector<uint8_t> raw_vdex;
	uint64_t dex_size;
	uint64_t vdex_size;
/*
	ed = clock();
	cout<< "vdex parse time : " << (float)(ed-st)/CLOCKS_PER_SEC << endl;
	st = clock();
*/
	for(int i=0; i<dex_cnt; ++i){
		str_dex = strs[i];

		/*FILE* fp = fopen(str_dex.c_str(), "rb");
		fseek(fp,0,SEEK_END);
		dex_size = ftell(fp);
		fclose(fp);
		*/
		unique_ptr<LIEF::DEX::File> dex_parse = LIEF::DEX::Parser::parse(str_dex);
		LIEF::DEX::File* dex = dex_parse.get();
		LIEF::DEX::File* vdex = &(*vdexes);
		LIEF::DEX::Header dex_h = dex->header();
		LIEF::DEX::Header vdex_h = vdex->header();
/*
		ed = clock();
		cout<< "dex and header time : " << (float)(ed-st)/CLOCKS_PER_SEC << endl;
		st = clock();
*/
		raw_dex = dex->raw(false);
		for(int p=0; p<30;p++) raw_dex.pop_back();
		dex_size = raw_dex.size();
		raw_vdex = vdex->raw(false);
		vdex_size = raw_vdex.size();
/*
		ed = clock();
		cout<< "calculate size time : " << (float)(ed-st)/CLOCKS_PER_SEC << endl;
		st = clock();
*/
		if(dex_size != vdex_size){
			ed = clock();
			cout<< "time : " << (float)(ed-st)/CLOCKS_PER_SEC << endl;
			
			if(is_v) cout << i << " dex size is different " << dex_size << " " << vdex_size << endl;
			system("rm *.dex > /dev/null");
			exit(0);
		}


		if(dex_h.classes().second != vdex_h.classes().second){
			ed = clock();
			cout<< "time : " << (float)(ed-st)/CLOCKS_PER_SEC << endl;
			if(is_v) printf("the number of classes is different\n");
			system("rm *.dex > /dev/null");
			exit(0);
		}
		
		if(dex_h.methods().second != vdex_h.methods().second){
			ed = clock();
			cout<< "time : " << (float)(ed-st)/CLOCKS_PER_SEC << endl;
			system("rm *.dex > /dev/null");
			if(is_v) printf("the number of methods is different\n");
			exit(0);
		}
		
		LIEF::DEX::it_methods dex_methods = dex->methods();
		LIEF::DEX::it_methods vdex_methods = vdex->methods();
		/*
		ed = clock();
		cout<< "parse method iter time : " << (float)(ed-st)/CLOCKS_PER_SEC << endl;
		st = clock();
		*/
		for(auto dex_method : dex_methods){
			LIEF::DEX::Method vdex_method = *vdex_methods;

			LIEF::DEX::Method::bytecode_t dex_code = dex_method.bytecode();
			LIEF::DEX::Method::bytecode_t vdex_code = vdex_method.bytecode();
			
			uint32_t dex_bytesize = dex_code.size();
			uint32_t vdex_bytesize = vdex_code.size();
			uint32_t idx = 0;
			
			bool return_flag = false;
			bool cvt_flag = false;

			while(idx < dex_bytesize){
				uint32_t op_size = op_table[dex_code[idx]];

				vector<uint8_t> dex_op;
				vector<uint8_t> vdex_op;

				dex_op.assign(dex_code.begin()+idx, dex_code.begin()+idx+op_size);
				vdex_op.assign(vdex_code.begin()+idx, vdex_code.begin()+idx+op_size);

				if(dex_op[0] == 0x0E || dex_op[0] == 0x0F || dex_op[0] == 0x10 || dex_op[0] == 0x11 ){
					return_flag = true;
				}

				if(cvt.find(dex_op[0]) != cvt.end()){
					cvt_flag = true;
                    dex_op[0] = cvt[dex_op[0]];
                }
				if(dex_op[0] != 0x1f){
					for(int j=0; j<op_size; j++){
						if(cvt_flag && j >=2) break;
						if(dex_op[j] != vdex_op[j]){
							if(not_match(dex_op[j], vdex_op[j])){
								ed = clock();
								cout<< "time : " << (float)(ed-st)/CLOCKS_PER_SEC << endl;
								if(is_v) printf("Method is not matched\n");
								system("rm *.dex > /dev/null");
								exit(0);
							}
						}
					}
				}
				if(return_flag) break;
				idx += op_size;
			}
			vdex_methods++;
		}
		vdexes++;
	}

	if(is_v) printf("Valid\n");
	ed = clock();
	cout<< "time : " << (float)(ed-st)/CLOCKS_PER_SEC << endl;
	system("rm *.dex > /dev/null");
	return 0;
}
