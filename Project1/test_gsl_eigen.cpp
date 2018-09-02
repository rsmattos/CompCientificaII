#include <stdio.h>
#include <iostream>
// #include <complex.h>
#include <complex>
// #include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_eigen.h>

int
main (void)
{
  double Matrix[] = { 0.0, 1.0, 0.0, 0.0,
                      0.0, 0.0, 1.0, 0.0,
                      0.0, 0.0, 0.0, 1.0,
                     -5.0, -4.0, -2.0, -1.0 };

    // double Defective[] = { -1.0,  0.0,  0.0,
    //                         1.0, -1.0,  0.0,
    //                         0.0,  1.0, -1.0};

  gsl_matrix_view m
    = gsl_matrix_view_array (Matrix, 4, 4);

  gsl_vector_complex *eval = gsl_vector_complex_alloc (4);
  gsl_matrix_complex *evec = gsl_matrix_complex_alloc (4, 4);

  gsl_eigen_nonsymmv_workspace * w =
    gsl_eigen_nonsymmv_alloc (4);

  gsl_eigen_nonsymmv (&m.matrix, eval, evec, w);

  gsl_eigen_nonsymmv_free (w);

  gsl_eigen_nonsymmv_sort (eval, evec,
                           GSL_EIGEN_SORT_ABS_DESC);

    // std::complex<double> test[2];
    std::complex<double> *test;
    test = new std::complex<double>[2];

    std::complex<double> *evals = new std::complex<double>[4];
    std::complex<double>**evecs = new std::complex<double>*[4];

    for(int i = 0; i < 4; i++){
        evecs[i] = new std::complex<double>[4];
    }


    gsl_permutation *p=gsl_permutation_alloc(4);
    gsl_matrix_complex *S=gsl_matrix_complex_alloc(4,4);
    gsl_matrix_complex *Sinv=gsl_matrix_complex_alloc(4,4);

  {
    int i, j;

    for (i = 0; i < 4; i++)
      {
        gsl_complex eval_i
           = gsl_vector_complex_get (eval, i);
        gsl_vector_complex_view evec_i
           = gsl_matrix_complex_column (evec, i);

        printf ("eigenvalue = %g + %gi\n",
                GSL_REAL(eval_i), GSL_IMAG(eval_i));
        std::real(evals[i]) = GSL_REAL(eval_i); std::imag(evals[i]) = GSL_IMAG(eval_i);
        std::cout << evals[i] << std::endl;
        printf ("eigenvector = \n");
        for (j = 0; j < 4; ++j)
          {
            gsl_complex z =
              gsl_vector_complex_get(&evec_i.vector, j);
            printf("%g + %gi\n", GSL_REAL(z), GSL_IMAG(z));
            std::real(evecs[i][j]) = GSL_REAL(z); std::imag(evecs[i][j]) = GSL_IMAG(z);
            gsl_matrix_complex_set(S,i,j,z);
            std::cout << evecs[i][j] << std::endl;
          }
      }
  }

  gsl_vector_complex_free(eval);
  gsl_matrix_complex_free(evec);

    int i, j, s;
  

    // gsl_matrix_complex_set(S,0,1,gsl_complex_rect(1.0,-1.0));
    // gsl_matrix_complex_set(S,1,0,gsl_complex_rect(1.5,0.8));
    // gsl_matrix_complex_set(S,1,1,gsl_complex_rect(-0.5,1.4));

    gsl_linalg_complex_LU_decomp(S,p,&s);
    gsl_linalg_complex_LU_invert(S,p,Sinv);

    gsl_complex det = gsl_linalg_complex_LU_det(S,s);

    std::complex<double> deter;

    std::real(deter) = GSL_REAL(det); std::imag(deter) = GSL_IMAG(det); 

    std::cout << deter << std::endl;
    
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){

    printf("\nesinv(%d,%d)=%g+%g*j",i+1,j+1,GSL_REAL(gsl_matrix_complex_get(Sinv,i,
    j)),GSL_IMAG(gsl_matrix_complex_get(Sinv,i,j)));
        }
    }
    printf("\n");

  delete[] test;
  delete[] evals;
  delete[] evecs;

  return 0;
}