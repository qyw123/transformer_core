#ifndef __SELFATTENTION_H__
#define __SELFATTENTION_H__

#define W 32
#define H 64
#define W_H 32
#define P 64

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
		float decode_w_o[H][8*W_H]);
#endif