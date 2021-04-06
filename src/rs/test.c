#include <string.h>

#include "op.h"
#include "array.h"
#include "decode.h"
#include "encode.h"

#define BUFFER_SIZE 100


int main()
{
	struct gf_tables *gf_table = malloc(sizeof(struct gf_tables));
	gf_table->gf_exp = malloc(sizeof(struct Array));
	gf_table->gf_log = malloc(sizeof(struct Array));
	initArray(gf_table->gf_exp, 512);
	initArray(gf_table->gf_log, 256);
	gf_table = init_tables();

	printf(">>> Reed-Solomon Error Correction\n");
	printf("Enter the string you want to test:\n");

	struct Array *msg_in = malloc(sizeof(struct Array));
	initArray(msg_in, 50);
	char my_msg[BUFFER_SIZE];

	fgets( my_msg, sizeof(my_msg), stdin );
    printf("\n");
	//gets(my_msg);
	//strcpy(my_msg, "Hello world");
	for (size_t i = 0; i < strlen(my_msg); i++) {
		msg_in->array[i] = (int)my_msg[i];
		insertArray(msg_in);
	}


	printf("Message given: [");
	for (size_t i = 0; i < msg_in->used; i++) {
        if (i == msg_in->used - 1)
		    printf("%u",msg_in->array[i]);
        else
            printf("%u,",msg_in->array[i]);
	}
	printf("]\n");

	struct Array *msg = malloc(sizeof(struct Array));
	initArray(msg, 170);

	struct Array *err_loc = malloc(sizeof(struct Array));

	struct Array *synd = malloc(sizeof(struct Array));

	struct Array *pos = malloc(sizeof(struct Array));

	struct Array *rev_pos = malloc(sizeof(struct Array));

	msg = rs_encode_msg(msg_in, 14, gf_table);

	/*msg->array[0] = 64;
	 msg->array[1] = 166;
	 msg->array[2] = 134;
	 msg->array[3] = 86;
	 msg->array[4] = 140;
	 msg->array[5] = 140;
	 msg->array[6] = 247;
	 msg->array[7] = 118;
	 msg->array[8] = 247;
	 msg->array[9] = 38;
	 msg->array[10] = 198;
	 msg->array[11] = 64;
	 msg->array[12] = 236;
	 msg->array[13] = 17;
	 msg->array[14] = 236;
	 msg->array[15] = 17;
	 msg->array[16] = 236;
	 msg->array[17] = 17;
	 msg->array[18] = 236;
	 msg->array[19] = 134;
	 msg->array[20] = 160;
	 msg->array[21] = 87;
	 msg->array[22] = 135;
	 msg->array[23] = 22;
	 msg->array[24] = 250;
	 msg->array[25] = 219;
	 msg->array[26] = 76;
	 msg->array[27] = 123;
	 msg->array[28] = 7;
	 msg->used = 29;*/

	/*msg->array[0] = 99;
	 msg->array[1] = 111;
	 msg->array[2] = 117;
	 msg->array[3] = 99;
	 msg->array[4] = 111;
	 msg->array[5] = 117;
	 msg->array[6] = 10;
	 msg->array[7] = 18;
	 msg->array[8] = 86;
	 msg->array[9] = 219;
	 msg->array[10] = 215;
	 msg->array[11] = 177;
	 msg->array[12] = 99;
	 msg->array[13] = 22;
	 msg->array[14] = 137;
	 msg->array[15] = 41;
	 msg->array[16] = 38;
	 msg->array[17] = 236;
	 msg->used = 18;*/

	printf("Message Encoded: [");
	for (size_t i = 0; i < msg->used; i++) {
        if (i == msg->used - 1)
            printf("%u", msg->array[i]);
        else
            printf("%u,",msg->array[i]);
	}
	printf("]\n");


	//Tempering msg
	msg->array[0] = 0;
	msg->array[3] = 0;
	msg->array[10] = 0;

	/*printf("Message Tempered: [");
	for (size_t i = 0; i < strlen(my_msg); i++) {
		printf("%u,",msg->array[i]);
	}
	printf("]\n");*/

	printf("Message Tempered: ");
	for (size_t i = 0; i < strlen(my_msg); i++) {
		printf("%c",msg->array[i]);
	}
	printf("\n");
	/*printf("Msg Encoded: [");
	for (size_t i = 0; i < msg->used; i++) {
		printf("%u,",msg->array[i]);
	}
	printf("]\n");*/

	synd = rs_calc_syndromes(msg, 14, gf_table);
	/*printf("synd : ");
	for (size_t i = 0; i < synd->used; i++) {
		printf("%u, ",synd->array[i]);
	}
	printf("\n");*/
	err_loc = rs_find_error_locator(synd, 14, 0, gf_table);
	/*printf("err_loc : ");
	for (size_t i = 0; i < err_loc->used; i++) {
		printf("%u, ",err_loc->array[i]);
	}
	printf("\n");*/
	pos = rs_find_errors(reverse_arr(err_loc), msg->used, gf_table);
	/*printf("err_pos : ");
	for (size_t i = 0; i < pos->used; i++) {
		printf("%u, ",pos->array[i]);
	}
	printf("\n");*/
	rev_pos = reverse_arr(pos);

	printf("Error indexes: [");
	for (size_t i = 0; i < rev_pos->used; i++) {
        if (i == rev_pos->used - 1)
            printf("%u", rev_pos->array[i]);
        else
            printf("%u,", rev_pos->array[i]);
	}
	printf("]\n");

	struct Array *err_pos = malloc(sizeof(struct Array));
	initArray(err_pos, 3);
	err_pos->array[0] = 0;

	//msg = rs_correct_errdata(msg, synd, pos, gf_table);
	msg = rs_correct_msg(msg, 14, err_pos, gf_table);

	printf("Message Corrected: [");
	for (size_t i = 0; i < msg->used; i++) {
        if (i == msg->used - 1)
            printf("%u", msg->array[i]);
        else
            printf("%u,",msg->array[i]);
	}
	printf("]\n");

	printf("Message Corrected: ");
	for (size_t i = 0; i < strlen(my_msg); i++) {
		printf("%c",msg->array[i]);
	}
	printf("\n");
	return 0;
}
