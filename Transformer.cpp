#include<cmath>
#include<ap_int.h>
#include"Transformer.h"

#define W 32
#define H 64
#define W_H 32
#define P 64


//矩阵乘法    C=A*B  A矩阵规模为h*hw,B矩阵规模为hw*W,C矩阵规模为h*w
void matrixmul(float *A,float *B,float *C,int h,int w,int hw)
{
	loop1:
	for(int i=0;i<h;i++)
	{
		loop2:
		for(int j=0;j<w;j++)
		{
			int p=0;
			loop3:
			for(int k=0;k<hw;k++)
			{
				p+=A[i*hw+k]*B[k*w+j];
			}
			C[i*w+j]=p;
		}
	}
}

//矩阵转置    out=in_T 输入矩阵规模为h*w
void transpose(float *in,float *out,int h,int w)
{
	for (int i=0;i<h;i++)
	{
		for (int j=0;j<w;j++)
		{
			out[j*h+i]=in[i*w+j];
		}
	}
}

//softmax函数
void softmax(float *input,float *res,int h,int w,int Max_i,int Max_j)
{
	float probability[h][w];
	float sum = 0;
	for(int i=0;i<h;i++)
	{
		for(int j=0;j<w;j++)
		{
			probability[i][j] = expf(input[i*w+j]);
			sum += probability[i][j];
		}
	}
	int max_i=0;
	int max_j=0;

	for(int i=0;i<h;i++)
	{
		for(int j=0;j<w;j++)
		{
			res[i*w+j]=probability[i][j]/sum;
			float res1 = res[i*w+j];
			float res2 = res[max_i*w+max_j];
			if(res1>res2)
			{
				max_i=i;
				max_j=j;
			}
		}
	}
	Max_i=max_i;
	Max_j=max_j;
}

//自注意力机制 输入矩阵in，通过w维数改变得到Q、K、V,再通过一系列运算得到输出
//in的规模：in_h*in_w   w的规模：out_h*in_h   out的规模：out_h*in_w
void selfattention(float *in,float *w_q,float *w_k,float *w_v,float *out,int in_h,int in_w,int out_h)
{
	float Q[out_h][in_w];
	float K[out_h][in_w];
	float V[out_h][in_w];
	matrixmul(w_q,in,Q[0],out_h,in_w,in_h);
	matrixmul(w_k,in,K[0],out_h,in_w,in_h);
	matrixmul(w_v,in,V[0],out_h,in_w,in_h);
	float K_T[in_w][out_h];
	transpose(K[0],K_T[0],out_h,in_w);
	float S[in_w][in_w];
	matrixmul(K_T[0],Q[0],S[0],in_w,in_w,out_h);
	float SS[in_w][in_w];
	int max_i;
	int max_j;
	softmax(S[0],SS[0],in_w,in_w,max_i,max_j);
	matrixmul(V[0],SS[0],out,out_h,in_w,in_w);
}

//拼接矩阵 将八个矩阵拼接在一起
void concat(float *x1,float *x2,float *x3,float *x4,float *x5,float *x6,float *x7,float *x8,float *x,int h,int w)
{
	for(int i=0;i<h;i++)
	{
		for (int j=0;j<w;j++)
		{
			x[i*w+j]=x1[i*w+j];
			x[(i+h)*w+j]=x2[i*w+j];
			x[(i+2*h)*w+j]=x3[i*w+j];
			x[(i+3*h)*w+j]=x4[i*w+j];
			x[(i+4*h)*w+j]=x5[i*w+j];
			x[(i+5*h)*w+j]=x6[i*w+j];
			x[(i+6*h)*w+j]=x7[i*w+j];
			x[(i+7*h)*w+j]=x8[i*w+j];
		}
	}
}
//w_o规模：h * 8*w_H   w的规模：w_h*in_h out的规模：h*w
void multi8head_attention(float *in,float *out,int w,int h,int w_h,
		float *w_q_1,float *w_k_1,float *w_v_1,
		float *w_q_2,float *w_k_2,float *w_v_2,
		float *w_q_3,float *w_k_3,float *w_v_3,
		float *w_q_4,float *w_k_4,float *w_v_4,
		float *w_q_5,float *w_k_5,float *w_v_5,
		float *w_q_6,float *w_k_6,float *w_v_6,
		float *w_q_7,float *w_k_7,float *w_v_7,
		float *w_q_8,float *w_k_8,float *w_v_8,
		float *w_o)
{
	float out_1[w_h][w];
	float out_2[w_h][w];
	float out_3[w_h][w];
	float out_4[w_h][w];
	float out_5[w_h][w];
	float out_6[w_h][w];
	float out_7[w_h][w];
	float out_8[w_h][w];

	selfattention(in,w_q_1,w_k_1,w_v_1,out_1[0],h,w,w_h);
	selfattention(in,w_q_2,w_k_2,w_v_2,out_2[0],h,w,w_h);
	selfattention(in,w_q_3,w_k_3,w_v_3,out_3[0],h,w,w_h);
	selfattention(in,w_q_4,w_k_4,w_v_4,out_4[0],h,w,w_h);
	selfattention(in,w_q_5,w_k_5,w_v_5,out_5[0],h,w,w_h);
	selfattention(in,w_q_6,w_k_6,w_v_6,out_6[0],h,w,w_h);
	selfattention(in,w_q_7,w_k_7,w_v_7,out_7[0],h,w,w_h);
	selfattention(in,w_q_8,w_k_8,w_v_8,out_8[0],h,w,w_h);

	float out_0[8*w_h][w];
	concat(out_1[0],out_2[0],out_3[0],out_4[0],out_5[0],out_6[0],out_7[0],out_8[0],out_0[0],w_h,w);
	matrixmul(w_o,out_0[0],out,h,w,8*w_h);
}

void vectoradd(float *A,float *B,float *C,int h,int w)//用于残差连接
{

	vectoradd:
	for(int i=0;i<h;i++)
	{
		for(int j=0;j<w;j++)
		{
			C[i*w+j]=A[i*w+j]+B[i*w+j];
		}

	}
}
void layernorm(float *in,float *out,int h,int w)
{
	for (int i=0;i<w;i++)
	{
		float sum=0;

		for (int j=0;j<h;j++)
		{
			sum+=in[j*w+i];
		}
		float mean=sum/h;

		float S_2;
		for (int j=0;j<h;j++)
		{
			S_2+=(in[j*w+i]-mean)*(in[j*w+i]-mean);
		}
		S_2/=h;
		float S=sqrt(S_2);
		for (int j=0;j<h;j++)
		{
			out[j*w+i]=(in[j*w+i]-mean)/S;
		}
	}
}

//全连接层  p为中间层的维度
void MLP(float *A,float *w_1,float *w_2,float *B,int h,int w,int p)
{
	float res[p][w];
	matrixmul(w_1,A,res[0],p,w,h);
	matrixmul(w_2,res[0],B,h,w,p);
}

//encode部分(此处设置N=1)
void encode(float *in,float *out,
				float *w_q_1,float *w_k_1,float *w_v_1,
				float *w_q_2,float *w_k_2,float *w_v_2,
				float *w_q_3,float *w_k_3,float *w_v_3,
				float *w_q_4,float *w_k_4,float *w_v_4,
				float *w_q_5,float *w_k_5,float *w_v_5,
				float *w_q_6,float *w_k_6,float *w_v_6,
				float *w_q_7,float *w_k_7,float *w_v_7,
				float *w_q_8,float *w_k_8,float *w_v_8,
				float *w_o,float *w1,float *w2,
				int w,int h,int w_h,int p)
{
	float out1_1[h][w];
	float out1_2[h][w];
	float out1_3[h][w];
	float out1_4[h][w];
	float out1_5[h][w];
	multi8head_attention(in,out1_1[0],w,h,w_h,
			w_q_1,w_k_1,w_v_1,
			w_q_2,w_k_2,w_v_2,
			w_q_3,w_k_3,w_v_3,
			w_q_4,w_k_4,w_v_4,
			w_q_5,w_k_5,w_v_5,
			w_q_6,w_k_6,w_v_6,
			w_q_7,w_k_7,w_v_7,
			w_q_8,w_k_8,w_v_8,
			w_o);
	layernorm(out1_1[0],out1_2[0],h,w);
	vectoradd(in,out1_2[0],out1_3[0],h,w);

	MLP(out1_3[0],w1,w2,out1_4[0],h,w,p);
	layernorm(out1_4[0],out1_5[0],h,w);
	vectoradd(out1_3[0],out1_5[0],out,h,w);
}


void mask(float *in,float *out,int h, int w)
{
	for (int i = 0; i<h; i++)
	{
		for(int j = 0; j<w; j++)
		{
				out[i*w+j] = i<=j ? in[i*w+j] : -10000;
		}
	}
}


void attention(float *in,float *encode_out,float *w_q,float *w_k,float *w_v,float *out,int in_h,int in_w,int out_h)
{
	float Q[out_h][in_w];
	float K[out_h][in_w];
	float V[out_h][in_w];
	matrixmul(w_q,encode_out,Q[0],out_h,in_w,in_h);
	matrixmul(w_k,encode_out,K[0],out_h,in_w,in_h);
	matrixmul(w_v,in,V[0],out_h,in_w,in_h);
	float K_[in_w][out_h];
	transpose(K[0],K_[0],out_h,in_w);
	float S[in_w][in_w];
	matrixmul(K_[0],Q[0],S[0],in_w,in_w,out_h);
	float SS[in_w][in_w];
	int max_i;
	int max_j;
	softmax(S[0],SS[0],in_w,in_w,max_i,max_j);
	matrixmul(V[0],SS[0],out,out_h,in_w,in_w);
}
//w_o规模：h * 8*w_H   w的规模：w_h*in_h out的规模：h*w
void decode_multi8head_attention(float *in,float *encode_out,float *out,int w,int h,int w_h,
		float *w_q_1,float *w_k_1,float *w_v_1,
		float *w_q_2,float *w_k_2,float *w_v_2,
		float *w_q_3,float *w_k_3,float *w_v_3,
		float *w_q_4,float *w_k_4,float *w_v_4,
		float *w_q_5,float *w_k_5,float *w_v_5,
		float *w_q_6,float *w_k_6,float *w_v_6,
		float *w_q_7,float *w_k_7,float *w_v_7,
		float *w_q_8,float *w_k_8,float *w_v_8,
		float *w_o)
{
	float out_1[w_h][w];
	float out_2[w_h][w];
	float out_3[w_h][w];
	float out_4[w_h][w];
	float out_5[w_h][w];
	float out_6[w_h][w];
	float out_7[w_h][w];
	float out_8[w_h][w];

	attention(in,encode_out,w_q_1,w_k_1,w_v_1,out_1[0],h,w,w_h);
	attention(in,encode_out,w_q_2,w_k_2,w_v_2,out_2[0],h,w,w_h);
	attention(in,encode_out,w_q_3,w_k_3,w_v_3,out_3[0],h,w,w_h);
	attention(in,encode_out,w_q_4,w_k_4,w_v_4,out_4[0],h,w,w_h);
	attention(in,encode_out,w_q_5,w_k_5,w_v_5,out_5[0],h,w,w_h);
	attention(in,encode_out,w_q_6,w_k_6,w_v_6,out_6[0],h,w,w_h);
	attention(in,encode_out,w_q_7,w_k_7,w_v_7,out_7[0],h,w,w_h);
	attention(in,encode_out,w_q_8,w_k_8,w_v_8,out_8[0],h,w,w_h);

	float out_0[8*w_h][w];
	concat(out_1[0],out_2[0],out_3[0],out_4[0],out_5[0],out_6[0],out_7[0],out_8[0],out_0[0],w_h,w);
	matrixmul(w_o,out_0[0],out,h,w,8*w_h);
}

//decode部分(此处设置N=1)
void decode(float *in,float *encode_out,float *out,
				float *w_q_1,float *w_k_1,float *w_v_1,
				float *w_q_2,float *w_k_2,float *w_v_2,
				float *w_q_3,float *w_k_3,float *w_v_3,
				float *w_q_4,float *w_k_4,float *w_v_4,
				float *w_q_5,float *w_k_5,float *w_v_5,
				float *w_q_6,float *w_k_6,float *w_v_6,
				float *w_q_7,float *w_k_7,float *w_v_7,
				float *w_q_8,float *w_k_8,float *w_v_8,
				float *w_q,float *w_k,float *w_v,
				float *w_o,float *w1,float *w2,
				int w,int h,int w_h,int p
				)
{
	float out1_1[h][w];
	float out1_2[h][w];
	float out1_3[h][w];
	float out1_4[h][w];
	float out1_5[h][w];
	float out1_6[h][w];
	float out1_7[h][w];
	float out1_8[h][w];
	float out1_9[h][w];

	float mask_out[h][w];
	mask(in,mask_out[0],w,h);
	multi8head_attention(mask_out[0],out1_1[0],w,h,w_h,
			w_q_1,w_k_1,w_v_1,
			w_q_2,w_k_2,w_v_2,
			w_q_3,w_k_3,w_v_3,
			w_q_4,w_k_4,w_v_4,
			w_q_5,w_k_5,w_v_5,
			w_q_6,w_k_6,w_v_6,
			w_q_7,w_k_7,w_v_7,
			w_q_8,w_k_8,w_v_8,
			w_o);
	layernorm(out1_1[0],out1_2[0],h,w);
	vectoradd(in,out1_2[0],out1_3[0],h,w);


	decode_multi8head_attention(out1_3[0],encode_out,out1_4[0],w,h,w_h,
				w_q_1,w_k_1,w_v_1,
				w_q_2,w_k_2,w_v_2,
				w_q_3,w_k_3,w_v_3,
				w_q_4,w_k_4,w_v_4,
				w_q_5,w_k_5,w_v_5,
				w_q_6,w_k_6,w_v_6,
				w_q_7,w_k_7,w_v_7,
				w_q_8,w_k_8,w_v_8,
				w_o);
	layernorm(out1_4[0],out1_5[0],h,w);
	vectoradd(out1_3[0],out1_5[0],out1_6[0],h,w);

	MLP(out1_6[0],w1,w2,out1_7[0],h,w,p);
	layernorm(out1_7[0],out1_8[0],h,w);
	vectoradd(out1_6[0],out1_8[0],out,h,w);
}

void transformer(float *in,float *out,
		float *encode_w_q_1,float *encode_w_k_1,float *encode_w_v_1,
		float *encode_w_q_2,float *encode_w_k_2,float *encode_w_v_2,
		float *encode_w_q_3,float *encode_w_k_3,float *encode_w_v_3,
		float *encode_w_q_4,float *encode_w_k_4,float *encode_w_v_4,
		float *encode_w_q_5,float *encode_w_k_5,float *encode_w_v_5,
		float *encode_w_q_6,float *encode_w_k_6,float *encode_w_v_6,
		float *encode_w_q_7,float *encode_w_k_7,float *encode_w_v_7,
		float *encode_w_q_8,float *encode_w_k_8,float *encode_w_v_8,
		float *encode_w_o,float *encode_w1,float *encode_w2,
		int w,int h,int w_h,int p,
		float *decode_w_q_1,float *decode_w_k_1,float *decode_w_v_1,
		float *decode_w_q_2,float *decode_w_k_2,float *decode_w_v_2,
		float *decode_w_q_3,float *decode_w_k_3,float *decode_w_v_3,
		float *decode_w_q_4,float *decode_w_k_4,float *decode_w_v_4,
		float *decode_w_q_5,float *decode_w_k_5,float *decode_w_v_5,
		float *decode_w_q_6,float *decode_w_k_6,float *decode_w_v_6,
		float *decode_w_q_7,float *decode_w_k_7,float *decode_w_v_7,
		float *decode_w_q_8,float *decode_w_k_8,float *decode_w_v_8,
		float *decode_w_q,float *decode_w_k,float *decode_w_v,
		float *decode_w_o,float *decode_w1,float *decode_w2
		)
{
	float encode_out[h][w];
	encode(in,encode_out[0],
			encode_w_q_1,encode_w_k_1,encode_w_v_1,
			encode_w_q_2,encode_w_k_2,encode_w_v_2,
			encode_w_q_3,encode_w_k_3,encode_w_v_3,
			encode_w_q_4,encode_w_k_4,encode_w_v_4,
			encode_w_q_5,encode_w_k_5,encode_w_v_5,
			encode_w_q_6,encode_w_k_6,encode_w_v_6,
			encode_w_q_7,encode_w_k_7,encode_w_v_7,
			encode_w_q_8,encode_w_k_8,encode_w_v_8,
			encode_w_o,encode_w1,encode_w2,
			w,h,w_h,p);

	decode(in,encode_out[0],out,
			decode_w_q_1,decode_w_k_1,decode_w_v_1,
			decode_w_q_2,decode_w_k_2,decode_w_v_2,
			decode_w_q_3,decode_w_k_3,decode_w_v_3,
			decode_w_q_4,decode_w_k_4,decode_w_v_4,
			decode_w_q_5,decode_w_k_5,decode_w_v_5,
			decode_w_q_6,decode_w_k_6,decode_w_v_6,
			decode_w_q_7,decode_w_k_7,decode_w_v_7,
			decode_w_q_8,decode_w_k_8,decode_w_v_8,
			decode_w_q,decode_w_k,decode_w_v,
			decode_w_o,decode_w1,decode_w2,
			w,h,w_h,p
			);
}
void soc(float in[H][W],
		float out[H][W],
		float encode_w_q_1[W_H][H],
		float encode_w_k_1[W_H][H],
		float encode_w_v_1[W_H][H],
		float encode_w_q_2[W_H][H],
		float encode_w_k_2[W_H][H],
		float encode_w_v_2[W_H][H],
		float encode_w_q_3[W_H][H],
		float encode_w_k_3[W_H][H],
		float encode_w_v_3[W_H][H],
		float encode_w_q_4[W_H][H],
		float encode_w_k_4[W_H][H],
		float encode_w_v_4[W_H][H],
		float encode_w_q_5[W_H][H],
		float encode_w_k_5[W_H][H],
		float encode_w_v_5[W_H][H],
		float encode_w_q_6[W_H][H],
		float encode_w_k_6[W_H][H],
		float encode_w_v_6[W_H][H],
		float encode_w_q_7[W_H][H],
		float encode_w_k_7[W_H][H],
		float encode_w_v_7[W_H][H],
		float encode_w_q_8[W_H][H],
		float encode_w_k_8[W_H][H],
		float encode_w_v_8[W_H][H],

		float decode_w_q_1[W_H][H],
		float decode_w_k_1[W_H][H],
		float decode_w_v_1[W_H][H],
		float decode_w_q_2[W_H][H],
		float decode_w_k_2[W_H][H],
		float decode_w_v_2[W_H][H],
		float decode_w_q_3[W_H][H],
		float decode_w_k_3[W_H][H],
		float decode_w_v_3[W_H][H],
		float decode_w_q_4[W_H][H],
		float decode_w_k_4[W_H][H],
		float decode_w_v_4[W_H][H],
		float decode_w_q_5[W_H][H],
		float decode_w_k_5[W_H][H],
		float decode_w_v_5[W_H][H],
		float decode_w_q_6[W_H][H],
		float decode_w_k_6[W_H][H],
		float decode_w_v_6[W_H][H],
		float decode_w_q_7[W_H][H],
		float decode_w_k_7[W_H][H],
		float decode_w_v_7[W_H][H],
		float decode_w_q_8[W_H][H],
		float decode_w_k_8[W_H][H],
		float decode_w_v_8[W_H][H],

		float decode_w_q[W_H][H],
		float decode_w_k[W_H][H],
		float decode_w_v[W_H][H],

		float encode_w1[P][H],
		float encode_w2[P][H],
		float decode_w1[P][H],
		float decode_w2[P][H],

		float encode_w_o[H][8*W_H],
		float decode_w_o[H][8*W_H])
{
	transformer(in[0],out[0],
			encode_w_q_1[0],encode_w_k_1[0],encode_w_v_1[0],
			encode_w_q_2[0],encode_w_k_2[0],encode_w_v_2[0],
			encode_w_q_3[0],encode_w_k_3[0],encode_w_v_3[0],
			encode_w_q_4[0],encode_w_k_4[0],encode_w_v_4[0],
			encode_w_q_5[0],encode_w_k_5[0],encode_w_v_5[0],
			encode_w_q_6[0],encode_w_k_6[0],encode_w_v_6[0],
			encode_w_q_7[0],encode_w_k_7[0],encode_w_v_7[0],
			encode_w_q_8[0],encode_w_k_8[0],encode_w_v_8[0],
			encode_w_o[0],encode_w1[0],encode_w2[0],
			W,H,W_H,P,
			decode_w_q_1[0],decode_w_k_1[0],decode_w_v_1[0],
			decode_w_q_2[0],decode_w_k_2[0],decode_w_v_2[0],
			decode_w_q_3[0],decode_w_k_3[0],decode_w_v_3[0],
			decode_w_q_4[0],decode_w_k_4[0],decode_w_v_4[0],
			decode_w_q_5[0],decode_w_k_5[0],decode_w_v_5[0],
			decode_w_q_6[0],decode_w_k_6[0],decode_w_v_6[0],
			decode_w_q_7[0],decode_w_k_7[0],decode_w_v_7[0],
			decode_w_q_8[0],decode_w_k_8[0],decode_w_v_8[0],
			decode_w_q[0],decode_w_k[0],decode_w_v[0],
			decode_w_o[0],decode_w1[0],decode_w2[0]
			);

}




