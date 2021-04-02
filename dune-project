(lang dune 2.0)
(name jsoo-css)

(source
 (github davesnx/jsoo-css))

(license MIT)
(authors "davesnx")
(maintainers "davesnx")

(generate_opam_files true)

(package
 (name jsoo-css)
 (synopsis "Typed functional interface to CSS in jsoo")
 (description "Typed functional interface to CSS in jsoo, bindings to inline styles and emotion")
 (depends
  (ocaml (>= 4.08.0))
  (dune (>= 2.0))
  (reason (>= 3.7.0))
  (gen_js_api (and (>= 1.0.7) (< 1.1.0)))
  js_of_ocaml
  js_of_ocaml-ppx
  js_of_ocaml-lwt
  jsoo-react
  lwt
  (odoc :with-doc)
  ocaml-lsp-server
 )
)