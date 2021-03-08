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
  js_of_ocaml
  (ocaml (>= 4.08.0))
  (dune (>= 2.0))
  (alcotest :with-test)
  (odoc :with-doc)
 )
)