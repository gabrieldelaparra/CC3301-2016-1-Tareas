#include <stdio.h>

void printBinaryUChar(unsigned char c){
	int i = 0;
	printf("%i:",c);
	for(i = 0; i < 8; i++){
		if(i % 4 == 0) printf(" ");
		printf("%i",(c & (1 << (7 - i))) >> (7 - i));
	}
	printf("\n");
}

void printBinaryUInt(unsigned int b){
	int i = 0;
	printf("%i:",b);
	for(i = 0; i < 32; i++){
		if(i%4==0) printf(" ");
		printf("%i",(b & (1 << (31 - i))) >> (31 - i));
	}
	printf("\n");
}

void printBinaryInt(int b){
	int i = 0;
	printf("%i:",b);
	for(i = 0; i < 32; i++){
		if(i%4==0) printf(" ");
		printf("%i",(b & (1 << (31 - i))) >> (31 - i));
	}
	printf("\n");
}

int minus(int x){
	return 1 + ~x;
}

int isNeg(int x){
	return ((1 << 31) & x) >> 31;
}

int abs(int x){
	if(isNeg(x)) 
		return minus(x);
	else 
		return x;
}

unsigned char rotateLeft(unsigned char c){
	unsigned char mask = 1 << 7;
	unsigned char msb = c & mask;
	printf("LFT: ");
	unsigned char r = (c << 1) + msb;
	printBinaryUChar(r);
	return r;
}

unsigned char rotateRight(unsigned char c){
	unsigned char mask = 1;
	unsigned char lsb = c & mask;
	printf("RGT: ");
	unsigned char r = (c >> 1) + (lsb << 7);
	printBinaryUChar(r);
	return r;
}

unsigned char rotate(unsigned char c, int bits){
	printf("SRC: ");
	printBinaryUChar(c);
	unsigned char r = 0;
	if(bits >= 0)
		r = rotateRight(c);
	else
		r = rotateLeft(c);
	printf("\n");
	return r;
}

unsigned int fullMask(int i){
	unsigned int mask = i == 0 ? -1 : (1 << 32 - i) - 1; 
	printf("Mask: ");
	printBinaryUInt(mask);
	return mask;
}

unsigned int customMask(int i, int k){
	unsigned int mask = k == 32 ? -1 : ((1 << k) - 1) << 32 - i - k;
	printf("Mask: ");
	printBinaryUInt(mask);
	return mask;
}

unsigned int extractMask(unsigned int x, int i, int k){
	printf("SRC: ");
	printBinaryUInt(x);
	//unsigned int r = (x&customMask(i,k))>>32-(i+k);
	unsigned int r = (x & fullMask(i)) >> 32 - (i + k);
	printf("EXT: ");
	printBinaryUInt(r);
	printf("\n");
	return r;	
}

int bits1(int n){
	printf("SRC: ");
	printBinaryInt(n);
	int i = 0;
	int count = 0;
	for (i = 0;i < 31;i++){ //Hasta 31, para no considerar el signo;
		int mask = (1<<i);
		int iBit = n & mask;
		if(iBit > 0)
			count++;
	}
	printf("CNT: %i \n", count);
	return count;
}

int intSize(){
	int i = ~0;
	int count = 0;
	do{
		count++;
		i = i << 1;
		printf("i: %i \n", i);
	}while(i != 0);
	printf("CNT: %i \n", count);
	return count;
}



int main()
{
	intSize();
	
	// bits1(0x048b6048);
	// bits1(0xFFFFFFFF);
	// bits1(0x7FFFFFFF);
	// bits1(0x1);
	
	// extractMask(0xFFFFFFFF,0,16);
	// extractMask(0xFFFFFFFF,1,30);
	// extractMask(0xFFFFFFFF,8,16);
	// extractMask(0xFFFFFFFF,0,0);
	// extractMask(0xFFFFFFFF,0,1);	
	// extractMask(0xFFFFFFFF,0,32);	
	// extractMask(0xFFFFFFFF,31,1);
	// extractMask(0xFFFFFFFF,32,0);
	// extractMask(0x048b6048,0,4);
	// extractMask(0x048b6048,8,12);
	// printf("\n");
	
	// rotate(1,1);	
	// rotate(2,1);	
	// rotate(3,1);	
	// rotate(11,1);	
	// printf("\n");
	
	// rotate(1,-1);	
	// rotate(2,-1);	
	// rotate(3,-1);	
	// rotate(11,-1);	
	// printf("\n");
	
	// printf("%i \n",abs(-1));
	// printf("%i \n",abs(-20));
	// printf("%i \n",abs(20));
	// printf("%i \n",abs(0));
	// printf("%i \n",abs(-0));
}