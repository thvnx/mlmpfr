module C = Configurator.V1

let cflags = ["-O2"; "-Wall"; "-Wextra"; "-fPIC"]

let () =
  C.main ~name:"discover-mpfr" (fun c ->
    let default : C.Pkg_config.package_conf =
      { libs   = ["-lmpfr"]
      ; cflags = cflags
      }
    in
    let conf =
      match C.Pkg_config.get c with
  | None -> default
  | Some pc ->
      match (C.Pkg_config.query pc ~package:"mpfr") with
     | None -> default
     | Some deps -> deps
    in


    C.Flags.write_sexp "c_flags.sexp" (List.concat [cflags; conf.cflags]);
    C.Flags.write_sexp "c_library_flags.sexp" conf.libs)

