#include <string>
#include <gmpxx.h>
#include "secure_rsa.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <map>
#include <time.h>
/*
m_value: message sent by the user
e_value: public exponent
d_value: private exponent
c_value: decrypted message
n_value: modulus

*/
void Initialize()
{
mpz_init(e_value);
mpz_init(constant_value);
mpz_init(p_value);
mpz_init(q_value);
mpz_init(n_value);
mpz_init(rand_num);
mpz_init(d_value);
mpz_init(c_value);
mpf_init(float_value_of_n);
mpz_init(phi_value);
mpz_init(p_minusvalue);
mpz_init(q_minusvalue);
mpf_init(float_value_of_d);
mpz_init(gcd_value_of_e_and_phi);
mpf_init(check_d_value);
mpz_set_ui(e_value, 65537);
mpz_set_ui(constant_value, 1);
mpz_init(zero_constant_value);
gmp_randinit_mt(r_state);
}
void Encryption()
{
    mpz_powm(c_value, m_value, e_value, n_value);
    gmp_printf("encrypted value of the message is::%Zd", c_value);
}
void Decryption()
{
    //3.CheckPoint::Timing Attack is implemented by embedding random value to the cipher text before decryting the cipher text.blind value is the embedded value.    
    start = clock();
    seed = (unsigned long int)time(0);
    printf("value of seed::%lu", seed);
    gmp_randseed_ui(r_state, seed);
    mpz_urandomb(rand_num,r_state,SIZE_OF_MODULO);
    mpz_t blind_value;
    mpz_init(blind_value);
    mpz_pow_ui(blind_value, rand_num, 65537);
    mpz_mul(c_value, blind_value, c_value);
    mpz_mod(c_value, c_value,n_value);
    mpz_powm(m_value, c_value, d_value, n_value);
    end = clock();
    double msecs;
    msecs = ((double) (end-start)) * 1000/CLOCKS_PER_SEC;
    printf(" Execution Time Of The DEcryption Function is ::%f",msecs);
    gmp_printf("decrypted value of the encrypted message is::%Zd", m_value);

}
bool CheckForDValue()
{
    mpf_set_z(float_value_of_n, n_value);                       
    mpf_sqrt(check_d_value, float_value_of_n);
    mpf_set_z(float_value_of_d, d_value);
    if(mpf_cmp(float_value_of_d, check_d_value) > 0)
    {
        return true;
    }
    return false;
}
void GeneratePrimes() 
{
    int count_of_primes =0;
    seed = (unsigned long int)time(0);
    printf("value of seed::%lu", seed);
    gmp_randseed_ui(r_state, seed);
    while(true)
    {

        mpz_urandomb(rand_num,r_state,SIZE_OF_MODULO);
 	if((mpz_even_p(rand_num) == 0))
	{
	    if(mpz_probab_prime_p(rand_num, ACCURACY_PARAMETER) == 1)
	    {	
                count_of_primes++;
		if(count_of_primes == 1)
		{
		    mpz_set(p_value,rand_num);
		}
		if(count_of_primes == 2)
		{
		    mpz_set(q_value,rand_num);
         	    mpz_mul(n_value, p_value, q_value);           
    		    mpz_sub(p_minusvalue, p_value, constant_value);
    		    mpz_sub(q_minusvalue, q_value, constant_value);
    		    mpz_mul(phi_value, p_minusvalue, q_minusvalue);
                    mpz_gcd(gcd_value_of_e_and_phi, e_value, phi_value);
    		    mpz_invert(d_value, e_value, phi_value);
                    bool d_value_greater_than_n_power_half = CheckForDValue();
		    if(mpz_cmp(gcd_value_of_e_and_phi, constant_value) == 0)
		    {
			if(!(mpz_cmp(d_value,zero_constant_value) == 0))
			{
			    if(d_value_greater_than_n_power_half)
			    {
				break;
			    }
			}
                    }
		    else
		    {
		        count_of_primes =0;
				
	            }
			   	
		} 
	    }		
	}

    }

}

int main (int argc, char* argv[])
{ 
    start = clock();
    mpz_init(m_value);
    printf("Enter Integer value that should get encrypted::");
    std::cin >> m_value;
    Initialize();
    GeneratePrimes();
    Encryption();
    Decryption();
    Print();
    Clear();
    end = clock();
    double msecs;
    msecs = ((double) (end-start)) * 1000/CLOCKS_PER_SEC;
    printf(" Execution Time Of The Entire Program::%f",msecs);
    return 0;
}
void Print()
{
    printf("Below are the private key, public key, Modulus and encrypted values of the message given by the user::\n");
    gmp_printf("value of d is --%Zd\n", d_value);
    gmp_printf("value of e is --%Zd\n", e_value);
    gmp_printf("value of n is --%Zd\n", n_value);
    gmp_printf("value of c is --%Zd\n", c_value);

}
void Clear()
{
    mpz_clear(rand_num);
    mpz_clear(m_value);
    mpz_clear(p_value);
    mpz_clear(q_value);
    mpz_clear(n_value);
    mpz_clear(p_minusvalue);
    mpz_clear(q_minusvalue);
    mpz_clear(e_value);
    mpz_clear(c_value);
    mpz_clear(d_value);
    mpz_clear(phi_value);
    mpz_clear(constant_value);
    mpz_clear(gcd_value_of_e_and_phi);
    mpf_clear(float_value_of_n);
    mpf_clear(float_value_of_d);
    mpf_clear(check_d_value);
    mpz_clear(zero_constant_value);
    gmp_randclear(r_state);
}
