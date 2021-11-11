/*
모두의 코드 16-2강 2번 문제
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_DIGIT 10
#define MAX_INT_DIGIT 20

struct BigNum {
	int i_digit[MAX_DIGIT];	//0번이 1의자리, 1번이 10의자리...
	int d_digit[MAX_DIGIT];	//0번이 0.1, 1번이 0.01...
	int i_total_digit;
	int d_total_digit;
	char sign;
	char inf;
};

struct BigInt {
	int i_digit[MAX_INT_DIGIT];	//0번이 1의자리, 1번이 10의자리...
	int i_total_digit;
	char sign;
	char inf;
};

struct BigNum generate_big_num();
struct BigNum generate_empty_big_num();
struct BigInt generate_empty_big_int();
struct BigInt int_to_big_int(int input);

void calibrate_big_int(struct BigInt* target);
void calibrate_big_num(struct BigNum* target);

struct BigInt big_num_to_big_int(struct BigNum input);

void print_big_num(struct BigNum input);
void print_big_int(struct BigInt input);

int compare_big_num(struct BigNum a, struct BigNum b);
int compare_big_int(struct BigInt a, struct BigInt b);
void shift_array(int* parray, int array_size, int shift);

struct BigInt multiply_big_int_int(struct BigInt a, int b);

struct BigNum add_big_num(struct BigNum a, struct BigNum b);
struct BigNum subtract_big_num(struct BigNum a, struct BigNum b);
struct BigNum multiply_big_num(struct BigNum a, struct BigNum b);
struct BigNum divide_big_num(struct BigNum a, struct BigNum b);

int main() {
	srand((unsigned int)time(NULL));

	struct BigNum A;
	struct BigNum B;

	A = generate_big_num();
	B = generate_big_num();

	print_big_num(A);
	print_big_num(B);

	struct BigNum Divided = divide_big_num(A, B);

	printf("Divided: ");
	print_big_num(Divided);

	struct BigNum Multiplyed = multiply_big_num(A, B);

	printf("Multiplyed: ");
	print_big_num(Multiplyed);

	struct BigNum Subtracted = subtract_big_num(A, B);

	printf("Subtracted: ");
	print_big_num(Subtracted);

	struct BigNum Added = add_big_num(A, B);

	printf("Added: ");
	print_big_num(Added);

	return 0;
}

struct BigNum generate_big_num() {
	struct BigNum output;

	output.i_total_digit = (rand() % (MAX_DIGIT - 1)) + 1;
	output.d_total_digit = (rand() % (MAX_DIGIT - 1)) + 1;
	printf("DEBUG: i total digit is %d\n", output.i_total_digit);
	printf("DEBUG: d total digit is %d\n", output.d_total_digit);

	int i;
	for (i = 0; i < output.i_total_digit - 1; i++) output.i_digit[i] = rand() % 10;
	output.i_digit[i] = (rand() % 9) + 1;
	for (i = output.i_total_digit; i < MAX_DIGIT; i++)output.i_digit[i] = 0;
	for (i = 0; i < output.d_total_digit - 1; i++) output.d_digit[i] = rand() % 10;
	output.d_digit[i] = (rand() % 9) + 1;
	for (i = output.d_total_digit; i < MAX_DIGIT; i++)output.d_digit[i] = 0;

	output.sign = rand() % 2;
	//output.sign = 0;
	printf("DEBUG: sign is %d\n", output.sign);
	output.inf = 0;

	return output;
}

struct BigNum generate_empty_big_num() {
	struct BigNum output;
	output.i_total_digit = 0;
	output.d_total_digit = 0;
	int i;
	for (i = 0; i < MAX_DIGIT; i++) {
		output.i_digit[i] = 0;
		output.d_digit[i] = 0;
	}
	output.sign = 0;
	output.inf = 0;
	return output;
}

struct BigInt generate_empty_big_int() {
	struct BigInt output;
	output.i_total_digit = 0;
	output.sign = 0;
	output.inf = 0;
	int i;
	for (i = 0; i < MAX_INT_DIGIT; i++)output.i_digit[i] = 0;
	return output;
}

struct BigInt int_to_big_int(int input) {
	struct BigInt output = generate_empty_big_int();

	int max_digit = 0;
	int i;
	for (i = 0; i < MAX_INT_DIGIT; i++) {
		output.i_digit[i] = input % 10;
		input /= 10;
		max_digit++;
		if (input == 0)break;
	}
	output.i_total_digit = max_digit;
	return output;
}

void calibrate_big_int(struct BigInt* target) {
	int i;
	for (i = MAX_INT_DIGIT - 1; i >= 0; i--)if (target->i_digit[i] != 0) break;
	target->i_total_digit = i + 1;
}

void calibrate_big_num(struct BigNum* target) {
	int i;
	for (i = MAX_DIGIT - 1; i >= 0; i--)if (target->i_digit[i] != 0) break;
	target->i_total_digit = i + 1;
	for (i = MAX_DIGIT - 1; i >= 0; i--)if (target->d_digit[i] != 0) break;
	target->d_total_digit = i + 1;
}

void print_big_num(struct BigNum input) {
	if (input.sign)printf("-");
	else printf("+");
	if (input.inf) {
		printf("inf");
	}
	else {
		int i;
		for (i = input.i_total_digit - 1; i >= 0; i--) printf("%d", input.i_digit[i]);
		printf(".");
		for (i = 0; i < input.d_total_digit; i++) printf("%d", input.d_digit[i]);
	}
	printf("\n");
}

void print_big_int(struct BigInt input) {
	if (input.sign) printf("-");
	else printf("+");

	if (input.inf) {
		printf("inf");
	}
	else {
		int i;
		for (i = input.i_total_digit - 1; i >= 0; i--)printf("%d", input.i_digit[i]);
	}
	printf("\n");
}

struct BigInt big_num_to_big_int(struct BigNum input) {
	struct BigInt output = generate_empty_big_int();
	int total_digit = input.i_total_digit + input.d_total_digit;
	int i;

	for (i = input.d_total_digit - 1; i >= 0; i--) output.i_digit[input.d_total_digit - 1 - i] = input.d_digit[i];
	for (i = 0; i < input.i_total_digit; i++) output.i_digit[input.d_total_digit + i] = input.i_digit[i];

	output.i_total_digit = total_digit;
	output.sign = input.sign;
	output.inf = input.inf;
	return output;
}

struct BigNum big_int_to_big_num(struct BigInt input, int power) {
	struct BigNum output = generate_empty_big_num();
	output.inf = input.inf;
	if (output.inf) return output;

	int i;
	if (power < 0) {
		output.d_total_digit = -power;
		output.i_total_digit = input.i_total_digit + power;
		int j = 0;
		for (i = output.d_total_digit - 1; i >= 0; i--) {
			if (j >= MAX_DIGIT)break;
			output.d_digit[j] = input.i_digit[i];
			j++;
		}
		j = 0;
		for (i = output.d_total_digit; i < input.i_total_digit; i++) {
			if (j >= MAX_DIGIT)break;
			output.i_digit[j] = input.i_digit[i];
			j++;
		}
		output.sign = input.sign;
		calibrate_big_num(&output);
		return output;
	}
	else if (power == 0) {
		printf("Not Implemented\n");
	}
	else {
		printf("Not Implemented\n");
	}
}

void shift_array(int* parray, int array_size, int shift) {
	int i;

	//printf("DEBUG: before shift: ");
	//for (i = 0; i < array_size; i++)printf("%d ", parray[i]);
	//printf("\n");

	if (shift > 0) {
		for (i = array_size - 1 - shift; i >= 0; i--) parray[i + shift] = parray[i];
		for (i = 0; i < shift; i++) parray[i] = 0;
	}if (shift < 0) {
		for (i = shift; i < array_size; i++)parray[i - shift] = parray[i];
		for (i = array_size - shift; i < array_size; i++)parray[i] = 0;
	}
	//printf("DEBUG: after shift: ");
	//for (i = 0; i < array_size; i++)printf("%d ", parray[i]);
	//printf("\n");
}

int compare_big_num(struct BigNum a, struct BigNum b) {
	// a > b => 1, a < b => 0
	if (a.i_total_digit > b.i_total_digit) return 1;
	else if (a.i_total_digit < b.i_total_digit) return 0;
	else {
		if (a.i_total_digit == 0) {
			if (a.d_digit[0] > b.d_digit[0]) return 1;
			else if (a.d_digit[0] < b.d_digit[0]) return 0;
			else {
				shift_array(a.d_digit, MAX_DIGIT, -1);
				shift_array(b.d_digit, MAX_DIGIT, -1);
				return compare_big_num(a, b);
			}
		}
		else {
			if (a.i_digit[a.i_total_digit - 1] > b.i_digit[b.i_total_digit - 1]) return 1;
			else if (a.i_digit[a.i_total_digit - 1] < b.i_digit[b.i_total_digit - 1]) return 0;
			else {
				a.i_digit[a.i_total_digit - 1] = 0;
				b.i_digit[b.i_total_digit - 1] = 0;
				a.i_total_digit--;
				b.i_total_digit--;
				return compare_big_num(a, b);
			}
		}		
	}
}

int compare_big_int(struct BigInt a, struct BigInt b) {
	// a > b => 1, a < b => 0
	if (a.i_total_digit > b.i_total_digit) return 1;
	else if (a.i_total_digit < b.i_total_digit) return 0;
	else {
		int* a_first_digit = &a.i_digit[a.i_total_digit - 1];
		int* b_first_digit = &b.i_digit[b.i_total_digit - 1];
		if (*a_first_digit > *b_first_digit)return 1;
		else if (*a_first_digit < *b_first_digit)return 0;
		else {
			*a_first_digit = 0;
			*b_first_digit = 0;
			a.i_total_digit--;
			b.i_total_digit--;
			return compare_big_int(a, b);
		}
	}
}

struct BigInt multiply_big_int_int(struct BigInt a, int b) {
	struct BigInt output = generate_empty_big_int();

	int buffer = 0;
	int i;
	for (i = 0; i < a.i_total_digit; i++) {
		int raw_result = buffer + a.i_digit[i] * b;
		int new_buffer = raw_result / 10;
		int result = raw_result % 10;
		//printf("DEBUG: %d + %d * %d = %d = %d + %d\n", buffer, a.i_digit[i], b, raw_result, new_buffer, result);
		buffer = new_buffer;
		output.i_digit[i] = result;
	}
	if (i == MAX_INT_DIGIT) {
		if (buffer != 0) {
			output.inf = 1;
			printf("DEBUG: inf overflow\n");
			return output;
		}
	}
	output.i_digit[i] = buffer;
	output.i_total_digit = a.i_total_digit;
	if (buffer != 0) {
		output.i_total_digit++;
		//printf("DEBUG: buffer == %d => total digit ++\n", buffer);
	}
	if (b >= 0) {
		output.sign = a.sign;
	}
	else {
		if (a.sign)output.sign = 0;
		else output.sign = 1;
	}
	calibrate_big_int(&output);
	return output;
}

struct BigInt add_big_int(struct BigInt a, struct BigInt b) {
	struct BigInt output = generate_empty_big_int();
	int buffer = 0;
	int i;
	for (i = 0; i < MAX_INT_DIGIT; i++) {
		int result = a.i_digit[i] + b.i_digit[i] + buffer;
		int new_buffer = result / 10;
		int new_result = result % 10;
		//printf("DEBUG: %d + %d + %d = %d = %d + %d\n", a.i_digit[i], b.i_digit[i], buffer, result, new_buffer, new_result);
		buffer = new_buffer;
		output.i_digit[i] = new_result;
	}
	if (buffer != 0) {
		output.inf = 1;
		printf("DEBUG: inf overflow\n");
		return output;
	}
	
	calibrate_big_int(&output);
	return output;
}

struct BigInt subtract_big_int(struct BigInt a, struct BigInt b) {
	struct BigInt output = generate_empty_big_int();
	if (a.sign == 0 && b.sign == 0) {
		if (compare_big_int(a, b)) {
			//printf("DEBUG: a > b\n");
			int start_digit;
			if (a.i_total_digit > b.i_total_digit)start_digit = a.i_total_digit;
			else start_digit = b.i_total_digit;

			int buffer = 0;
			int i;
			for (i = 0; i < start_digit; i++) {
				int raw_result = buffer + a.i_digit[i] - b.i_digit[i];
				int result = raw_result;
				int new_buffer = 0;
				if (raw_result < 0) {
					new_buffer = -1;
					result += 10;
				}
				//printf("DEBUG: %d + %d - %d = %d = %d * 10 + %d\n", buffer, a.i_digit[i], b.i_digit[i], raw_result, new_buffer, result);
				output.i_digit[i] = result;
				buffer = new_buffer;
			}
			calibrate_big_int(&output);
			//printf("Final buffer %d\n", buffer);
			output.sign = 0;
			return output;
		}
		else {
			//printf("DEBUG: a < b\n");
			output = subtract_big_int(b, a);
			output.sign = 1;
			return output;
		}
	}
	else {
		printf("Not Implemented\n");
	}
}

void divide_and_mod_big_int(struct BigInt a, struct BigInt b, int* divided, struct BigInt* mod) {
	*divided = 0;
	//printf("DEBUG: A="); print_big_int(a);
	//printf("DEBUG: B="); print_big_int(b);
	while (compare_big_int(a, b)) {
		a = subtract_big_int(a, b);
		++*divided;
		//printf("DEBUG: a=");
		//print_big_int(a);
		//printf("DEBUG: divided=%d\n", *divided);
	}
	*mod = a;
}

void shift_big_int(struct BigInt *input, int shift) {
	if (input->i_digit[MAX_INT_DIGIT - 1] != 0) {
		input->inf = 1;
		printf("DEBUG: inf overflow\n");
		return;
	}
	shift_array(input->i_digit, MAX_INT_DIGIT, shift);
	input->i_total_digit += shift;
	calibrate_big_int(input);
}

struct BigNum add_big_num(struct BigNum a, struct BigNum b) {
	struct BigNum output;
	output = generate_empty_big_num();
	if (a.sign == 1 && b.sign == 1) {
		// (-1) + (-1) = - (1 + 1)
		//printf("DEBUG: a + b = - (-a + -b)\n");
		a.sign = 0;
		b.sign = 0;
		output = add_big_num(a, b);
		output.sign = 1;
		return output;
	}
	else if (a.sign == 1 && b.sign == 0) {
		//printf("DEBUG: a + b = b - (-a)\n");
		// (-1) + (1) = (1) - (1)
		a.sign = 0;
		return subtract_big_num(b, a);
	}
	else if (a.sign == 0 && b.sign == 1) {
		//printf("DEBUG: a + b = a - (-b)\n");
		// (1) + (-1) = 1 - 1
		b.sign = 0;
		return subtract_big_num(a, b);
	}

	//printf("Adding\n");

	int starting_digit;
	if (a.d_total_digit > b.d_total_digit) starting_digit = a.d_total_digit;
	else starting_digit = b.d_total_digit;
	//printf("DEBUG: d starting digit is %d\n", starting_digit);

	int buffer = 0;
	int i;
	for (i = starting_digit - 1; i >= 0; i--) {
		int result = a.d_digit[i] + b.d_digit[i] + buffer;
		int new_buffer = result / 10;
		int new_result = result % 10;
		//printf("DEBUG: %d + %d + %d = %d = %d + %d\n", a.d_digit[i], b.d_digit[i], buffer, result, new_buffer, new_result);
		buffer = new_buffer;
		output.d_digit[i] = new_result;
	}
	output.d_total_digit = starting_digit;

	if (a.i_total_digit > b.i_total_digit) starting_digit = a.i_total_digit;
	else starting_digit = b.i_total_digit;
	//printf("DEBUG: i starting digit is %d\n", starting_digit);

	for (i = 0; i < starting_digit; i++) {
		int result = a.i_digit[i] + b.i_digit[i] + buffer;
		int new_buffer = result / 10;
		int new_result = result % 10;
		//printf("DEBUG: %d + %d + %d = %d = %d + %d\n", a.i_digit[i], b.i_digit[i], buffer, result, new_buffer, new_result);
		buffer = new_buffer;
		output.i_digit[i] = new_result;
	}
	if (i == MAX_DIGIT && buffer != 0) {
		output.inf = 1;
		printf("DEBUG: inf overflow\n");
		return output;
	}

	output.i_digit[i] = buffer;
	//printf("DEBUG: [%d] = %d\n", i, buffer);
	if (buffer == 0) output.i_total_digit = starting_digit;
	else output.i_total_digit = starting_digit + 1;
	//printf("DEBUG: i starting digit is %d\n", starting_digit);

	return output;
}

struct BigNum subtract_big_num(struct BigNum a, struct BigNum b) {
	struct BigNum output;
	output = generate_empty_big_num();
	if (a.sign == 1 && b.sign == 1) {
		//printf("DEBUG: a - b = (-b) - (-a)\n");
		// (-2) - (-3) = 3 - 2
		a.sign = 0;
		b.sign = 0;
		output = subtract_big_num(b, a);
		return output;
	}
	else if (a.sign == 1 && b.sign == 0) {
		//printf("DEBUG: a - b = -(-a + b)\n");
		// (-2) - (3) = - (2 + 3)
		a.sign = 0;
		output = add_big_num(a, b);
		output.sign = 1;
		return output;
	}
	else if (a.sign == 0 && b.sign == 1) {
		//printf("DEBUG: a - b = a + (-b)\n");
		// (2) - (-3) = 2 + 3
		b.sign = 0;
		return add_big_num(a, b);
	}

	//printf("Subtracting\n");

	if (compare_big_num(a, b)) {
		//printf("DEBUG: a > b\n");
		int start_digit = 0;
		if (a.d_total_digit > b.d_total_digit)start_digit = a.d_total_digit;
		else start_digit = b.d_total_digit;

		int buffer = 0;
		int i;
		for (i = start_digit - 1; i >= 0; i--) {
			int raw_result = buffer + a.d_digit[i] - b.d_digit[i];
			int result = raw_result;
			int new_buffer = 0;
			if (raw_result < 0) {
				new_buffer = -1;
				result += 10;
			}
			//printf("DEBUG: %d + %d - %d = %d = %d * 10 + %d\n", buffer, a.d_digit[i], b.d_digit[i], raw_result, new_buffer, result);
			output.d_digit[i] = result;
			buffer = new_buffer;
		}
		output.d_total_digit = start_digit;
		if (a.i_total_digit > b.i_total_digit)start_digit = a.i_total_digit;
		else start_digit = b.i_total_digit;
		for (i = 0; i < start_digit;i++) {
			int raw_result = buffer + a.i_digit[i] - b.i_digit[i];
			int result = raw_result;
			int new_buffer = 0;
			if (raw_result < 0) {
				new_buffer = -1;
				result += 10;
			}
			//printf("DEBUG: %d + %d - %d = %d = %d * 10 + %d\n", buffer, a.i_digit[i], b.i_digit[i], raw_result, new_buffer, result);
			output.i_digit[i] = result;
			buffer = new_buffer;
		}
		output.i_total_digit = start_digit;
		//printf("Final buffer %d\n", buffer);
		output.sign = 0;
		return output;
	}
	else {
		//printf("DEBUG: a < b\n");
		output = subtract_big_num(b, a);
		output.sign = 1;
		return output;
	}
}

struct BigNum multiply_big_num(struct BigNum a, struct BigNum b) {
	//printf("Multiplying\n");

	struct BigNum output = generate_empty_big_num();

	int a_point = a.d_total_digit;
	int b_point = b.d_total_digit;

	struct BigInt a_int = big_num_to_big_int(a);
	struct BigInt b_int = big_num_to_big_int(b);
	struct BigInt output_int = generate_empty_big_int();

	//printf("A to Int: 10^-%d * ", a_point);
	//print_big_int(a_int);
	//printf("B to Int: 10^-%d * ", b_point);
	//print_big_int(b_int);

	int i;
	for (i = 0; i < b_int.i_total_digit; i++) {
		//printf("DEBUG: added so far = ");
		//print_big_int(output_int);
		struct BigInt one_digit_mul = multiply_big_int_int(a_int, b_int.i_digit[i]);
		shift_big_int(&one_digit_mul, i);
		//printf("DEBUG: one digit multiplied: ");
		//print_big_int(one_digit_mul);
		output_int = add_big_int(output_int, one_digit_mul);
		if (output_int.inf) break;
	}
	output_int.sign = a_int.sign ^ b_int.sign;
	//printf("DEBUG: Integer multiplied = ");
	//print_big_int(output_int);
	output = big_int_to_big_num(output_int, -a_point - b_point);
	calibrate_big_num(&output);
	return output;
}

struct BigNum divide_big_num(struct BigNum a, struct BigNum b) {
	//printf("Dividing\n");

	struct BigNum output = generate_empty_big_num();

	int a_point = a.d_total_digit;
	int b_point = b.d_total_digit;
	int point_diff = b_point - a_point;

	struct BigInt a_int = big_num_to_big_int(a);
	struct BigInt b_int = big_num_to_big_int(b);
	struct BigInt output_int = generate_empty_big_int();
	a_int.sign = 0; b_int.sign = 0;

	//printf("A to Int: 10^-%d * ", a_point);
	//print_big_int(a_int);
	//printf("B to Int: 10^-%d * ", b_point);
	//print_big_int(b_int);

	//a / b
	int i_digit[MAX_DIGIT] = { 0 };
	struct BigInt buffer = generate_empty_big_int();
	int i;
	for (i = MAX_INT_DIGIT - 1; i >= 0; i--) {
		int j = i - MAX_INT_DIGIT + a_int.i_total_digit;
		int k;
		if (j >= 0) k = a_int.i_digit[j];
		else k = 0;
		struct BigInt target_digit = int_to_big_int(k);

		//printf("DEBUG: now dividing digit %d, i is %d\n", j, i);

		shift_big_int(&buffer, 1);
		buffer = add_big_int(buffer, target_digit);
		calibrate_big_int(&buffer);
		//printf("DEBUG: new buffer = ");
		//print_big_int(buffer);
		
		int new_digit;
		divide_and_mod_big_int(buffer, b_int, &new_digit, &buffer);
		//printf("DEBUG: new digit = %d\n", new_digit);
		//printf("DEBUG: new buffer = ");
		//print_big_int(buffer);

		if (new_digit == 0) continue;
		output_int.i_digit[i] = new_digit;
	}
	calibrate_big_int(&output_int);
	//printf("DEBUG: output_int=");
	//print_big_int(output_int);
	int point_loc = MAX_INT_DIGIT - a_int.i_total_digit;
	output = big_int_to_big_num(output_int, point_diff - point_loc);
	char sign = a.sign ^ b.sign;
	output.sign = sign;
	return output;
}