#include "Transformer.h"
#include <cstdlib>
#include <iostream>
using namespace std;

int main()
{
	float in[H][W];
	float out[H][W];
	float encode_w_q_1[W_H][H];
	float encode_w_k_1[W_H][H];
	float encode_w_v_1[W_H][H];
	float encode_w_q_2[W_H][H];
	float encode_w_k_2[W_H][H];
	float encode_w_v_2[W_H][H];
	float encode_w_q_3[W_H][H];
	float encode_w_k_3[W_H][H];
	float encode_w_v_3[W_H][H];
	float encode_w_q_4[W_H][H];
	float encode_w_k_4[W_H][H];
	float encode_w_v_4[W_H][H];
	float encode_w_q_5[W_H][H];
	float encode_w_k_5[W_H][H];
	float encode_w_v_5[W_H][H];
	float encode_w_q_6[W_H][H];
	float encode_w_k_6[W_H][H];
	float encode_w_v_6[W_H][H];
	float encode_w_q_7[W_H][H];
	float encode_w_k_7[W_H][H];
	float encode_w_v_7[W_H][H];
	float encode_w_q_8[W_H][H];
	float encode_w_k_8[W_H][H];
	float encode_w_v_8[W_H][H];

	float decode_w_q_1[W_H][H];
	float decode_w_k_1[W_H][H];
	float decode_w_v_1[W_H][H];
	float decode_w_q_2[W_H][H];
	float decode_w_k_2[W_H][H];
	float decode_w_v_2[W_H][H];
	float decode_w_q_3[W_H][H];
	float decode_w_k_3[W_H][H];
	float decode_w_v_3[W_H][H];
	float decode_w_q_4[W_H][H];
	float decode_w_k_4[W_H][H];
	float decode_w_v_4[W_H][H];
	float decode_w_q_5[W_H][H];
	float decode_w_k_5[W_H][H];
	float decode_w_v_5[W_H][H];
	float decode_w_q_6[W_H][H];
	float decode_w_k_6[W_H][H];
	float decode_w_v_6[W_H][H];
	float decode_w_q_7[W_H][H];
	float decode_w_k_7[W_H][H];
	float decode_w_v_7[W_H][H];
	float decode_w_q_8[W_H][H];
	float decode_w_k_8[W_H][H];
	float decode_w_v_8[W_H][H];

	float decode_w_q[W_H][H];
	float decode_w_k[W_H][H];
	float decode_w_v[W_H][H];

	float encode_w1[P][H];
	float encode_w2[P][H];
	float decode_w1[P][H];
	float decode_w2[P][H];

	float encode_w_o[H][8*W_H];
	float decode_w_o[H][8*W_H];

	int i, j;

	for(i = 0;i<H;i++){
		for(j=0;j<W;j++)
			in[i][j] = rand()%100;
	}

	for(i = 0;i<P;i++){
		for(j=0;j<H;j++)
			encode_w1[i][j]= rand()%100;
			encode_w2[i][j]= rand()%100;
			decode_w1[i][j]= rand()%100;
			decode_w2[i][j]= rand()%100;
	}

	for(i = 0;i<H;i++){
		for(j=0;j<8*W_H;j++)
			encode_w_o[i][j] = rand()%100;
			decode_w_o[i][j] = rand()%100;
	}

	for(i = 0;i<W_H;i++){
		for(j=0;j<H;j++)
			 encode_w_q_1[i][j]= rand()%100;
			 encode_w_k_1[i][j]= rand()%100;
			 encode_w_v_1[i][j]= rand()%100;
			 encode_w_q_2[i][j]= rand()%100;
			 encode_w_k_2[i][j]= rand()%100;
			 encode_w_v_2[i][j]= rand()%100;
			 encode_w_q_3[i][j]= rand()%100;
			 encode_w_k_3[i][j]= rand()%100;
			 encode_w_v_3[i][j]= rand()%100;
			 encode_w_q_4[i][j]= rand()%100;
			 encode_w_k_4[i][j]= rand()%100;
			 encode_w_v_4[i][j]= rand()%100;
			 encode_w_q_5[i][j]= rand()%100;
			 encode_w_k_5[i][j]= rand()%100;
			 encode_w_v_5[i][j]= rand()%100;
			 encode_w_q_6[i][j]= rand()%100;
			 encode_w_k_6[i][j]= rand()%100;
			 encode_w_v_6[i][j]= rand()%100;
			 encode_w_q_7[i][j]= rand()%100;
			 encode_w_k_7[i][j]= rand()%100;
			 encode_w_v_7[i][j]= rand()%100;
			 encode_w_q_8[i][j]= rand()%100;
			 encode_w_k_8[i][j]= rand()%100;
			 encode_w_v_8[i][j]= rand()%100;

			 decode_w_q_1[i][j]= rand()%100;
			 decode_w_k_1[i][j]= rand()%100;
			 decode_w_v_1[i][j]= rand()%100;
			 decode_w_q_2[i][j]= rand()%100;
			 decode_w_k_2[i][j]= rand()%100;
			 decode_w_v_2[i][j]= rand()%100;
			 decode_w_q_3[i][j]= rand()%100;
			 decode_w_k_3[i][j]= rand()%100;
			 decode_w_v_3[i][j]= rand()%100;
			 decode_w_q_4[i][j]= rand()%100;
			 decode_w_k_4[i][j]= rand()%100;
			 decode_w_v_4[i][j]= rand()%100;
			 decode_w_q_5[i][j]= rand()%100;
			 decode_w_k_5[i][j]= rand()%100;
			 decode_w_v_5[i][j]= rand()%100;
			 decode_w_q_6[i][j]= rand()%100;
			 decode_w_k_6[i][j]= rand()%100;
			 decode_w_v_6[i][j]= rand()%100;
			 decode_w_q_7[i][j]= rand()%100;
			 decode_w_k_7[i][j]= rand()%100;
			 decode_w_v_7[i][j]= rand()%100;
			 decode_w_q_8[i][j]= rand()%100;
			 decode_w_k_8[i][j]= rand()%100;
			 decode_w_v_8[i][j]= rand()%100;

			 decode_w_q[i][j]= rand()%100;
			 decode_w_k[i][j]= rand()%100;
			 decode_w_v[i][j]= rand()%100;
	}
	soc(in,out,\
        encode_w_q_1,\
        encode_w_k_1,\
        encode_w_v_1,\
        encode_w_q_2,\
		encode_w_k_2,\
		encode_w_v_2,\
		encode_w_q_3,\
		encode_w_k_3,\
		encode_w_v_3,\
		encode_w_q_4,\
		encode_w_k_4,\
		encode_w_v_4,\
		encode_w_q_5,\
		encode_w_k_5,\
		encode_w_v_5,\
		encode_w_q_6,\
		encode_w_k_6,\
		encode_w_v_6,\
		encode_w_q_7,\
		encode_w_k_7,\
		encode_w_v_7,\
		encode_w_q_8,\
		encode_w_k_8,\
		encode_w_v_8,\

		decode_w_q_1,\
		decode_w_k_1,\
		decode_w_v_1,\
		decode_w_q_2,\
		decode_w_k_2,\
		decode_w_v_2,\
		decode_w_q_3,\
		decode_w_k_3,\
		decode_w_v_3,\
		decode_w_q_4,\
		decode_w_k_4,\
		decode_w_v_4,\
		decode_w_q_5,\
		decode_w_k_5,\
		decode_w_v_5,\
		decode_w_q_6,\
		decode_w_k_6,\
		decode_w_v_6,\
		decode_w_q_7,\
		decode_w_k_7,\
		decode_w_v_7,\
		decode_w_q_8,\
		decode_w_k_8,\
		decode_w_v_8,\

		decode_w_q,\
		decode_w_k,\
		decode_w_v,\

		encode_w1,\
		encode_w2,\
		decode_w1,\
		decode_w2,\

		encode_w_o,\
		decode_w_o);

	std::cout<<"输入矩阵:"<<std::endl;
	for (i=0;i<H;i++){
			for (j=0;j<W;j++){
				std::cout<<in[i][j]<<" ";
			}
			std::cout<<std::endl;
		}
	std::cout<<std::endl;
	std::cout<<"输出矩阵:"<<std::endl;
	for (i=0;i<H;i++){
			for (j=0;j<W;j++){
				std::cout<<out[i][j]<<" ";
			}
			std::cout<<std::endl;
		}
	std::cout<<std::endl;


}
