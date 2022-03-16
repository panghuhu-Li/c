#include<windows.h>
int main(){
	int i;
	while(i < 100000){
		SetCursorPos(100,100);
		i += 1;
	}
	return 0;
}
