(lang dune 2.0)
(name jsoo-css)

(source
 (github ml-in-barcelona/jsoo-css))

(license MIT)
(authors "davesnx")
(maintainers "davesnx")

(generate_opam_files true)

(package
 (name jsoo-css)
 (synopsis "CSS Typed functional interface in jsoo")
 (description "CSS Typed functional interface in jsoo, bindings to inline styles and emotion")
 (depends
  (ocaml (>= 4.12.0))
  (dune (and (>= 2.5) (< 4)))
  (gen_js_api (and (>= 1.0.7) (< 1.1.0)))
  js_of_ocaml
  js_of_ocaml-ppx
  (odoc :with-doc)
  (ocamlformat :dev)
  (dune-release :dev)
  (ocaml-lsp-server :dev)
  (reason :with-test)
  (jsoo-react :dev)
 )
)
