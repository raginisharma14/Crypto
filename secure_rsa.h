#ifndef SECURE_RSA
#define SECURE_RSA

clock_t start, end;
const int SIZE_OF_MODULO = 2048;
const int ACCURACY_PARAMETER = 100;
/*
Declaration of all the mpz_t variables
*/
mpz_t rand_num;
mpz_t m_value;
mpz_t p_value;
mpz_t q_value;
mpz_t n_value;
mpz_t p_minusvalue;
mpz_t q_minusvalue;
mpz_t e_value;
mpz_t c_value;
mpz_t d_value;
mpz_t phi_value;
mpz_t constant_value;
mpz_t gcd_value_of_e_and_phi;
mpf_t float_value_of_n;
mpf_t float_value_of_d;
mpf_t check_d_value;
mpz_t zero_constant_value;
gmp_randstate_t r_state;
unsigned long int seed;
/*
Below is the declaration of two functions encryption and decryption. 
*/
void encryption(mpz_t m);
void decryption(mpz_t c);
bool CheckForDValue();
void Initialize();
void GeneratePrimes();
void Clear();
void Print();

#endif
