#include <stdio.h>

int F(int X,int Y,int Z){
	return (X&Y)|((~X)&Z);
}

int G(int X,int Y,int Z){
	return (X&Z)|(Y&(~Z));
}

int H(int X,int Y,int Z){
	return X^Y^Z;
}

int I(int X,int Y,int Z){
	return Y^(X|(~Z));
}

void FF(int a,int b,int c,int d,int mi,int s,int tj)
{
	int temp = 0;
	temp = F(b,c,d) + a + mi+ tj;
	temp = (temp<<s)|(temp>>(32-s));
	a = b + temp; 
}



void GG(int a,int b,int c,int d,int mi,int s,int tj){
	int temp = G(b,c,d) + a + mi + tj;
	temp = (temp<<s)|(temp>>(32-s));
	a = b + temp; 
}

void HH(int a,int b,int c,int d,int mi,int s,int tj){
	int temp = H(b,c,d) + a + mi + tj;
	temp = (temp<<s)|(temp>>(32-s));
	a = b + temp; 
}

void II(int a,int b,int c,int d,int mi,int s,int tj){
	int temp = I(b,c,d) + a + mi + tj;
	temp = (temp<<s)|(temp>>(32-s));
	a = b + temp; 
}



void main()
{
	unsigned int A = 0x67452301;
	unsigned int B = 0xEFCDAB89;
	unsigned int C = 0x98BADCFE;
	unsigned int D = 0x10325476;
	unsigned int i,j = 0;
	unsigned int out[4]={0};

	unsigned int T[64] = {
		0xD76AA478,0xE8C7B756,0x242070DB,0xC1BDCEEE,0xF57C0FAF,0x4787C62A,0xA8304613,0xFD469501,
		0x698098D8,0x8B44F7AF,0xFFFF5BB1,0x895CD7BE,0x6B901122,0xFD987193,0xA679438E,0x49B40821,
		0xF61E2562,0xC040B340,0x265E5A51,0xE9B6C7AA,0xD62F105D,0x02441453,0xD8A1E681,0xE7D3FBC8,
		0x21E1CDE6,0xC33707D6,0xF4D50D87,0x455A14ED,0xA9E3E905,0xFCEFA3F8,0x676F02D9,0x8D2A4C8A,
		0xFFFA3942,0x8771F681,0x6D9D6122,0xFDE5380C,0xA4BEEA44,0x4BDECFA9,0xF6BB4B60,0xBEBFBC70,
		0x289B7EC6,0xEAA127FA,0xD4EF3085,0x04881D05,0xD9D4D039,0xE6DB99E5,0x1FA27CF8,0xC4AC5665,
		0xF4292244,0x432AFF97,0xAB9423A7,0xFC93A039,0x655B59C3,0x8F0CCC92,0xFFEFF47D,0x85845DD1,
		0x6FA87E4F,0xFE2CE6E0,0xA3014314,0x4E0811A1,0xF7537E82,0xBD3AF235,0x2AD7D2BB,0xEB86D391
		};

	unsigned int s[64]={
		7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,
		5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
		4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
		6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21
	};

	unsigned int m[64]={
		0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
		1,6,11,0,5,10,15,4,9,14,3,8,13,2,7,12,
		5,8,11,14,1,4,7,10,13,0,3,6,9,12,15,2,
		0,7,14,5,12,3,10,1,8,15,6,13,4,11,2,9
	};


	unsigned char in[56];
	unsigned int a[64] = {0};
	unsigned int M[16] = {0};
	unsigned int load = 0;
	unsigned int f,g,h;
	g = 0;
	printf("Input:\n");
	scanf("%s",in);
	for(f = 0;in[f]!= 0; f++)
	{
		a[load] = in[f];
		load++;
	}

	if(56 != f)
	{
		a[load] = 0x80;
	}

	h=f*8;
	if(0!= h/256)
	{
		a[56] = h/256;
		a[57] = h%256;
	}
	else a[56] = h;

	for(f = 0;a[f]!= 0;f+=4)
	{
		f+=3;
		M[g] = a[f]*256*256*256;
		f--;
		M[g]+= a[f]*256*256;
		f--;
		M[g]+= a[f]*256;
		f--;
		M[g]+=a[f];
		g++;
	}

	g = 14;
	for(f = 56;a[f]!= 0;f+=4)
	{
		f+=3;
		M[g] = a[f]*256*256*256;
		f--;
		M[g]+= a[f]*256*256;
		f--;
		M[g]+= a[f]*256;
		f--;
		M[g]+=a[f];
		g++;
	}
	printf("%x\n",*M);
	for(i = 0; i < 4; i++)
		{
			for(j=0;j<16;j+=4)
			{
				FF(A,B,C,D,M[m[j]],s[j],T[j]);
				FF(D,A,B,C,M[m[j+1]],s[j+1],T[j+1]);
				FF(C,D,A,B,M[m[j+2]],s[j+2],T[j+2]);
				FF(B,C,D,A,M[m[j+3]],s[j+3],T[j+3]);
			}
			for(;j<32;j+=4)
			{
				GG(A,B,C,D,M[m[j]],s[j],T[j]);
				GG(D,A,B,C,M[m[j+1]],s[j+1],T[j+1]);
				GG(C,D,A,B,M[m[j+2]],s[j+2],T[j+2]);
				GG(B,C,D,A,M[m[j+3]],s[j+3],T[j+3]);
			}
			for(;j<48;j+=4)
					{
						HH(A,B,C,D,M[m[j]],s[j],T[j]);
						HH(D,A,B,C,M[m[j+1]],s[j+1],T[j+1]);
						HH(C,D,A,B,M[m[j+2]],s[j+2],T[j+2]);
						HH(B,C,D,A,M[m[j+3]],s[j+3],T[j+3]);
					}
			for(;j<64;j+=4)
					{
						II(A,B,C,D,M[m[j]],s[j],T[j]);
						II(D,A,B,C,M[m[j+1]],s[j+1],T[j+1]);
						II(C,D,A,B,M[m[j+2]],s[j+2],T[j+2]);
						II(B,C,D,A,M[m[j+3]],s[j+3],T[j+3]);
					}
		}

	out[0]=D;
	out[1]=C;
	out[2]=B;
	out[3]=A;
	
	for(j=0;j<4;j++)
	{
		printf("%x",out[j]);
	}
	
}
