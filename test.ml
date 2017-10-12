open Mlmpfr;;
  

let x = mpfr_init2 500 in
    mpfr_out_str 10 100 x MPFR_RNDZ
    
