#include "serial.cpp"
using namespace std;


string get_gps(Serial &gps_serial){
	string result = "";
	char read_buf [MAX_BUF];
    char *read_index = read_buf;
    int buf_stack = 0;
    bool flag = true;
    bool colon = false;
    bool data_start = true;
    memset(read_buf, '\0', sizeof(MAX_BUF));
    while(data_start){
		int read_byte = gps_serial.sread(read_index, sizeof(char));
		if ( read_byte< 0) {
			printf("Error reading: %s", strerror(errno));
			data_start = false;
		}
		else if(read_byte == 1 && (*read_index) == '$'){
			cout<<"Data start!!"<<endl;
			memset(read_buf, '\0', sizeof(MAX_BUF));
			read_buf[0] = '$';
			read_index = read_buf;
			read_index++;
			buf_stack = 1;
			flag = true;
		}
		else if(flag){
			if(read_byte == 1){
				if(buf_stack<MAX_BUF){
					if((*read_index) == '\n'){
						result = read_buf;
						memset(read_buf, '\0', sizeof(MAX_BUF));
						read_index  = read_buf;
						buf_stack = 0;
						flag = false;
						data_start = false;
					}
					else if((*read_index) == ','){
						if(!colon){
							read_index++;
							buf_stack++;
							colon = true;
						}
					}
					else{
						read_index++;
						buf_stack++;
						colon = false;
					}
				}
				else{
					cout<<"Data Over Flow!!"<<endl;
					memset(read_buf, '\0', sizeof(MAX_BUF));
					read_index = read_buf;
					buf_stack = 0;
					flag = false;
				}	
			}
		}
	}
	return result;
}
