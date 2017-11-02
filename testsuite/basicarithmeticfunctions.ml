open Printf
module M = Mpfr

let all op1 op2 =
  let r = M.add op1 op2 in printf "%s\n" (M.get_formatted_str r);
  let r = M.add_int op1 (M.get_int op2) in printf "%s\n" (M.get_formatted_str r);
  let r = M.add_float op1 (M.get_float op2) in printf "%s\n" (M.get_formatted_str r);
  let r = M.sub op1 op2 in printf "%s\n" (M.get_formatted_str r);
  let r = M.sub_int op1 (M.get_int op2) in printf "%s\n" (M.get_formatted_str r);
  let r = M.int_sub (M.get_int op1) op2 in printf "%s\n" (M.get_formatted_str r);
  let r = M.sub_float op1 (M.get_float op2) in printf "%s\n" (M.get_formatted_str r);
  let r = M.float_sub (M.get_float op1) op2 in printf "%s\n" (M.get_formatted_str r);
  let r = M.mul op1 op2 in printf "%s\n" (M.get_formatted_str r);
  let r = M.mul_int op1 (M.get_int op2) in printf "%s\n" (M.get_formatted_str r);
  let r = M.mul_float op1 (M.get_float op2) in printf "%s\n" (M.get_formatted_str r);
  let r = M.div op1 op2 in printf "%s\n" (M.get_formatted_str r);
  let r = M.div_int op1 (M.get_int op2) in printf "%s\n" (M.get_formatted_str r);
  let r = M.int_div (M.get_int op1) op2 in printf "%s\n" (M.get_formatted_str r);
  let r = M.div_float op1 (M.get_float op2) in printf "%s\n" (M.get_formatted_str r);
  let r = M.float_div (M.get_float op1) op2 in printf "%s\n" (M.get_formatted_str r);
  let r = M.sqrt op1 in printf "%s\n" (M.get_formatted_str r);
  let r = M.sqrt_int (M.get_int op1) in printf "%s\n" (M.get_formatted_str r);
  let r = M.cbrt op1 in printf "%s\n" (M.get_formatted_str r);
  let r = M.root op1 10 in printf "%s\n" (M.get_formatted_str r);
  let r = M.pow op1 op2 in printf "%s\n" (M.get_formatted_str r);
  let r = M.pow_int op1 (M.get_int op2) in printf "%s\n" (M.get_formatted_str r);
  let r = M.neg op1 in printf "%s\n" (M.get_formatted_str r);
  let r = M.abs op1 in printf "%s\n" (M.get_formatted_str r);
  let r = M.dim op1 op2 in printf "%s\n" (M.get_formatted_str r);
  let r = M.mul_2int op1 (M.get_int op2) in printf "%s\n" (M.get_formatted_str r);
  let r = M.div_2int op1 (M.get_int op2) in printf "%s\n" (M.get_formatted_str r)

let _ =
  all (M.make_from_float (1. /. 3.)) (M.make_from_float (1. /. 10.)); printf "\n";
  all (M.make_from_float ((~-. 4.) /. 3.)) (M.make_from_float (1. /. 10.)); printf "\n";
  all (M.make_from_float (1. /. 3.)) (M.make_from_float ((~-. 113.) /. 10.)); printf "\n";
  all (M.make_zero M.Positive) (M.make_from_float ((~-. 1.) /. 10.)); printf "\n";
  all (M.make_zero M.Negative) (M.make_zero M.Negative)
