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
 (synopsis "Bindings to CSS in jsoo")
 (description "Bindsings to CSS in jsoo")
 (depends
  (ocaml (>= 4.08.0))
  (dune (>= 2.0))
  reason (>= 3.7.0)
  js_of_ocaml
  js_of_ocaml-ppx
  (alcotest :with-test)
  (odoc :with-doc)
  ocaml-lsp-server
 )
)