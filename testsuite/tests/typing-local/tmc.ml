(* TEST
  * stack-allocation
  ** setup-ocamlopt.opt-build-env
  *** ocamlopt.opt
    ocamlopt_opt_exit_status = "2"
  **** check-ocamlopt.opt-output
*)

(* Cannot use TMC on local-returning functions *)
let[@tail_mod_cons] rec copy_list (local_ li) = local_
  match li with
  | [] -> []
  | x :: xs -> x :: copy_list xs

